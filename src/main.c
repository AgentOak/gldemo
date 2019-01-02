#include "master.h"
#include "window.h"

#include <getopt.h>

const app_options *opts;

static void printHelp(char *argv0) {
    printf(GLDEMO_NAME "\n\
\n\
Usage: %s [-s <0-2>] [-l <n>] [-v] [-D] [-h] [<additional argument>*]\n\
\n\
Parameters:\n\
    -s n: Set swap interval to n frames\n\
        0 disables vsync\n\
        1 enables vsync (double-buffered) (default)\n\
        2 enables vsync (triple-buffered)\n\
    -l n: Set frame limit to n frames per second\n\
        0 disables frame limit (default)\n\
        n outputs a frame at most every 1/n seconds\n\
    -v: Increase verbosity (print additional information)\n\
    -D: Create an OpenGL debug context\n\
        Depending on the driver, this might enable additional messages\n\
        and on older drivers is the only way to obtain error messages\n\
    -V: Print version and exit\n\
    -h, -H: Print this help and exit\n\
", argv0);
}

int main(int argc, char *argv[]) {
    // Construct options with defaults
    app_options *newopts = malloc(sizeof(*opts));
    if (!newopts) {
        FAIL("Could not allocate memory for options");
    }

    newopts->swapInterval = 1;
    newopts->frameLimit = 0;

    int opt;
    while ((opt = getopt(argc, argv, "hHVvDs:l:")) != -1) {
        switch (opt) {
            case 'h':
            case 'H':
                printHelp(argv[0]);
                return EXIT_SUCCESS;
            case 'V':
                printf(GLDEMO_NAME "\n");
                return EXIT_SUCCESS;
            case 'v':
                newopts->verbose = true;
                break;
            case 'D':
                newopts->debug = true;
                break;
            case 's':
                newopts->swapInterval = (uint16_t) strtoul(optarg, NULL, 10);
                break;
            case 'l':
                newopts->frameLimit = (uint16_t) strtoul(optarg, NULL, 10);
                break;
            case '?':
                printHelp(argv[0]);
                return EXIT_FAILURE;
            default:
                FAIL("Argument parsing error");
        }
    }

    INFO(GLDEMO_NAME);

    // Pass other arguments to the scene
    newopts->argc = (uint32_t) argc - optind;
    newopts->argv = &argv[optind];

    opts = newopts;

    for (uint32_t i = 0; i < opts->argc; i++) {
        NOTICE("Additional argument %d: %s", i, opts->argv[i]);
    }

    window();

    free(newopts);
    return EXIT_SUCCESS;
}
