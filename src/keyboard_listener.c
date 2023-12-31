#include "../includes/keyboards.h"
#include <stdbool.h>

static int file_descriptor_check(const char* path)
{
    int fd = open(path, O_RDONLY|O_NONBLOCK);
    if (fd < 0) {
        perror("Failed to open the input device");
        exit(EXIT_FAILURE);
    } else {
        return fd;
    }
}

static bool input_checker(struct input_event* ev) {
    printf("%u pressed\n", (unsigned int) ev->code);
    switch (ev->code) {
        case KEY_SPACE:
            printf("Spacebar pressed\n");
            break;
        case KEY_X:
            printf("X pressed\n");
            break;
        case KEY_TAB:
            return false;
    }
    return true;
}

static void init_device(int fd, struct libevdev **dev) {
    int rc = libevdev_new_from_fd(fd, dev);
    if (rc < 0) {
        perror("Failed to init libevdev");
        exit(EXIT_FAILURE);
    }
}
static void grab_keyboard(int fd) {
    if (ioctl(fd, EVIOCGRAB, 1) == -1) {
        perror("Failed to grab the keyboard_listen");
        exit(EXIT_FAILURE);
    }
}
static void event_listener(int fd, struct libevdev *dev, bool *can_listen) {
    struct input_event ev;
    fd_set set;
    struct timeval timeout;

    while(*can_listen) {
        FD_ZERO(&set);
        FD_SET(fd, &set);

        timeout.tv_sec = 0;
        timeout.tv_usec = 10000; // 10ms

        int rc = select(fd + 1, &set, NULL, NULL, &timeout);
        if (rc > 0) {
            rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
            if (rc == 0 && ev.type == EV_KEY && ev.value == 1) {
                *can_listen = input_checker(&ev);
            }
        } else if (rc < 0) {
            perror("select() failed");
            exit(EXIT_FAILURE);
        }
        usleep(1000); // 1ms
    }
}
static void releaseKeyboard(int fd) {
    ioctl(fd, EVIOCGRAB, 0);
}
static void freeResources(struct libevdev *dev, int fd) {
    libevdev_free(dev);
    close(fd);
}
void* keyboard_listen(void *arg) {
    char *path = (char *)arg;
    struct libevdev *dev = NULL;
    int fd = file_descriptor_check(path);
    bool can_listen = true;

    init_device(fd, &dev);
    grab_keyboard(fd);
    event_listener(fd, dev, &can_listen);
    releaseKeyboard(fd);
    freeResources(dev, fd);

    pthread_exit(NULL);
}
