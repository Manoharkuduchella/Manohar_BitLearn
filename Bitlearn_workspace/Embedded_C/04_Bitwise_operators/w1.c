#include<stdio.h>

/*
AND
------
 0 0 0
 0 1 0
 1 0 0
 1 1 1

 OR
 ----
 0 0 0
 0 1 1
 1 0 1
 1 1 1

 XOR
 -----
 0 0 0
 0 1 1
 1 0 1
 1 1 0

 << and >> shift the bits respectively

*/

/*Write a program to perform the following operations on the Least and Most Significant Bits (LSB/MSB) of a given integer:
Set the LSB to 1
Clear the LSB (set to 0)
Toggle the LSB
Set the MSB to 1
Clear the MSB (set to 0)
Toggle the MSB
Set a specific bit to 1
Clear a specific bit
Toggle a specific bit*/

void EC_BO_W1_2(){
        unsigned int num=3;

    num = num|1;

    num = (~1&num);

    num = num^1;

    num = (1<<31)|num;

    num = ~(1<<31)&num;

    num = ~(1<<31)^num;

    num = (1<<3)|num;

    num = ~(1<<3)&num;
    num = (1<<3)^num;
}


/*Write a program to modify specific portions of a given integer:
Set all bits in the Least Significant Byte (LSB) to 1
Set all bits in the Most Significant Byte (MSB) to 1
Set all bits in the Least Significant Nibble to 1
Set all bits in the Most Significant Nibble to 1
Set n bits to 1 (user input)
Clear n bits (set to 0), with n as input
Toggle n bits (user input)*/
void EC_BO_W1_3()
{
    unsigned int num=3;

    num = (0xff|num);

    num = (0xff000000|num);

    num = (0x0f|num);

    num = (0xf0000000|num);

    int n;num =1;
    printf("enter n:");
    scanf("%d",&n);

    num = ~(~0<<n)|num;
    //printf("%x",num);

    num=0xffffff;
    num = (~0<<n)&num;
    //printf("%x",num);

    num=0xffffff;
    num = ~(~0<<n)^num;
    printf("%x",num);


}


/*Write a program to check bit status in an integer:
Check if LSB is set (1) or not (0)
Check if MSB is set (1) or not (0)
Check if the nth bit is set (1) or not (0) (user input)*/
void EC_BO_W1_4()
{
    unsigned int num=3;
    int n;
    printf("enter n:");
    scanf("%d",&n);
    printf("its %d\n",(num&1));
    printf("its %d\n",((num>>31)&1));
    printf("its %d\n",((num>>n)&1));

    
}


/*Write macros to set, clear, and toggle the nth bit using bitwise operators*/

#define SET(WORD,N) WORD = ((1<<N)|WORD)
#define CLEAR(WORD,N) WORD = (~(1<<N)&WORD)
#define TOGGLE(WORD,N) WORD = ((1<<N)^WORD)
void EC_BO_W1_5()
{
    unsigned int num=3;
    SET(num,2);
    printf("%x ",num);
    CLEAR(num,2);
    printf("%x ",num);
    TOGGLE(num,2);
    printf("%x ",num);
}



/*Write a C program to count the number of set bits in an unsigned integer.*/
void EC_BO_W1_6()
{
    unsigned int num=3;int cnt=0;
    for(int i=31;i>=0;i--)
    {
        if((num>>i)&1)
            cnt++;
    }

    printf("%d",cnt);

}


/*How can you count the number of set bits in a floating-point number?*/
void EC_BO_W1_7()
{
    //Note: bitwise operations on float is not valid
    union var{
        float f;
        int i;
    }v;
    v.f = 23.4;

    for(int i=31;i>=0;i--)
    {
        printf("%d ",(v.i>>i)&1);

    }


}


/*Write a C program to count the number of bits set to 1 in an integer. Also compare different methods. Additionally, check if the 20th bit of a 32-bit integer is set.*/
void EC_BO_W1_8()
{

}

