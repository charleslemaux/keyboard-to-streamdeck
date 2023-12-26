#ifndef GL
	#define GL
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
#endif
