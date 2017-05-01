#include "spidey.h"

int main(int argc, char *argv[]) {
    char *port = argv[1];

    // listen to socket
    int server_fd = socket_listen(port);
    if (server_fd < 0) {
        return EXIT_FAILURE;
    }

    debug("Listening on port: %s\n", port);

    while (1) {
        /* Accept an incoming connection */
        debug("Accepting client request");
        struct request *r = accept_request(server_fd);
        if (r == NULL)
            continue;
        
        debug("Handling client request");
        int a = parse_request(r);
        fprintf(stderr, "%d\n", a);
        free_request(r);
    }

    return EXIT_SUCCESS;
}
