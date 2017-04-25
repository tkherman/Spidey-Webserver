/* request.c: HTTP Request Functions */

#include "spidey.h"

#include <errno.h>
#include <string.h>

#include <unistd.h>

int parse_request_method(struct request *r);
int parse_request_headers(struct request *r);

/**
 * Accept request from server socket.
 *
 * This function does the following:
 *
 *  1. Allocates a request struct initialized to 0.
 *  2. Initializes the headers list in the request struct.
 *  3. Accepts a client connection from the server socket.
 *  4. Looks up the client information and stores it in the request struct.
 *  5. Opens the client socket stream for the request struct.
 *  6. Returns the request struct.
 *
 * The returned request struct must be deallocated using free_request.
 **/
struct request *
accept_request(int sfd)
{
    struct request *r;
    struct sockaddr raddr;
    socklen_t rlen = sizeof(raddr);

    /* Allocate request struct (zeroed) */
    calloc(1, sizeof(struct request));

    /* Accept a client */
    if ((r->fd = accept(sfd, &raddr, &rlen)) == -1) {
        fprinf(stderr, "Unable to accept client: %s\n", strerror(errno));
        return -1;
    }

    /* Lookup client information */
    if (getnameinfo(&raddr, rlen, r->host, sizeof(r->host), r->port, sizeof(r->port), 
        NI_NUMERICHOST | NI_NUMERICSERV) != 0) {
        
        fprintf(stderr, "getnameifo fails: %s\n", strerror(errno));
        return -1;
    }
    

    /* Open socket stream */
    r->file = fdopen(r->fd, "r+");

    log("Accepted request from %s:%s", r->host, r->port);
    return r;

fail:
    free_request(r);
    return NULL;
}

/**
 * Deallocate request struct.
 *
 * This function does the following:
 *
 *  1. Closes the request socket stream or file descriptor.
 *  2. Frees all allocated strings in request struct.
 *  3. Frees all of the headers (including any allocated fields).
 *  4. Frees request struct.
 **/
void
free_request(struct request *r)
{
    struct header_t *header;

    if (r == NULL) {
    	return;
    }

    /* Close socket or fd */
    close(r->fd);
    fclose(r->file);

    /* Free allocated strings */
    free(r->method);
    free(r->uri);
    free(r->path);
    free(r->query);

    /* Free headers */
    struct header *curr, *next;
    curr = r->headers;
    next = curr->next;
    
    bool all_deleted = false;
    while (!all_deleted) {
        free(curr->name);
        free(curr->value);

        if (next == NULL) {
            all_deleted = true;
            continue;
        }

        curr = next;
        next = curr->next;
    }


    /* Free request */
    free(r);
}

/**
 * Parse HTTP Request.
 *
 * This function first parses the request method, any query, and then the
 * headers, returning 0 on success, and -1 on error.
 **/
int
parse_request(struct request *r)
{
    /* Parse HTTP Request Method */
    if (parse_request_method(r))
        return -1;

    /* Parse HTTP Requet Headers*/
    if (parse_request_headers(r))
        return -1;
}

/**
 * Parse HTTP Request Method and URI
 *
 * HTTP Requests come in the form
 *
 *  <METHOD> <URI>[QUERY] HTTP/<VERSION>
 *
 * Examples:
 *
 *  GET / HTTP/1.1
 *  GET /cgi.script?q=foo HTTP/1.0
 *
 * This function extracts the method, uri, and query (if it exists).
 **/
int
parse_request_method(struct request *r)
{
    /* Read line from socket */
    char buffer[BUFSIZ];
    
    fgets(buffer, BUFSIZ, r->file);

    /* Parse method and uri */
    char *w;
    w = strtok(buffer, " ");
    r->method = strdup(w);
    w = strtok(buffer, " ");
    r->uri = strdup(w);
    

    /* Parse query from uri */
    char *ptr = strchr(r->uri, '?');
    if (ptr) {
        r->query = ++ptr;
        *ptr = '\0';
    }

    /* Record method, uri, and query in request struct */

    debug("HTTP METHOD: %s", r->method);
    debug("HTTP URI:    %s", r->uri);
    debug("HTTP QUERY:  %s", r->query);

    return 0;

fail:
    return -1;
}

/**
 * Parse HTTP Request Headers
 *
 * HTTP Headers come in the form:
 *
 *  <NAME>: <VALUE>
 *
 * Example:
 *
 *  Host: localhost:8888
 *  User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:29.0) Gecko/20100101 Firefox/29.0
 *  Accept: text/html,application/xhtml+xml
 *  Accept-Language: en-US,en;q=0.5
 *  Accept-Encoding: gzip, deflate
 *  Connection: keep-alive
 *
 * This function parses the stream from the request socket using the following
 * pseudo-code:
 *
 *  while (buffer = read_from_socket() and buffer is not empty):
 *      name, value = buffer.split(':')
 *      header      = new Header(name, value)
 *      headers.append(header)
 **/
int
parse_request_headers(struct request *r)
{
    struct header *curr = NULL;
    char buffer[BUFSIZ];
    char *name;
    char *value;
    
    /* Parse headers from socket */
    while (fgets(buffer, BUFSIZ, r->file)) {
        struct header *new_header = ccalloc(1, sizeof(struct header));

        char *delimPtr = strchr(buffer, ':');
        *delimPtr = '\0';
        name = strdup(buffer);
        delimPtr = skip_whitespace(delimPtr);
        chomp(delimPtr);
        value = strdup(delimPtr);

        new_header->name = name;
        new_header->value = value;
        new_header->next = r->headers;

        r->headers = new_header;

    }

#ifndef NDEBUG
    for (struct header *header = r->headers; header != NULL; header = header->next) {
    	debug("HTTP HEADER %s = %s", header->name, header->value);
    }
#endif
    return 0;

fail:
    return -1;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
