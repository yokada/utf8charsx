#include "../src/utf8charsx.h"

/**
 * $ cd path/to/utf8charsx/test
 * $ gcc -DDEBUG -Wall -Werror -o utf8charsx-test utf8charsx-test.c ../src/utf8charsx.c; ./utf8charsx-test
 */

void test1(const char* test) {
    // as utf8 literal always uses const char*.
    // the string as bytes uses uint8_t* instead.
    Utf8chars utf8chars = new_utf8chars(test);
    printf("utf8chars.length=%i\n", utf8chars.length);

    const char* u = u8"u";
    const char* ri = u8"リ";
    const char* emp = u8"";
    printf("strcmp:%i\n", strncmp((const char*)utf8chars.chars[0], u, 5));
    printf("strcmp:%i\n", strncmp((const char*)utf8chars.chars[4], ri, 5));

    replace_utf8chars(&utf8chars, 0, ri);
    replace_utf8chars(&utf8chars, 1, emp);

    uint32_t result = release_utf8chars(&utf8chars);
    printf("expected released result=%i is 0 as succeeded.\n", result);
}

int main(void) {
    test1(u8"utf8リテラルは const char* とする。　バイトで扱うときは uint8_t にする。サロゲートペアの文字を含む 𩸽（ホッケ）");
}

