#ifndef OPENGL_CSFML_GL_H
#define OPENGL_CSFML_GL_H
#include <vulkan/vulkan.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/OpenGL.h>
enum Scenes {
    Menu,
    Sequel,
    MainScreen,
    Ending,
};
typedef struct {
    sfKeyCode key;
    sfRenderWindow* w;
    enum Scenes scene;
} Options;
void set_title(sfRenderWindow *w, enum Scenes s);
void window_manager(sfRenderWindow* w);
#endif //OPENGL_CSFML_GL_H
