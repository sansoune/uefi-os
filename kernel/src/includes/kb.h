#pragma once 
#include "stdint.h"
#include "stdio.h"
#include "pic.h"
#include "irq.h"
#include "string.h"

extern bool status;
void init_kb();
void curretnPos();
void clean_buffer();
char* readStr();