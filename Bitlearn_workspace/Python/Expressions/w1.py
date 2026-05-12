"""
#Py_w1_1

import math
n =7
print(math.sqrt(n))
"""

"""
#Py_w1_2

a, b, c, x = 2, 3, 4, 5
print(a*x**2+b*x+c)
"""
"""
#Py_w1_3

a = 29
d = 6

print(a%d)
"""
"""
#Py_w1_4

num =0
print("positive" if num > 0 else "negative" if num < 0 else "zero")
"""
"""
#Py_w1_5
"""

"""
n = -12
print(abs(n))

#Py_w1_6
a = 15
b = 8
a , b = b, a
print(a,b)

#Py_w1_7
x =5
y=8
z=10
print((x+y+x)/3)

#Py_w1_8
a,b = 20,13
print("a is small" if a < b else "b is small" )

#Py_w1_9
x,y = 9,5
result = x^y
print(F"{result}")

#Py_w1_10
a = 18
print("True" if a%2 == 0 and a%3 == 0 else "Flase")

#Py_w1_11
a, b, c = 14,27,19
print(a if ((a>b)and(a>c)) else b if (b>c) else c)

#Py_w1_12
n = 32
if n>0 and n&(n-1) == 0:
    print("power of two")

#Py_w1_13
a, b, c = 20, 12,18

res = (a+b+c) - max(a,b,c) - min(a,b,c)
print(res)
"""
"""
#Py_w1_14
n = 1
print(n)
print("n=",n^(1<<4))

#Py_w1_15
p = 0xf
print(p.bit_count())

#Py_w1_16
def find_sign(n):
    return ((n>0) - (n<0))

n=4
print(find_sign(n))

#Py_w1_17
n =12

stat = (n%4 == 0) and (n%8 != 0)
print(stat)
"""
"""
#Py_w1_18
n = 150
k = 2
res = ((n << k)|(n >> (8-k))) & 0xFF
print(res)

#Py_w1_19
a,b,c = 8,27,14

res = (max(a,b,c) - min(a,b,c))
print(res)
"""
#Py_w1_20
n =9
bit = 3

res = n | (1<<bit)
print(res)