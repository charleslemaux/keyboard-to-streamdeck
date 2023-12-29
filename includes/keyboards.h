#ifndef OPENGL_CSFML_KEYBOARDS_H
#define OPENGL_CSFML_KEYBOARDS_H
#include <fcntl.h>
typedef struct {
    char *dev_name;
    char *dev_event_path;
    char *dev_system_path;
} Keyboards;
typedef struct {
  Keyboards* keyboards;
  int num_keyboards;
} KeyboardArray ;
KeyboardArray get_keyboards(void);
Keyboards* create_keyboard(const char* dev_name, const char* dev_event_path, const char* dev_system_path);
void read_keyboards(KeyboardArray* keyboard_array);
void free_keyboards_array(KeyboardArray* kb_array);
void free_keyboards(Keyboards* keyboards, int num_keyboards);
#endif //OPENGL_CSFML_KEYBOARDS_H
