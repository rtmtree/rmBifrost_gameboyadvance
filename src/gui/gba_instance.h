
#ifndef GBA_INSTANCE_H
#define GBA_INSTANCE_H

#include "gba_emu/gba_emu.h"
#include "../../external/lvgl/lvgl.h"
#include "port/port.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define GBA_EMU_PREFIX "gba_emu: "

#define OPTARG_TO_VALUE(value, type, base)                                  \
    do {                                                                    \
        char* ptr;                                                          \
        (value) = (type)strtoul(optarg, &ptr, (base));                      \
        if (*ptr != '\0') {                                                 \
            printf(GBA_EMU_PREFIX "Parameter error: -%c %s\n", ch, optarg); \
            show_usage(argv[0], EXIT_FAILURE);                              \
        }                                                                   \
    } while (0)

typedef struct
{
    const char* file_path;
    lv_gba_view_mode_t mode;
    int volume;
} gba_emu_param_t;

static void show_usage(const char* progname, int exitcode)
{
    printf("\nUsage: %s"
           " -f <string> -m <decimal-value> -m <decimal-value> -h\n",
        progname);
    printf("\nWhere:\n");
    printf("  -f <string> rom file path.\n");
    printf("  -m <decimal-value> view mode: "
           "0: simple; 1: virtual keypad.\n");
    printf("  -v <decimal-value> set volume: 0 ~ 100.\n");
    printf("  -h help.\n");

    exit(exitcode);
}

void start_gba(void);

#endif // GBA_INSTANCE_H
