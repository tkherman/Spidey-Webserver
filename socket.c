/* socket.c: Simple Socket Functions */

#include "spidey.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

/**
 * Allocate socket, bind it, and listen to specified port.
 **/
int
socket_listen(const char *port)
{
    struct addrinfo  hints = {0};
    struct addrinfo *results;
    int    socket_fd = -1;
    char *host = NULL;

    /* Lookup server address information */
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    int s;
    if ((s = getaddrinfo(host, port, &hints, &results) != 0)) {
        debug("getaddrinfo failed: %s\n", gai_strerror(s));
        return -1;
    }

    /* For each server entry, allocate socket and try to connect */
    for (struct addrinfo *p = results; p != NULL && socket_fd < 0; p = p->ai_next) {
        /* Allocate socket */
        
        if ((socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) {
            debug("Unable to make socket: %s\n", strerror(errno));
            continue;
        }

	    /* Bind socket */

        if (bind(socket_fd, p->ai_addr, p->ai_addrlen) < 0) {
            debug("Unable to bind: %s\n", strerror(errno));
            close(socket_fd);
            socket_fd = -1;
            continue;
        }

    	/* Listen to socket */
    
        if (listen(socket_fd, SOMAXCONN) < 0) {
            debug("Unable to listen: %s\n", strerror(errno));
            close(socket_fd);
            socket_fd = -1;
            continue;
        }

    }

    freeaddrinfo(results);
    return socket_fd;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
