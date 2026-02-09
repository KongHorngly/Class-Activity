
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "common.h"

int main() {
    mqd_t mq;
    struct mq_attr attr;
    const char *message = "Hello from sender!";

    /* Define queue attributes */
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;           // Max messages in queue
    attr.mq_msgsize = MAX_SIZE;    // Max size of each message
    attr.mq_curmsgs = 0;

    /* Create and open the message queue */
    /* O_CREAT: Create if it doesn't exist, O_WRONLY: Write only */
    mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0644, &attr);

    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    /* Send the message */
    /* We add +1 to strlen to include the null terminator '\0' */
    if (mq_send(mq, message, strlen(message) + 1, 0) == -1) {
        perror("mq_send");
        exit(EXIT_FAILURE);
    }

    printf("Sender: Message sent successfully: \"%s\"\n", message);

    /* Close the queue handle */
    mq_close(mq);

    return 0;
}