#ifndef OPENGL_CSFML_GL_H
#define OPENGL_CSFML_GL_H
#include <vulkan/vulkan.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/OpenGL.h>
#include "keyboards.h"

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
void set_title(sfRenderWindow *w, enum Scenes s);
void window_manager(sfRenderWindow* w, KeyboardArray* kb_array);

//Menu UI
void menu_ui_renderer(sfRenderWindow *w, KeyboardArray* kb_array);
void init_menu_ui(void);

#endif //OPENGL_CSFML_GL_H
