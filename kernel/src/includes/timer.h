#pragma once
#include "stdio.h"
#include "stdint.h"
#include "io.h"
#include "irq.h"

void init_timer();
int second();
void sleep(int ticks);