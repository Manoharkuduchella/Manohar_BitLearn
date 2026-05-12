#include<stdio.h>
#include<stddef.h>
/* Structure vs Union in Embedded Systems */
struct st
{
    int a;
    char b;
};

union un{
    int a;
    char b;
};
void EC_STC_W1_1()
{
    struct st v;
    union un u;

    printf("st: %d and un:%d",sizeof(v),sizeof(u));
}


/* Bit-fields in Structures */
struct reg
{
    int RCC:8;
};

void EC_STC_W1_2()
{
    struct reg a;
    a.RCC = 0xff;

    printf("%x",a.RCC);
    /*toggle bit without bitwise*/
    //calculate bit position with out using <<
    int value =1;int pos =2;
    for(int i=0;i<pos;i++)
    {
        value = value*2;//becomes 4 --> 0x04;
    }

    if(((a.RCC / value)%2) == 1)
    {
        a.RCC = a.RCC - value; //as bit is 1 make it 0
    }
    else{
        a.RCC = a.RCC + value; //as bit is 0 make it 1
    }
}

/*Structure Padding, Alignment, and Packing */
struct regi
{
    int b;
    char c;
};
void EC_STC_W1_3()
{
    struct regi r;
    printf("size of struct regi: %d\n",sizeof(r));
    //offsetof() macro is used to find the offset value of member of struct or union in allocated memmory

    printf("offset of r.b: %d\n",offsetof(struct regi,b));
    printf("offset of r.c: %d\n",offsetof(struct regi,c));
}


/*Function Pointers in Structures*/
void fun1()
{
    printf("form fun1");
}
void fun2()
{
    printf("form fun2");
}
void fun3()
{
    printf("form fun3");
}

struct driver_behaviour
{
    void (*fp1)(void);
    void (*fp2)(void);
    void (*fp3)(void);
};

void EC_STC_W1_4()
{
    struct driver_behaviour b;
    b.fp1 = fun1;
    b.fp2 = fun2;
    b.fp3 = fun3;

    b.fp1();
    b.fp2();
    b.fp3();
}

/*Nested Structures and Arrays within Structures */

struct regis
{
    int b;
    char c;
};
struct bank
{
    int a[10];
    char b;
    struct regis r;
};

void EC_STC_W1_7()
{
    struct bank bk;
    bk.r.b = 5;
    bk.a[5] = 6;

    struct bank *sptr = &bk;
 
    printf("sptr->r.b: %d\n",sptr->r.b);
    printf("sptr->a[5]: %d\n",sptr->a[5]);
}

#include <stdio.h>

/* structure */
struct Student {
    int id;
    float marks;
};

/* pass by value */
void modify_by_value(struct Student s)
{
    s.id = 100;
    s.marks = 99.9;
}

/* pass by reference */
void modify_by_ref(struct Student *s)
{
    s->id = 200;
    s->marks = 88.8;
}

/* return structure */
struct Student create_student()
{
    struct Student s = {1, 75.5};
    return s;
}

void EC_STC_W1_8()
{
    struct Student s1 = {10, 60.0};

    modify_by_value(s1);
    printf("After pass by value: id=%d marks=%.1f\n", s1.id, s1.marks);

    modify_by_ref(&s1);
    printf("After pass by reference: id=%d marks=%.1f\n", s1.id, s1.marks);

    struct Student s2 = create_student();
    printf("Returned struct: id=%d marks=%.1f\n", s2.id, s2.marks);

    printf("Size of struct: %lu bytes\n", sizeof(struct Student));
}

struct Data {
    int a;
    float b;
    char c;
};


union UData {
    int a;
    float b;
    char c;
};

void EC_STC_W1_9()
{
    struct Data s = {10, 5.5, 'A'};

    int arr[3] = {10, 20, 30};

    union UData u;
    u.a = 10;

    printf("Structure: %d %.1f %c\n", s.a, s.b, s.c);
    printf("Array: %d %d %d\n", arr[0], arr[1], arr[2]);
    printf("Union (int): %d\n", u.a);

    printf("Size of struct: %lu\n", sizeof(s));
    printf("Size of array: %lu\n", sizeof(arr));
    printf("Size of union: %lu\n", sizeof(u));
}


#include <stdio.h>


typedef struct {
    int id;
    float val;
} Device;


Device g_dev = {1, 1.1};

void EC_STC_W1_10()
{
    
    struct {
        int a;
        float b;
    } local = {2, 2.2};

    
    static Device s_dev = {3, 3.3};

    
    Device d = {.id = 10, .val = 9.9};

    printf("Global: %d %.1f\n", g_dev.id, g_dev.val);
    printf("Local: %d %.1f\n", local.a, local.b);
    printf("Static: %d %.1f\n", s_dev.id, s_dev.val);
    printf("Designated: %d %.1f\n", d.id, d.val);
}


#include <stdio.h>


struct A {
    char c;
    int i;
    char d;
};


struct B {
    int i;
    char c;
    char d;
};


#pragma pack(1)
struct Packed {
    char c;
    int i;
    char d;
};
#pragma pack()

void EC_STC_W1_11()
{
    printf("Size of struct A: %lu\n", sizeof(struct A));
    printf("Size of struct B: %lu\n", sizeof(struct B));
    printf("Size of packed struct: %lu\n", sizeof(struct Packed));
}



int main()
{
    //EC_STC_W1_1();

   // EC_STC_W1_2();
   //EC_STC_W1_3();

   //EC_STC_W1_4();
   EC_STC_W1_7();
    EC_STC_W1_8();
    EC_STC_W1_9();
    EC_STC_W1_10();
    EC_STC_W1_11();
}