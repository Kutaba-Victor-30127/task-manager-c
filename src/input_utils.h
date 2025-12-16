#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include "task.h"

int readIntInRange(const char *prompt, int min, int max);
int readPositiveInt(const char *prompt);
Date readDate(void);

#endif