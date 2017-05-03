/* spidey: Simple HTTP Server */

#include "spidey.h"

#include <errno.h>
#include <stdbool.h>
#include <string.h>

#include <unistd.h>

/* Global Variables */
char *Port	      = "9898";
char *MimeTypesPath   = "/etc/mime.types";
char *DefaultMimeType = "text/plain";
char *RootPath	      = "www";
mode  ConcurrencyMode = SINGLE;

/**
 * Display usage message.
 */
void
usage(const char *progname, int status)
{
    fprintf(stderr, "Usage: %s [hcmMpr]\n", progname);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    -h            Display help message\n");
    fprintf(stderr, "    -c mode       Single or Forking mode\n");
    fprintf(stderr, "    -m path       Path to mimetypes file\n");
    fprintf(stderr, "    -M mimetype   Default mimetype\n");
    fprintf(stderr, "    -p port       Port to listen on\n");
    fprintf(stderr, "    -r path       Root directory\n");
    exit(status);
}

/**
 * Parses command line options and starts appropriate server
 **/
int
main(int argc, char *argv[])
{
    int c;
    int sfd;

    /* Parse command line options */
    char * progname = argv[0];
    int argind = 1;
    while (argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-') {
        char *arg = argv[argind++];
        switch (arg[1]) {
            case 'h':
                usage(progname, 0);
                break;
            case 'c': //specify concurrency mode
                if(argind < argc) {
                    if(streq(argv[argind], "SINGLE")) //default (do nothing)
                        break;
                    if(streq(argv[argind], "FORKING"))
                        ConcurrencyMode = FORKING;
                    else
                        usage(progname, 1);
                    argind++;
                } else {
                    usage(progname, 1);
                }
                break;
            case 'm': //set mimetype path
                if(argind < argc) {
                    MimeTypesPath = argv[argind++];
                } else {
                    usage(progname, 1);
                }
                break;
            case 'M': //set mimetype
                if(argind < argc) {
                    DefaultMimeType = argv[argind++];
                } else {
                    usage(progname, 1);
                }
                break;
            case 'p': //set port 
                if(argind < argc) {
                    Port = argv[argind++];
                } else {
                    usage(progname, 1);
                }
                break;
            case 'r': //set path 
                if(argind < argc) {
                    RootPath = argv[argind++];
                } else {
                    usage(progname, 1);
                }
                break;
            default:
                usage(progname, 1);
                break;
        }
    }

    /* Listen to server socket */

    /* Determine real RootPath */

    log("Listening on port %s", Port);
    debug("RootPath        = %s", RootPath);
    debug("MimeTypesPath   = %s", MimeTypesPath);
    debug("DefaultMimeType = %s", DefaultMimeType);
    debug("ConcurrencyMode = %s", ConcurrencyMode == SINGLE ? "Single" : "Forking");

    /* Start either forking or single HTTP server */
    return EXIT_SUCCESS;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
