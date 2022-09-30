#ifndef __INIT_H__
#define __INIT_H__
#include "exception.h"

void init();
void init_vector_table();
void init_exception_handlers();
void init_first_user_task();

#endif