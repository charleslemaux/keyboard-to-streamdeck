#include <libudev.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int extractInputNumber(const char *syspath)
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

static int is_keyboard_valid(const char *c) //TODO : refactor this function
{
    char full_path[256];
    int event_nb = extractInputNumber(c);
    snprintf(full_path, sizeof(full_path), "%s%d\n", "/dev/input/event", event_nb);

    printf("%s\n", full_path);
    FILE *file = fopen(full_path, "r");
    if (file){
        printf("VALID\n");
        fclose(file);
        return (1);
    } else {
        printf("INVALID\n");
        return (0);
    }
}

int get_keyboards() {
    struct udev *udev = udev_new();
    if (!udev) {
        printf("Failed to create udev\n");
        return (1);
    }

    struct udev_enumerate *enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "input");
    udev_enumerate_scan_devices(enumerate);

    struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
    struct udev_list_entry *entry;

    udev_list_entry_foreach(entry, devices) {
        const char *path = udev_list_entry_get_name(entry);
        struct udev_device *dev = udev_device_new_from_syspath(udev, path);
        const char *devtype = udev_device_get_property_value(dev, "ID_INPUT_KEYBOARD");
        const char *name = udev_device_get_property_value(dev, "NAME");
        if (devtype != NULL && strcmp(devtype, "1") == 0 && name != NULL) {
            //printf("Keyboard device: %s\n", udev_device_get_syspath(dev));
            //printf("Keyboard name: %s\n", udev_device_get_property_value(dev, "NAME"));
            if (is_keyboard_valid(udev_device_get_syspath(dev)))
                printf("VALID\n");
            // TODO : Store the keyboard device information as needed
        }
        udev_device_unref(dev);
    }
    udev_enumerate_unref(enumerate);
    udev_unref(udev);

    return (0);
}