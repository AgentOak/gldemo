#include "message.h"
#include "gldemo.h"

#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>

bool debug = false;

static void printHelp(char *argv0) {
    printf(GLDEMO_NAME "\n\
\n\
Usage: %s [-s <0-2>] [-v] [-h] [<scene argument>*]\n\
\n\
Parameters:\n\
    -s n: Set swap interval to n frames\n\
        0 disables vsync\n\
        1 enables vsync (double-buffered) (default)\n\
        2 enables vsync (triple-buffered)\n\
    -v: Increase verbosity (debug mode)\n\
    -V: Print version and exit\n\
    -h, -H: Print this help and exit\n\
", argv0);
}

int main(int argc, char *argv[]) {
    // Construct options with defaults
    gldemo_options opts = {
        .swapInterval = 1
    };

    int opt;
    while ((opt = getopt(argc, argv, "s:vhH")) != -1) {
        switch (opt) {
            case 'h':
            case 'H':
                printHelp(argv[0]);
                return EXIT_SUCCESS;
            case 'V':
                INFO(GLDEMO_NAME);
                return EXIT_SUCCESS;
            case 'v':
                debug = true;
                break;
            case 's':
                opts.swapInterval = atoi(optarg);
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
    opts.sceneArgc = argc - optind;
    opts.sceneArgv = malloc(sizeof(string) * opts.sceneArgc);
    if (!opts.sceneArgv) {
        FAIL("Could not allocate memory for arguments");
    }

    for (int i = 0; i < opts.sceneArgc; i++) {
        string s = str(argv[optind]);
        // We need this workaround because const members in structs can't be initialized
        memcpy(&opts.sceneArgv[i], &s, sizeof(string));

        DEBUG("Scene argument %d: %s", i, opts.sceneArgv[i].str);
    }

    gldemo(&opts);

    free(opts.sceneArgv);
    return EXIT_SUCCESS;
}
