#include "../includes/gl.h"
#include <stdlib.h>
#include <string.h>

static enum Scenes s;

const char* ScenesNames[] = {
        "Menu",
        "Sequel",
        "MainScreen",
        "Ending",
};

void set_title(sfRenderWindow *w, enum Scenes scene)
{
    s = scene;
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
    switch (opts.scene) {
        case Menu:
            menu_ui_renderer(w);
            break;
        case Sequel:
            break;
        case MainScreen:
            break;
        case Ending:
            break;
    }
    sfRenderWindow_display(w);
}
