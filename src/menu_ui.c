#include "../includes/gl.h"
#include "../includes/san-francisco.h"

sfFont* gFont = NULL;
sfText* kbList = NULL;
sfText* buttonText = NULL;

static void draw_kb_menu(sfRenderWindow *w, KeyboardArray* kb_array)
{
    for (int i = 0; i < kb_array->num_keyboards; i++) {
        sfText_setPosition(kbList, (sfVector2f){20, (float)(50 + i * 30)});
        sfText_setString(kbList, kb_array->keyboards[i].dev_name);
        sfRenderWindow_drawText(w, kbList, NULL);
    }
}

static void draw_close_button(sfRenderWindow* window, float scale) {
    sfVector2u windowSize = sfRenderWindow_getSize(window);
    sfVector2f size = {50 * scale, 50 * scale};
    sfVector2f pos = {(float)windowSize.x - size.x, (float)windowSize.y - size.y};

    sfVertexArray* lines = sfVertexArray_create();
    sfVertexArray_resize(lines, 4);

    sfVertex line1 = {pos, sfColor_fromRGB(255, 0, 0)};
    sfVertex line2 = {pos.x + size.x, pos.y + size.y, sfColor_fromRGB(255, 0, 0)};
    sfVertex line3 = {pos.x, pos.y + size.y, sfColor_fromRGB(255, 0, 0)};
    sfVertex line4 = {pos.x + size.x, pos.y, sfColor_fromRGB(255, 0, 0)};

    sfVertexArray_setPrimitiveType(lines, sfLinesStrip);
    sfVertexArray_append(lines, line1);
    sfVertexArray_append(lines, line2);
    sfVertexArray_append(lines, line3);
    sfVertexArray_append(lines, line4);

    sfRenderWindow_drawVertexArray(window, lines, NULL);

    sfVertexArray_destroy(lines);
}

void init_menu_ui(void)
{
    gFont = sfFont_createFromMemory((void *)SFNSDisplay_Regular_otf, SFNSDisplay_Regular_otf_len);
    kbList = sfText_create();
    sfText_setFont(kbList, gFont);
    sfText_setCharacterSize(kbList, (unsigned int)(20));
}

void menu_ui_renderer(sfRenderWindow* w, KeyboardArray* kb_array)
{
    draw_kb_menu(w, kb_array);
    draw_close_button(w, 1.f);
}