/*Write a C program to check whether a number is a power of 2 using bitwise operations.*/
void EC_BO_W1_9()
{
    int n;
    printf("enter n:");
    scanf("%d",&n);

    if((n&(n-1)) == 0)
        printf("its a power of two\n");
    else 
        printf("its not a power of two\n");

}

/*Write a C program to determine whether a number is odd or even using bitwise operators.*/
void EC_BO_W1_10()
{
    int n;
    printf("enter n:");
    scanf("%d",&n);

    if((n&1) == 0)
        printf("its even\n");
    else 
        printf("its odd\n");
}


/*Implement the function setbits(x, p, n, y) that sets n bits in x starting at position p with the rightmost n bits of y.*/
void EC_BO_W1_11()
{
    unsigned int x=0xffffffff,p=4,n=4,y=0x0000;

    int mask = ~(~0<<n);

    x = x&(~(mask<<p));
    x=x|((mask&y)<<p);

    printf("%x",x);
}


/*Given two integers A and B, write a program to count the number of bits that need to be flipped to convert A into B.*/
void EC_BO_W1_12()
{
    int a =5;
    int b= 3,cnt=0;
    int res = a^b;

    for(int i=31;i>=0;i--)
    {
        if((res>>i)&1)
            cnt++;
    }

    printf("%d",cnt);
}
/*Write a program to reverse all bits in an integer.*/
void EC_BO_W1_13()
{
    unsigned int a =0xfA;
    int cnt =32;
    int res=0;
    while(cnt--)
    {
        res = res<<1|(a&1);
        a = a>>1;
    }

    printf("%x",res);

}

/*Write a program to reverse:
Bits at odd positions
Bits at even positions*/
void EC_BO_W1_14()
{
    unsigned int a = 0xCA;

    unsigned int odd = a & 0x55555555;
    /*
    note: ox1100 1010
    pos:    8765 4321
    odd:     . .  . .
    even:   . .  . .
    */

    unsigned int rev = 0,compressed=0,res=0;
   
    for(int i=0,j=0;i<32;i+=2)
    {
        if(odd & (1<<i))
            compressed = (compressed|(1<<j));
        j++;
    }

    //reverse only 16bits
    for(int i=0;i<16;i++)
    {
        rev = (rev<<1)|((compressed>>i)&1);
    }

    //clear odd positions
    res = (a & 0xAAAAAAAA);
    //update the odds
    for(int i=0,j=0;i<32;i+=2)
    {
        if(rev & (1<<j))
            res = res | (1<<i);
        j++;
    }

    printf("%x",res);



}

/*Write a program to multiply a number by 9 using bitwise shift operations. */
void EC_BO_W1_15()
{
    int n= 5;
    int res;
    res = (n<<3)+n;
    printf("%d",res);
} 

/*Write a program to determine the size (in bits) of an integer using bit shifts. */
void EC_BO_W1_16()
{
    unsigned int a = ~0;

    int cnt=0;

    while(a != 0)
    {
        a=a>>1;
        cnt++;
    }
    printf("%d",cnt);
}

/*Write a program to convert a Little Endian integer to its Big Endian equivalent*/
void EC_BO_W1_17()
{
    int a = 0x12345678;
    char *p = (char*)&a;

    a = ((0xff&a)<<24)|((0xff00&a)<<8)|((0xff0000&a)>>8)|((0xff000000&a)>>24);

    printf("%x",a);
}


int main()
{
    //EC_BO_W1_2(); 
    //EC_BO_W1_3();  
    //EC_BO_W1_4();    
    //EC_BO_W1_5();
    //EC_BO_W1_6();
    //EC_BO_W1_7();
    //EC_BO_W1_8();
    //EC_BO_W1_9();
    //EC_BO_W1_10();
    //EC_BO_W1_11();
    //EC_BO_W1_12();

    //EC_BO_W1_13();

    //EC_BO_W1_14();
    //EC_BO_W1_15();

    //EC_BO_W1_16();
    EC_BO_W1_17();

}