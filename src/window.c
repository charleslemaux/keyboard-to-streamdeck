#include "../includes/gl.h"
#include <stdlib.h>
#include <string.h>

const char* ScenesNames[] = {
        "Menu",
        "Sequel",
        "MainScreen",
        "Ending",
};

void set_title(sfRenderWindow *w, enum Scenes s)
{
    int i = 17;
    char *title = (char *)malloc(25  * sizeof(char));
    title[24] = '\0';

    strcpy(title, "OpenGL x CSFML - ");
    strcat(title, ScenesNames[s]);

    sfRenderWindow_setTitle(w, title);
    free(title);
}

void window_manager(sfRenderWindow* w)
{
    sfRenderWindow_clear(w, sfWhite);
    sfRenderWindow_display(w);
}
