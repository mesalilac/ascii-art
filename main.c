#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/fallback-font.h"

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        fprintf(stderr, "Missing message!\n");
        exit(1);
    }

    char *message = malloc(128 * sizeof(char));
    if (message == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for message!\n");
        exit(1);
    }

    // Parse args and extract the message
    for (int i = 1; i < argc; ++i)
    {
        strncpy(message, argv[i], strlen(argv[i]) + 1);
    }

    printf("%s\n", DEFAULT_FONT);

    return 0;
}
