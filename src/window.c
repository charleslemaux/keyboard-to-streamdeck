#include "../includes/san-francisco.h"
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

static void draw_button(sfRenderWindow *w, float scale, const char* text)
{
    sfRectangleShape* rect = sfRectangleShape_create();
    sfVector2u windowSize = sfRenderWindow_getSize(w);
    sfVector2f size = {100 * scale, 50 * scale};
    sfRectangleShape_setSize(rect, size);
    sfRectangleShape_setFillColor(rect, sfColor_fromRGB(255, 211, 211));
    sfRectangleShape_setPosition(rect, (sfVector2f){((float)windowSize.x - size.x) / 2, ((float)windowSize.y - size.y) / 2});

    sfFont* font = sfFont_createFromMemory((void *)SFNSDisplay_Regular_otf, SFNSDisplay_Regular_otf_len);
    sfText* buttonText = sfText_create();
    sfText_setFont(buttonText, font);
    sfText_setString(buttonText, text);
    sfText_setCharacterSize(buttonText, (unsigned int)(20 * scale));



    sfFloatRect textBounds = sfText_getLocalBounds(buttonText);
    sfFloatRect buttonBounds = sfRectangleShape_getGlobalBounds(rect);
    sfVector2f textPos;
    textPos.x = buttonBounds.left + (buttonBounds.width - textBounds.width) / 2;
    textPos.y = buttonBounds.top + (buttonBounds.height - (textBounds.height + textBounds.top - textBounds.top)) / 2;
    sfText_setPosition(buttonText, textPos);

    sfRenderWindow_drawRectangleShape(w, rect, NULL);
    sfRenderWindow_drawText(w, buttonText, NULL);

    sfText_destroy(buttonText);
    sfFont_destroy(font);
    sfRectangleShape_destroy(rect);
}

void window_manager(sfRenderWindow* w)
{
    sfRenderWindow_clear(w, sfWhite);
    draw_button(w, 1.f, "Test !");
    sfRenderWindow_display(w);
}
