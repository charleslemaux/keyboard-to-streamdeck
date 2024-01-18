#include <pthread.h>
#include "keyboards.h"

int main(int argc, char **argv)
{
    if (geteuid() != 0) {
        char sudo[]="/usr/bin/sudo";
        char pbin[]="./gl";
        execl(sudo,sudo,pbin,(char *)NULL);
    }

    pthread_t thread_id = create_kb_thread();

    pthread_join(thread_id, NULL);
    free_keyboards_array(&kb_array);
    exit(EXIT_SUCCESS);
}
