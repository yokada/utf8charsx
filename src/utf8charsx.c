#include "utf8charsx.h"


Utf8chars new_utf8chars(const char* str) {
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t k = 0;
    uint32_t mem = UTF8CHARSX_DEFAULT_SIZE;

    uint8_t **c = (uint8_t**)malloc(sizeof(uint8_t*) * mem);
    for (uint32_t h=0;h<mem; h++) {
        c[h] = NULL;
    }

    while (*str != '\0') {
        if (c[i] == NULL) {
            c[i] = malloc(sizeof(uint8_t) * UTF8CHARSX_MAX_BYTES_PER_ONE_CHAR);
        }

        if (*str == 0x0a || *str == 0x0d || (*str & 0x80) == 0) {
            DEBUG_PRINT("Newline or 1-byte char str=0x%x\n", *str);
            k=0;
            c[i][j] = *str;
        } else if ((*str & 0xf0) == 0xf0) {
            DEBUG_PRINT("4-bytes char, first byte str=0x%x\n", *str);
            k=3;
            c[i][j] = *str;
            j++;
        } else if ((*str & 0xf0) == 0xe0) {
            DEBUG_PRINT("3-bytes char, first byte str=0x%x\n", *str);
            k=2;
            c[i][j] = *str;
            j++;
        } else if ((*str & 0xc0) == 0x80) {
            DEBUG_PRINT("N-bytes char, second bytes or more str=0x%x\n", *str);
            k--;
            c[i][j] = *str;
            j++;
        } else {
            DEBUG_PRINT("invalid byte %x\n", *str);
        }

        if (k==0) {
            c[i][j+1] = '\0';
            DEBUG_PRINT("--------- UTF8 char c[%d]=%s\n", i, c[i]);
            i++;
            j=0;

            if (i >= mem) {
                DEBUG_PRINT("    Increase memory of chars array using UTF8CHARSX_DEFAULT_SIZE:%d, current mem=%i\n", UTF8CHARSX_DEFAULT_SIZE, mem);
                mem += UTF8CHARSX_DEFAULT_SIZE;

                // the following code raises an error when it is going to free:
                //c = (uint8_t**)realloc(c, mem);

                // as below, you do instead:
                c = (uint8_t**)realloc(c, sizeof(uint8_t*) * mem);

                for (uint32_t l=i;l<mem;l++) {
                    c[l] = NULL;
                }
            }

        }

        str++;
    }

    Utf8chars chars;
    chars.chars = c;
    chars.length = i;

    return chars;
}

/**
 * @return 0 or more positive unsigned integer
 *   0 = succeed
 *   0 < error
 */
uint32_t release_utf8chars(Utf8chars_t utf8chars) {
    if (utf8chars->chars == NULL) {
        return 0;
    }

    uint32_t len = utf8chars->length;
    uint32_t i = 0;
    while(i < utf8chars->length) {
        DEBUG_PRINT("would free: %i, %s\n", i, utf8chars->chars[i]);
        free(utf8chars->chars[i]);
        i++;
    }
    free(utf8chars->chars);
    return len - i;
}

uint32_t replace_utf8chars(Utf8chars_t utf8chars, uint32_t idx, const char* ch) {
    memcpy(utf8chars->chars[idx], ch, UTF8CHARSX_MAX_BYTES_PER_ONE_CHAR);
    return 0;
}
