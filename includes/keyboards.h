#ifndef OPENGL_CSFML_KEYBOARDS_H
#define OPENGL_CSFML_KEYBOARDS_H
#include <fcntl.h>
#include <libudev.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <libevdev/libevdev.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
    char *dev_name;
    char *dev_event_path;
    char *dev_system_path;
} Keyboards;

typedef struct {
  Keyboards* keyboards;
  int num_keyboards;
} KeyboardArray ;

//Creation
extern KeyboardArray kb_array;
KeyboardArray get_keyboards(void);
Keyboards* create_keyboard(const char* dev_name, const char* dev_event_path, const char* dev_system_path);
pthread_t create_kb_thread();

//Utils
void read_keyboards(KeyboardArray* keyboard_array);
void free_keyboards_array(KeyboardArray* kb_array);
void free_keyboards(Keyboards* keyboards, int num_keyboards);

//Most important
void* keyboard_listen(void *arg);

#endif //OPENGL_CSFML_KEYBOARDS_H
