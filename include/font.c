/*
    in Font struct store each chars longest line
*/

typedef struct {
    char line[];
    int max_len;
} Char;

typedef struct {
    Char *chars[95];
} Font;

void parse_font(Font *font, char *font_file_text)
{
}
