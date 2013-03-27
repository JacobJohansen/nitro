#include "err.h"
#include "socket.h"
#include "runtime.h"

nitro_socket_t *nitro_socket_new() {
    nitro_socket_t *sock;
    ZALLOC(sock);

//    pthread_mutex_init(&sock->l_sub, NULL);
 //   sock->sub_keys = NULL;
    // Change to stdatomic.h XXX
    __sync_add_and_fetch(&the_runtime->num_sock, 1);
    return sock;

}

NITRO_SOCKET_TRANSPORT socket_parse_location(char *location, char **next) {
    if (!strncmp(location, TCP_PREFIX, strlen(TCP_PREFIX))) {
        *next = location + strlen(TCP_PREFIX);
        return NITRO_SOCKET_TCP;
    }

    if (!strncmp(location, INPROC_PREFIX, strlen(INPROC_PREFIX))) {
        *next = location + strlen(INPROC_PREFIX);
        return NITRO_SOCKET_INPROC;
    }

    nitro_set_error(NITRO_ERR_PARSE_BAD_TRANSPORT);
    return -1;
}

void nitro_socket_destroy(nitro_socket_t *s) {
    free(s);
    __sync_add_and_fetch(&the_runtime->num_sock, 1);
}