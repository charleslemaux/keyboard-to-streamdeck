#include <libudev.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../includes/keyboards.h"

static Keyboards* create_keyboard(const char* dev_name, const char* dev_event_path, const char* dev_system_path) {
    Keyboards* kbd = malloc(sizeof(Keyboards));
    if (kbd == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    kbd->dev_name = malloc(strlen(dev_name) + 1);
    kbd->dev_event_path = malloc(strlen(dev_event_path) + 1);
    kbd->dev_system_path = malloc(strlen(dev_system_path) + 1);

    if (kbd->dev_name == NULL || kbd->dev_event_path == NULL || kbd->dev_system_path == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    strcpy(kbd->dev_name, dev_name);
    strcpy(kbd->dev_event_path, dev_event_path);
    strcpy(kbd->dev_system_path, dev_system_path);

    return kbd;
}

void free_keyboards(Keyboards* keyboards, int num_keyboards) {
    for (int i = 0; i < num_keyboards; ++i) {
        free(keyboards[i].dev_name);
        free(keyboards[i].dev_event_path);
        free(keyboards[i].dev_system_path);
    }
    free(keyboards);
}

void free_keyboards_array(KeyboardArray* kb_array)
{
    free_keyboards(kb_array->keyboards, kb_array->num_keyboards);
}

void read_keyboards(KeyboardArray* keyboard_array)
{
    for (int i = 0; i < keyboard_array->num_keyboards; ++i) {
        printf("Name: %s\n", keyboard_array->keyboards[i].dev_name);
        printf("Event Path: %s\n", keyboard_array->keyboards[i].dev_event_path);
        printf("System Path: %s\n\n", keyboard_array->keyboards[i].dev_system_path);
    }
}


static int extract_input_number(const char *syspath)
{
    const char *inputStr = "input";
    char *lastInput = strrchr(syspath, '/');
    if (lastInput != NULL) {
        lastInput = strstr(lastInput, inputStr);
        if (lastInput != NULL) {
            lastInput += strlen(inputStr);
            return atoi(lastInput);
        }
    }
    return (0);
}

static int is_keyboard_valid(const char *path)
{
    int fd = open(path, O_RDONLY|O_NONBLOCK);
    if (fd < 0) {
        return (0);
    }
    return (1);
}

static char* get_kb_evt_path_by_syspath(const char* syspath){
    char* path = malloc(256 * sizeof(char));
    if (path == NULL) {
        return NULL;
    }
    int event_nb = extract_input_number(syspath);
    snprintf(path, 256, "/dev/input/event%d", event_nb);
    return path;
}

KeyboardArray get_keyboards() {
    struct udev *udev = udev_new();
    if (!udev) {
        printf("Failed to create udev\n");
        exit(1);
    }

    struct udev_enumerate *enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "input");
    udev_enumerate_scan_devices(enumerate);

    struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
    struct udev_list_entry *entry;

    Keyboards* keyboards = NULL;
    int num_keyboards = 0;

    udev_list_entry_foreach(entry, devices) {
        const char *path = udev_list_entry_get_name(entry);
        struct udev_device *dev = udev_device_new_from_syspath(udev, path);
        const char *device_type = udev_device_get_property_value(dev, "ID_INPUT_KEYBOARD");
        const char *name = udev_device_get_property_value(dev, "NAME");
        if (device_type != NULL && strcmp(device_type, "1") == 0 && name != NULL) {
            if (is_keyboard_valid(get_kb_evt_path_by_syspath(udev_device_get_syspath(dev)))) {
                keyboards = realloc(keyboards, (num_keyboards + 1) * sizeof(Keyboards));
                if (keyboards == NULL) {
                    printf("Memory allocation failed.\n");
                    exit(1);
                }
                keyboards[num_keyboards] = *create_keyboard(
                        name,
                        get_kb_evt_path_by_syspath(udev_device_get_syspath(dev)),
                        udev_device_get_syspath(dev));
                num_keyboards++;
            }
        }
        udev_device_unref(dev);
    }

    KeyboardArray keyboards_array = {keyboards, num_keyboards};

    udev_enumerate_unref(enumerate);
    udev_unref(udev);

    return keyboards_array;
}