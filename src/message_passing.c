#include "message_passing.h"
#include "printf.h"
#include "task.h"
#include "utilities.h"
#include "task_scheduler.h"

bool register_sender(Task *receiver, Task *sender) {
    return push_queue(&receiver->senders, sender->tid);
}

int next_sender(Task *receiver) {
    return pop_queue(&receiver->senders);
}

SendArgs *get_send_args(Task *task) {
    return (SendArgs*) task->x;
}

ReceiveArgs *get_receive_args(Task *task) {
    return (ReceiveArgs*) task->x;
}

ReplyArgs *get_reply_args(Task *task) {
    return (ReplyArgs*) task->x;
}

int copy_message(const char *msg_from, int len_msg_from, char *msg_to, int len_msg_to) {
    int actual_len = (len_msg_from < len_msg_to) ? len_msg_from : len_msg_to;
    memcpy(msg_to, msg_from, actual_len);
    return actual_len;
}

void synchronized_send_receive(Task *sender, const char *msg_from, int len_msg_from, Task *receiver, char *msg_to,
                              int len_msg_to) {
    if (sender == NULL || receiver == NULL) {
        printf("Assertion: Sender | Receiver cannot be NULL\r\n");
        return;
    }

//    if (receiver->state == Ready) {
//        printf("Assertion: State of receiver cannot be Ready\r\n");
//        return;
//    }

//    *get_receive_args(receiver)->tid = sender->tid;

    int actual_len = copy_message(msg_from, len_msg_from, msg_to, len_msg_to);
    return_to(receiver, actual_len);

    receiver->state = Ready;
}


void sys_send() {
    Task *sender = get_current_task();
    SendArgs* args = get_send_args(sender);
    Task *receiver = task_queue_get(args->tid);

    if (receiver == NULL) {
        printf("Receiver tid not found\r\n");
        return_to(sender, -1);
        return;
    }

    if (receiver->state == WaitReceive) {
        ReceiveArgs *receive_args = get_receive_args(receiver);

        *receive_args->tid = sender->tid;
        synchronized_send_receive(sender, args->msg, args->msg_len, receiver, receive_args->msg, receive_args->msg_len);
        // block sender
        sender->state = WaitReply;
    } else {
        bool success = register_sender(receiver, sender);
        if (success) {
            // block sender
            sender->state = WaitSend;
        } else {
            printf("Fail to register as sender to receiver(tid:%d)\r\n", receiver->tid);
            return_to(sender, -2);
        }
    }
}

/** make the return value of Receive be -1 if the sender terminated before receiving **/
void sys_receive() {
    Task *receiver = get_current_task();
    ReceiveArgs *args = get_receive_args(receiver);

    if (is_empty(&receiver->senders)) {
        printf("sender queue is empty, block receiver\r\n");
        receiver->state = WaitReceive;
        return;
    }

    int sender_id = next_sender(receiver);
    Task *sender = task_queue_get(sender_id);
    if (sender == NULL) {
        printf("Sender tid: %d is invalid", sender_id);
        return_to(receiver, -1);
        return;
    }

    SendArgs *send_args = get_send_args(sender);
    *args->tid = sender->tid;
    synchronized_send_receive(sender, send_args->msg, send_args->msg_len, receiver, args->msg, args->msg_len);

    sender->state = WaitReply;
}

void sys_reply() {
    Task* receiver = get_current_task();
    ReplyArgs *args = get_reply_args(receiver);

    Task *sender = task_queue_get(args->tid);

    if (sender == NULL) {
        printf("Sender tid: %d is invalid", sender_id);
        return_to(receiver, -1);
        return;
    }

    SendArgs *send_args = get_send_args(sender);
    synchronized_send_receive(receiver, args->reply, args->reply_len, sender, send_args->reply, send_args->reply_len);
}