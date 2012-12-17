#include <nitro.h>
#include <nitro-private.h>

static __thread int nitro_errno;

char *nitro_errmsg(NITRO_ERROR error) {
    switch (error) {
        case NITRO_ERR_ERRNO:
            return strerror(errno);
            break;
        case NITRO_ERR_ALREADY_RUNNING:
            return "nitro is already running; cannot call nitro_start twice";
            break;
        case NITRO_ERR_TCP_LOC_NOCOLON:
            return "TCP socket location did not contain a colon";
            break;
        case NITRO_ERR_TCP_LOC_BADPORT:
            return "TCP socket location did not contain an integer port number";
            break;

        default:
            assert(0);
            break;
    }

    return NULL;
}

NITRO_ERROR nitro_error() {
    return nitro_errno;
}

int nitro_set_error(NITRO_ERROR e) {
    nitro_errno = e;
    return -1;
}