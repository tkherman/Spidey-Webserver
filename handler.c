/* handler.c: HTTP Request Handlers */

#include "spidey.h"

#include <errno.h>
#include <limits.h>
#include <string.h>

#include <dirent.h>
#include <unistd.h>

/* Internal Declarations */
http_status handle_browse_request(struct request *request);
http_status handle_file_request(struct request *request);
http_status handle_cgi_request(struct request *request);
http_status handle_error(struct request *request, http_status status);

/**
 * Handle HTTP Request
 *
 * This parses a request, determines the request path, determines the request
 * type, and then dispatches to the appropriate handler type.
 *
 * On error, handle_error should be used with an appropriate HTTP status code.
 **/
http_status
handle_request(struct request *r)
{
    http_status result;

    /* Parse request */
    if (parse_request(r) < 0) {
        result = handle_error(r, HTTP_STATUS_BAD_REQUEST);
    }

    /* Determine request path */
    r->path = determine_request_path(r->uri);
    if (r->path == NULL) {
        result = handle_error(r, HTTP_STATUS_BAD_REQUEST);
    }
    debug("HTTP REQUEST PATH: %s", r->path);

    /* Dispatch to appropriate request handler type */
    request_type type = determine_request_type(r->path);

    if (type == REQUEST_BROWSE)
        result = handle_browse_request(r);
    else if (type == REQUEST_CGI)
        result = handle_cgi_request(r);
    else if (type == REQUEST_FILE)
        result = handle_file_request(r);
    else
        result = handle_error(r, HTTP_STATUS_BAD_REQUEST);
        

    log("HTTP REQUEST STATUS: %s", http_status_string(result));

    return result;
}

/**
 * Handle browse request
 *
 * This lists the contents of a directory in HTML.
 *
 * If the path cannot be opened or scanned as a directory, then handle error
 * with HTTP_STATUS_NOT_FOUND.
 **/
http_status
handle_browse_request(struct request *r)
{
    struct dirent **entries;
    int n;

    /* Open a directory for reading or scanning */
    n = scandir(r->path, &entries, NULL, alphasort);
    if (n == -1) {
        return handle_error(r, HTTP_STATUS_NOT_FOUND);
    }

    /* Write HTTP Header with OK Status and text/html Content-Type */
    fprintf(r->file, "HTTP/1.0 200 OK\n");
    fprintf(r->file, "Content-Type: text/html\n");
    fprintf(r->file, "\r\n");
    

    /* For each entry in directory, emit HTML list item */
    fprintf(r->file, "<ul>\n");
    while (n--) {
        char link[200];
        sprintf(link, "%s:%s/%s", "localhost", Port, entries[n]->d_name);
        debug("link: %s", link);
        fprintf(r->file, "<li><a href=\"%s\">%s</a></li>\n", link, entries[n]->d_name);
        free(entries[n]);
    }
    fprintf(r->file, "</ul>\n");
    free(entries);

    /* Flush socket, return OK */
    fflush(r->file);
    return HTTP_STATUS_OK;
}

/**
 * Handle file request
 *
 * This opens and streams the contents of the specified file to the socket.
 *
 * If the path cannot be opened for reading, then handle error with
 * HTTP_STATUS_NOT_FOUND.
 **/
http_status
handle_file_request(struct request *r)
{
    FILE *fs;
    char buffer[BUFSIZ];
    char *mimetype = NULL;
    size_t nread;

    /* Open file for reading */
    fs = fopen(r->path, "r");
    if (fs == NULL)
        return handle_error(r, HTTP_STATUS_NOT_FOUND);

    /* Determine mimetype */
    mimetype = determine_mimetype(r->path);

    /* Write HTTP Headers with OK status and determined Content-Type */
    fprintf(r->file, "HTTP/1.0 200 OK\n");
    fprintf(r->file, "%s\n", mimetype);
    fprintf(r->file, "\r\n");

    /* Read from file and write to socket in chunks */
    while (!feof(fs)) {
        // read from file to buffer
        nread = fread(buffer, BUFSIZ, 1, fs);

        // write to client file from buffer
        fwrite(buffer, nread, 1, r->file);        
    }

    /* Close file, flush socket, deallocate mimetype, return OK */
    fclose(fs);
    fflush(r->file);
    free(mimetype);

    return HTTP_STATUS_OK;
}

/**
 * Handle file request
 *
 * This popens and streams the results of the specified executables to the
 * socket.
 *
 *
 * If the path cannot be popened, then handle error with
 * HTTP_STATUS_INTERNAL_SERVER_ERROR.
 **/
http_status
handle_cgi_request(struct request *r)
{
    FILE *pfs;
    char buffer[BUFSIZ];

    /* Export CGI environment variables from request:
    * http://en.wikipedia.org/wiki/Common_Gateway_Interface */
    setenv("DOCUMENT_ROOT", RootPath, 1);
    setenv("QUERY_STRING", r->query, 1);
    setenv("REMOTE_ADDR", r->host, 1);
    setenv("REMOTE_PORT", r->port, 1);
    setenv("REQUEST_METHOD", r->method, 1);
    setenv("REQUEST_URI", r->uri, 1);
    setenv("SCRIPT_FILENAME", r->path, 1);
    setenv("SERVER_PORT", Port, 1);


    /* Export CGI environment variables from request headers */
    struct header* header = r->headers;

    while (header != NULL) {
        
        if (streq("Host", header->name))
            setenv("HTTP_HOST", header->value, 1);

        else if (streq("Accept", header->name))
            setenv("HTTP_ACCEPT", header->value, 1);
        
        else if (streq("Accept-Language", header->name))
            setenv("HTTP_ACCEPT_LANGUAGE", header->value, 1);

        else if (streq("Accept-Encoding", header->name))
            setenv("HTTP_ACCEPT_ENCODING", header->value, 1);

        else if (streq("Connection", header->name))
            setenv("HTTP_CONNECTION", header->value, 1);

        else if (streq("User-Agent", header->name))
            setenv("HTTP_USER_AGENT", header->value, 1);

        header = header->next;

    }

    /* POpen CGI Script */
    pfs = popen(r->path, "r");
    if (pfs == NULL) {
        handle_error(r, HTTP_STATUS_INTERNAL_SERVER_ERROR);
    }


    /* Copy data from popen to socket */
    while (fgets(buffer, BUFSIZ, pfs)) {
        fputs(buffer, r->file);
    }

    /* Close popen, flush socket, return OK */
    pclose(pfs);
    fflush(r->file);

    return HTTP_STATUS_OK;
}

/**
 * Handle displaying error page
 *
 * This writes an HTTP status error code and then generates an HTML message to
 * notify the user of the error.
 **/
http_status
handle_error(struct request *r, http_status status)
{
    const char *status_string = http_status_string(status);

    /* Write HTTP Header */
    fprintf(r->file, "HTTP/1.0 %s\n",status_string);
    fprintf(r->file, "Content-Type: text/html\n");
    fprintf(r->file, "\r\n");

    /* Write HTML Description of Error*/
    fprintf(r->file, "<h1>%s</h1>",status_string);
    fprintf(r->file, "<p>Who do you call when shit hits the fan?</p>");


    /* Return specified status */
    return status;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
