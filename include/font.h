#define MAX_FONT_CHARS 95
#define MAX_CHAR_LINES 7
#define MAX_LINE_WIDTH 7

#define DEBUG 1

typedef struct
{
    char ch;
    char **lines;
    int lines_index;
} Char;

typedef struct
{
    Char **chars;
    int chars_index;
} Font;

void font_parse_text(Font *font, char *data);
void font_free_all(Font *font);
void font_debug_info(Font *font);
