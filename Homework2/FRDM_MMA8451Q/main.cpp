#include <stdio.h>
union word
{
    short x; /* use as word */
    char bytes [2]; /* use as byte */
};
int main()
{
    union word w;
    w.x = 0x08F0; /* 08 F0 */
    printf("LSB = %x, MSB = %x\n", w.bytes[0], w.bytes[1]);
    return 0;
}