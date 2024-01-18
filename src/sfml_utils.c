#include "../includes/gl.h"
#include "../includes/san-francisco.h"

sfFont* gFont = NULL;
sfSprite * gSprite = NULL;
sfVector2u gSize = {0};

sfText *create_text(const char *textStr, sfColor color)
{
    sfText* text = sfText_create();
    sfText_setFont(text, gFont);
    sfText_setString(text, textStr);
    sfText_setCharacterSize(text, (unsigned int)(20));
    sfText_setFillColor(text, color);

    return text;
}

void update_view(unsigned int w, unsigned int h)
{
    sfView *view = sfView_createFromRect((sfFloatRect) {0, 0, (float)w, (float)h});
    sfRenderWindow_setView(opts.window, view);
    sfView_destroy(view);
}

void init_smfl(sfRenderWindow* w)
{
    gSprite = sfSprite_create();
    gFont = sfFont_createFromMemory((void *)SFNSDisplay_Regular_otf, SFNSDisplay_Regular_otf_len);
    if (!gFont)
        exit(EXIT_FAILURE);
    gSize = sfRenderWindow_getSize(w);

    init_menu_ui();
}
