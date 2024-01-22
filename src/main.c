#include "../includes/keyboards.h"

KeyboardArray kb_array;

int main(int argc, char **argv)
{
    if (geteuid() != 0) {
        printf("You must run this program as root.\n");
        exit(EXIT_FAILURE);
    }

    kb_array = get_keyboards();
    read_keyboards(&kb_array);

    int input = 0;
    printf("Select the keyboard you want to listen to: ");
    scanf("%d", &input);
    if (input > kb_array.num_keyboards || input < 0) {
        printf("Invalid input.\n");
        exit(EXIT_FAILURE);
    }

    pthread_t thread_id = create_kb_thread(kb_array.keyboards[input].dev_event_path);

    pthread_join(thread_id, NULL);
    free_keyboards_array(&kb_array);
    exit(EXIT_SUCCESS);
}
