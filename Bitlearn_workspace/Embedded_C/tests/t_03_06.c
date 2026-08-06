#define IS_POWER_OF_2(x)   ((x) > 0 && (((x) & ((x) - 1)) == 0))


// A power of 4 is:

// A power of 2
// The set bit must be in an even position (0,2,4,...)
#define IS_POWER_OF_4(x) \
    (IS_POWER_OF_2(x) && ((x) & 0x55555555))


// A power of 8 is:
// A power of 2
// The set bit must be in an even position 0, 3, 6, 9, 12, ...
#define IS_POWER_OF_8(x) \
    (IS_POWER_OF_2(x) && ((x) & 0x49249249))



// A power of 16 is:
// A power of 2
// The set bit must be in an even position 0, 4, 8, 12, 16, ...
#define IS_POWER_OF_16(x) \
    (IS_POWER_OF_2(x) && ((x) & 0x11111111))


//Count no of Set bits
#define COUNT_SET_BITS(x)                  \
({                                         \
    unsigned int n = (x);                  \
    unsigned int count = 0;                \
    while(n)                               \
    {                                      \
        n &= (n - 1);                      \
        count++;                           \
    }                                      \
    count;                                 \
})

//Count bits to flip to convert A to B
static inline int count_bits_to_flip(unsigned int a, unsigned int b)
{
    unsigned int x = a ^ b;
    int count = 0;

    while(x)
    {
        x &= (x - 1); // remove rightmost set bit
        count++;
    }

    return count;
}


#define REVERSE_BITS32(x) ({                \
    uint32_t n = (x);                       \
    n = ((n >> 1) & 0x55555555) | ((n & 0x55555555) << 1); \
    n = ((n >> 2) & 0x33333333) | ((n & 0x33333333) << 2); \
    n = ((n >> 4) & 0x0F0F0F0F) | ((n & 0x0F0F0F0F) << 4); \
    n = ((n >> 8) & 0x00FF00FF) | ((n & 0x00FF00FF) << 8); \
    n = (n >> 16) | (n << 16);              \
    n;                                      \
})


#define SWAP_BITS(num, i, j)                                    \
    do {                                                        \
        unsigned int bit1 = ((num) >> (i)) & 1U;               \
        unsigned int bit2 = ((num) >> (j)) & 1U;               \
        if (bit1 != bit2)                                       \
            (num) ^= ((1U << (i)) | (1U << (j)));              \
    } while (0)


#define SWAP_EVEN_ODD_BITS(x) \
    ((((x) & 0xAAAAAAAAU) >> 1) | (((x) & 0x55555555U) << 1))



#define COPY_SET_BITS_1BASE(x,y,l,r) \
    ((x) |= ((y) & (((~0U << ((l)-1)) ^ (~0U << (r))))))


#define TOGGLE_BITS_RANGE(x, l, r) \
    ((x) ^= ((~0U << (l)) ^ (~0U << ((r) + 1))))


#define OPPOSITE_SIGNS(x, y) (((x) ^ (y)) < 0)
int x = 10;
int y = -20;

printf("%d\n", OPPOSITE_SIGNS(x, y));


#define ARE_EQUAL(x, y) (!((x) ^ (y)))

//python
list[start : end : step]
nums = [10, 20, 30, 40, 50, 60]
nums[1:4] --> [20, 30, 40]
nums[:3] --> [10, 20, 30]


//map
The map() function in Python is used to apply a function to every element of an iterable (list, tuple, etc.) and return an iterator containing the results.
ex1: nums = [1, 2, 3, 4, 5]

result = map(lambda x: x*x, nums)

print(list(result))

ex2: 
def square(x):
    return x * x

nums = [1, 2, 3, 4]

result = map(square, nums)

print(list(result))


//median
def find_median(nums):
    nums.sort()
    n = len(nums)

    if n % 2 == 1:
        # Odd number of elements
        return nums[n // 2]
    else:
        # Even number of elements
        mid1 = nums[(n // 2) - 1]
        mid2 = nums[n // 2]
        return (mid1 + mid2) / 2

# Example
numbers = [7, 2, 5, 1, 9]

median = find_median(numbers)
print("Median =", median)