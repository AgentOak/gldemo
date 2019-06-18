#include "master.h"

#include "window.h"
#include "util/alloc.h"
#include "util/print.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

bool verbose;
const app_options *opts;

static void printHelp(char *argv0) {
    printf(GLDEMO_NAME "\n\
\n\
Usage: %s [-s <0-2>] [-l <n>] [-r <width>x<height>] [-v] [-D] [-h] [<additional argument>*]\n\
\n\
Parameters:\n\
    -s n: Set swap interval to n frames\n\
        0 disables vsync\n\
        1 enables vsync (double-buffered) (default)\n\
        2 enables vsync (triple-buffered)\n\
    -l n: Set frame limit to n frames per second\n\
        0 disables frame limit (default)\n\
        n outputs a frame at most every 1/n seconds\n\
    -r <width>x<height>: Set output resolution\n\
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
    app_options *newopts = safe_malloc(sizeof(*newopts));

    newopts->debugContext = false;
    newopts->swapInterval = 1;
    newopts->frameLimit = 0;
    newopts->outputWidth = 1280;
    newopts->outputHeight = 720;

    int opt;
    while ((opt = getopt(argc, argv, "hHVvDr:s:l:")) != -1) {
        switch (opt) {
            case 'h':
            case 'H':
                printHelp(argv[0]);
                return EXIT_SUCCESS;
            case 'V':
                printf(GLDEMO_NAME "\n");
                return EXIT_SUCCESS;
            case 'v':
                verbose = true;
                break;
            case 'D':
                newopts->debugContext = true;
                break;
            case 'r':
                if (!sscanf(optarg, "%hux%hu", &newopts->outputWidth, &newopts->outputHeight)) {
                    FAIL("Illegal argument for -r");
                }
                break;
            case 's':
                if (!sscanf(optarg, "%hu", &newopts->swapInterval)) {
                    FAIL("Illegal argument for -s");
                }
                break;
            case 'l':
                if (!sscanf(optarg, "%hu", &newopts->frameLimit)) {
                    FAIL("Illegal argument for -l");
                }
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
    newopts->argc = (uint32_t) (argc - optind);
    newopts->argv = &argv[optind];

    opts = newopts;

    for (uint32_t i = 0; i < opts->argc; i++) {
        NOTICE("Additional argument %d: %s", i, opts->argv[i]);
    }

    window();

    safe_free(newopts);
    return EXIT_SUCCESS;
}
