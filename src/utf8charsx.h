#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define UTF8CHARSX_DEFAULT_SIZE 8
#define UTF8CHARSX_MAX_BYTES_PER_ONE_CHAR 5

#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) printf(fmt, __VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif

typedef struct {
    uint8_t** chars;
    uint32_t length;
} Utf8chars, *Utf8chars_t;

Utf8chars new_utf8chars(const char*);
uint32_t release_utf8chars(Utf8chars_t);
uint32_t replace_utf8chars(Utf8chars_t, uint32_t idx, const char*);
