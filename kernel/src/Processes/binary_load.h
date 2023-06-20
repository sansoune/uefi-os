#pragma once


void load_flat_binary_at (char* code, int code_len, void* memloc);
void run_flat_binary (void* memloc);