/*
    in Font struct store each chars longest line
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "font.h"

char *collect_word(char *data, int *cursor)
{
    char *word = malloc(128 * sizeof(char));
    if (word == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for word\n");
        exit(1);
    }

    int i = 0;
    while (data[*cursor] != ' ' && data[*cursor] != '\0' &&
           data[*cursor] != '\n')
    {
        word[i] = data[*cursor];
        i++;
        *cursor += 1;
    }
    word[i] = '\0';
    return word;
}

void handle_declaration(Font *font, int *cursor, char *data)
{
    while (data[*cursor] == ' ' || data[*cursor] == '\n')
        (*cursor)++;

    Char *font_char = malloc(sizeof(Char));
    if (font_char == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for font char\n");
        exit(1);
    }

    font_char->lines = malloc(MAX_CHAR_LINES * sizeof(char *));
    if (font_char->lines == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for font char lines\n");
        exit(1);
    }
    font_char->lines_index = 0;
    font_char->ch          = data[(*cursor)++];

    while (data[*cursor] == '\n')
        (*cursor)++;

    while (data[*cursor] != '$' && data[*cursor] != '\0')
    {
        char *temp_string = malloc(32 * sizeof(char));
        if (temp_string == NULL)
        {
            fprintf(stderr, "Failed to allocate memory for temp_string\n");
            exit(1);
        }
        int temp_string_len = 0;

        while (data[*cursor] != '\n' && data[*cursor] != '$' &&
               data[*cursor] != '\0')
        {
            temp_string[temp_string_len++] = data[(*cursor)++];
        }
        temp_string[temp_string_len] = '\0';

        if (strncmp(temp_string, "@INSERT_EMPTY_SPACE", 20) == 0)
        {
            char *line     = malloc(MAX_LINE_WIDTH * sizeof(char));
            int line_count = 0;

            for (int i = 0; i < MAX_LINE_WIDTH; ++i)
            {
                line[line_count++] = ' ';
            }
            line[line_count] = '\0';

            font_char->lines[font_char->lines_index++] = line;
        }
        else
        {
            int missing_empty_space = MAX_LINE_WIDTH - temp_string_len;

            for (int i = 0; i < missing_empty_space; ++i)
            {
                temp_string[temp_string_len++] = ' ';
            }
            temp_string[temp_string_len] = '\0';

            char *line = malloc(sizeof(temp_string));

            strncpy(line, temp_string, strlen(temp_string) + 1);

            font_char->lines[font_char->lines_index++] = line;
        }

        free(temp_string);

        if (data[*cursor] == '\n')
            (*cursor)++;
    }

    if (MAX_CHAR_LINES - font_char->lines_index > 0)
    {
        int missing_lines = MAX_CHAR_LINES - font_char->lines_index;
        for (int i = 0; i < missing_lines; ++i)
        {
            char *temp_string = malloc((MAX_LINE_WIDTH + 1) * sizeof(char));
            int index         = 0;

            for (int j = 0; j < MAX_LINE_WIDTH; ++j)
            {
                temp_string[index++] = ' ';
            }
            temp_string[index] = '\0';

            char *line = malloc(sizeof(temp_string));
            strncpy(line, temp_string, strlen(temp_string) + 1);

            font_char->lines[font_char->lines_index++] = line;

            free(temp_string);
        }
    }

    font->chars[font->chars_index++] = font_char;
}

void font_parse_insert_empty_space_char(Font *font)
{
    Char *font_char        = malloc(sizeof(Char));
    font_char->ch          = ' ';
    font_char->lines_index = 0;
    font_char->lines       = malloc(MAX_CHAR_LINES * sizeof(char *));
    if (font_char->lines == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for font char lines\n");
        exit(1);
    }

    // lines
    for (int i = 0; i < MAX_CHAR_LINES; ++i)
    {
        char *temp_string = malloc((MAX_LINE_WIDTH + 1) * sizeof(char));
        int index         = 0;

        for (int j = 0; j < MAX_LINE_WIDTH; ++j)
        {
            temp_string[index++] = ' ';
        }
        temp_string[index] = '\0';

        char *line = malloc(sizeof(temp_string));
        strncpy(line, temp_string, strlen(temp_string) + 1);

        font_char->lines[font_char->lines_index++] = line;

        free(temp_string);
    }

    font->chars[font->chars_index++] = font_char;
}

void font_parse_text(Font *font, char *data)
{
    int cursor = 0;

    while (data[cursor] != '\0')
    {
        while (data[cursor] == '$')
        {
            char *action = collect_word(data, &cursor);

            if (strncmp(action, "$DECLARATION", 13) == 0)
            {
                handle_declaration(font, &cursor, data);
            }

            free(action);
        }

        cursor++;
    }

    font_parse_insert_empty_space_char(font);
}

void font_free_all(Font *font)
{
    for (int i = 0; i < font->chars_index; ++i)
    {
        for (int j = 0; j < font->chars[i]->lines_index; ++j)
        {
            free(font->chars[i]->lines[j]);
        }
        free(font->chars[i]->lines);
        free(font->chars[i]);
    }
    free(font->chars);
    free(font);
}

void font_debug_info(Font *font)
{
    if (DEBUG == 0)
    {
        return;
    }

    printf("#################### DEBUG INFO ####################\n");
    printf("chars list:\n");

    for (int i = 0; i < font->chars_index; ++i)
    {
        printf(
            "\t-> '%c' [lines_count: %i]\n",
            font->chars[i]->ch,
            font->chars[i]->lines_index
        );

        for (int j = 0; j < font->chars[i]->lines_index; ++j)
        {
            printf("\t'%s'\n", font->chars[i]->lines[j]);
        }
    }

    printf("\n");
    printf("chars_count: %i\n", font->chars_index);
    printf("#################### DEBUG INFO ####################\n");
}
