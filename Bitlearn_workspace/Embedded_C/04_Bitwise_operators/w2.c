#include <stdio.h>

/* 1. Check LSB */
void EC_BO_W2_1()
{
    int n = 5;
    if(n & 1)
        printf("LSB of %d is set (1)", n);
    else
        printf("LSB of %d is not set (0)", n);
}

/* 2. Check MSB (8-bit) */
void EC_BO_W2_2()
{
    int n = 128;
    if(n & (1 << 7))
        printf("MSB of %d is set (1)", n);
    else
        printf("MSB of %d is not set (0)", n);
}

/* 3. Get nth bit */
void EC_BO_W2_3()
{
    int n = 10, pos = 2;
    int bit = (n >> pos) & 1;
    printf("Bit %d of %d is %d", pos, n, bit);
}

/* 4. Set nth bit */
void EC_BO_W2_4()
{
    int n = 8, pos = 0;
    int res = n | (1 << pos);
    printf("Number after setting bit %d: %d", pos, res);
}

/* 5. Clear nth bit */
void EC_BO_W2_5()
{
    int n = 10, pos = 3;
    int res = n & ~(1 << pos);
    printf("Number after clearing bit %d: %d", pos, res);
}

/* 6. Toggle nth bit */
void EC_BO_W2_6()
{
    int n = 10, pos = 1;
    int res = n ^ (1 << pos);
    printf("Number after toggling bit %d: %d", pos, res);
}

/* 7. Highest set bit position */
void EC_BO_W2_7()
{
    int n = 18, pos = -1;
    for(int i = 0; i < 32; i++)
    {
        if(n & (1 << i))
            pos = i;
    }
    printf("Highest set bit of %d is at position %d", n, pos);
}

/* 8. Lowest set bit position */
void EC_BO_W2_8()
{
    int n = 18, pos = -1;
    for(int i = 0; i < 32; i++)
    {
        if(n & (1 << i))
        {
            pos = i;
            break;
        }
    }
    printf("Lowest set bit of %d is at position %d", n, pos);
}

/* 9. Count trailing zeros */
void EC_BO_W2_9()
{
    int n = 40, count = 0;
    while(((n >> count) & 1) == 0 && count < 32)
        count++;
    printf("Number of trailing zeros: %d", count);
}

/* 10. Count leading zeros (32-bit) */
void EC_BO_W2_10()
{
    int n = 16, count = 0;
    for(int i = 31; i >= 0; i--)
    {
        if((n >> i) & 1)
            break;
        count++;
    }
    printf("Number of leading zeros: %d", count);
}

/* 11. Flip bits (8-bit) */
void EC_BO_W2_11()
{
    unsigned char n = 5;
    unsigned char res = ~n;
    printf("Flipped bits: %d", res);
}

/* 12. Count zeros and ones (8-bit) */
void EC_BO_W2_12()
{
    int n = 15, ones = 0, zeros = 0;
    for(int i = 0; i < 8; i++)
    {
        if(n & (1 << i))
            ones++;
        else
            zeros++;
    }
    printf("Number of ones: %d, Number of zeros: %d", ones, zeros);
}

/* 13. Rotate left */
void EC_BO_W2_13()
{
    int n = 16, pos = 2;
    int res = (n << pos) | (n >> (32 - pos));
    printf("Result after rotation: %d", res);
}

/* 14. Decimal to binary */
void EC_BO_W2_14()
{
    int n = 13;
    printf("Binary representation: ");
    for(int i = 31; i >= 0; i--)
    {
        if((n >> i) & 1)
        {
            for(int j = i; j >= 0; j--)
                printf("%d", (n >> j) & 1);
            break;
        }
    }
}

/* 15. Swap using XOR */
void EC_BO_W2_15()
{
    int a = 5, b = 9;
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    printf("After swapping: a=%d, b=%d", a, b);
}

/* 16. Even or Odd */
void EC_BO_W2_16()
{
    int n = 7;
    if(n & 1)
        printf("%d is odd", n);
    else
        printf("%d is even", n);
}

int main()
{
    //EC_BO_W2_1();
    //EC_BO_W2_2();
    //EC_BO_W2_3();
    //EC_BO_W2_4();
    //EC_BO_W2_5();
    //EC_BO_W2_6();
    //EC_BO_W2_7();
    //EC_BO_W2_8();
    //EC_BO_W2_9();
    //EC_BO_W2_10();
    //EC_BO_W2_11();
    //EC_BO_W2_12();
    //EC_BO_W2_13();

}