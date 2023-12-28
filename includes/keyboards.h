#ifndef OPENGL_CSFML_KEYBOARDS_H
#define OPENGL_CSFML_KEYBOARDS_H
int get_keyboards(void);
typedef struct {
    int nb;
    char *dev_name;
    char *dev_event_path;
    char *dev_system_path;
} Keyboards;
#endif //OPENGL_CSFML_KEYBOARDS_H
