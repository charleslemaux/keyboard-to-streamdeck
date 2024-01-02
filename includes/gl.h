#ifndef OPENGL_CSFML_GL_H
#define OPENGL_CSFML_GL_H
#include <vulkan/vulkan.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/OpenGL.h>
#include "keyboards.h"
#include <stdbool.h>

enum Scenes {
    Menu,
    Sequel,
    MainScreen,
    Ending,
};
typedef struct {
    sfKeyCode key;
    sfRenderWindow* window;
    enum Scenes scene;
    short chosen_kb;
} Options;
extern Options opts;

//CSMFL Functions
void init_smfl(sfRenderWindow* w);
void set_title(sfRenderWindow *w, enum Scenes s);
void update_view(unsigned int w, unsigned int h);
sfText *create_text(const char *textStr, sfColor color);
void window_manager(sfRenderWindow* w);

//CSFML Globals
extern sfFont* gFont;
extern sfVector2u gSize;

//Menu UI
void init_menu_ui(void);
void menu_ui_renderer(sfRenderWindow *w);

#endif //OPENGL_CSFML_GL_H
