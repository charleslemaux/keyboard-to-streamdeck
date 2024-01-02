#include "../includes/gl.h"

sfText* kbList = NULL;
sfFloatRect bounds = {0};
KeyboardArray kb_array;

//FPS SPECIFIC
sfClock* gClock;
sfTime gTime;
sfText* fpsText;
static char* fpsToString(double fps){static char str[50];sprintf(str, "FPS: %.1f", fps);return str;}
static void draw_fps_counter(sfRenderWindow *w)
{
    gTime = sfClock_getElapsedTime(gClock);
    double fps = 1.0 / sfTime_asSeconds(gTime);

    sfText_setString(fpsText, fpsToString(fps));
    sfRenderWindow_drawText(w, fpsText, NULL);
    sfClock_restart(gClock);
}
//FPS SPECIFIC

static void draw_kb_menu(sfRenderWindow *w)
{
    float totalHeight = bounds.height * (float)kb_array.num_keyboards;
    float startY = ((float)gSize.y / 2.0f) - (totalHeight / 2.0f);

    for (int i = 0; i < kb_array.num_keyboards; i++) {
        sfText_setPosition(kbList, (sfVector2f){20, (startY + (bounds.height + (float)i * 30))});
        sfText_setString(kbList, kb_array.keyboards[i].dev_name);
        sfRenderWindow_drawText(w, kbList, NULL);
    }
}

void init_menu_ui(void)
{
    kb_array = get_keyboards();
    read_keyboards(&kb_array);
    kbList = create_text("", sfBlack);

    //FPS SPECIFIC
    gClock = sfClock_create();
    fpsText = create_text("", sfBlack);
    //FPS SPECIFIC
}

void menu_ui_renderer(sfRenderWindow* w)
{
    bounds = sfText_getLocalBounds(kbList);
    draw_fps_counter(w);
    draw_kb_menu(w);
}
