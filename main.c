#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/font.h"

#define SIZEOF_FONT_FILE 5128

int main(int argc, char **argv)
{
    char *message = malloc(128 * sizeof(char));
    if (message == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for message!\n");
        exit(1);
    }
    char *font_file = malloc(64 * sizeof(char));
    if (font_file == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for font file!\n");
        exit(1);
    }

    if (argc >= 3)
    {
        strncpy(font_file, argv[1], strlen(argv[1]) + 1);
        strncpy(message, argv[2], strlen(argv[2]) + 1);
    }
    else
    {
        fprintf(stderr, "Missing <font-file>, and <message>!\n");
        fprintf(stderr, "Usage: %s <font-file> <message>\n", argv[0]);
        exit(1);
    }

    FILE *font_file_handle = fopen(font_file, "r");
    if (font_file_handle == NULL)
    {
        fprintf(stderr, "Failed to open font file! '%s'\n", font_file);
        exit(1);
    }

    char *data = malloc(SIZEOF_FONT_FILE * sizeof(char));
    if (data == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for data\n");
        exit(1);
    }

    fread(data, sizeof(char), SIZEOF_FONT_FILE, font_file_handle);
    fclose(font_file_handle);

    Font *font = malloc(sizeof(Font));
    if (font == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for font\n");
        exit(1);
    }

    font->chars = malloc(MAX_FONT_CHARS * sizeof(Char));
    if (font->chars == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for font chars\n");
        exit(1);
    }

    font->chars_index = 0;

    font_parse_text(font, data);
    font_debug_info(font);

    font_free_all(font);
    free(message);
    free(font_file);
    free(data);
}
