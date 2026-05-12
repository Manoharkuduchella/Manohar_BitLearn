"""
#Py_w1_1
for num in range(10,1000):
    ones = num%10
    tens = (num//10)%10
    hundreds = num//100
    res = (ones**3) + (tens**3) + (hundreds**3)

    if res == num:
        print(num)

#Py_w1_2
n = 10
c_prod =0
for i in range(1,11):
    c_prod += n
    print(f"{n} x {i} = {c_prod}")
"""
"""
#Py_w1_3
n = int(input("enter number"))
for p in range(2,n+1):
    for i in range(2,p):
        if(p%i == 0):
            break
    else:
        print(p)
"""
"""
#Py_w1_4
n = 5
for i in range(1,n):
    for j in range(i):
        print(j+1,end=" ")
    print()
"""
"""
#Py_w1_5
m = 125
b = m
while b > 0:
    print(b%10, end=" ")
    b = b//10
"""
"""
#Py_w1_6
def is_palindorme(num):
    if num < 0:
        return False
    
    origin = num
    rev = 0
    while origin > 0:
        rev = (rev*10)+origin%10
        origin = origin//10    

    if num==rev:
        return True

n = 121
print(is_palindorme(n))
"""
"""
#Py_w1_7
a = 6
b = 8

while a != b:
    if a>b:
        a = a-b
    else:
        b = b-a

print(f"GCD : {a}")
"""
"""
#Py_w1_8
def hallow_square(n):
    for i in range(n):
        for j in range(n):
            if i == 0 or i == n-1 or j == 0 or j == n-1:
                print("*",end=" ")
            else:
                print(" ",end=" ")
        print()


hallow_square(5)


#Py_w1_9

def sumify(num):
    while num > 9:
        sum = 0
        while(num > 0):
            sum = sum+num%10
            num = num//10
        num = sum
    return num

print(sumify(9875))
"""
"""
#Py_w1_10
num = 123
cnt = 0
if num == 0:
    cnt = 1
else:
    n = abs(num)
    while(n > 0):
        n //=10
        cnt += 1

print(f"Number of digits: {cnt}")
"""
"""
#Py_w1_11
num = 5
fact = 1

if num < 0:
    print("no fact")
elif num == 0:
    print("The 0 fact is 1")
else:
    for i in range(1,num+1):
        fact *= i

print(fact)
"""
"""
#Py_w1_12
n = 5
for i in range(1,n+1):
    print("*"*i)

#Py_w1_13
n = 10
odd_sum =0

for i in range(1,n+1,2):
    odd_sum += i

print(f"odd_sum: {odd_sum}")
"""
"""
#Py_w1_14
n = 6
sum_div =0
for i in range(1,n):
    if n%i == 0:
        sum_div += i

if sum_div == n:
    print("its perfect")
else:
    print("it isn't perfect")
"""
"""
#Py_w1_15
n = 10

for i in range(n,0,-1):
    print(i)
"""
"""
#Py_w1_16
n = 1002
z_cnt=0

while n > 0:
    if n%10 == 0:
        z_cnt += 1
    n //= 10

print(f"z_cnt: {z_cnt}")
"""
"""
#Py_w1_17
n = 1000
sum =0

for i in range(n):
    if i%3 == 0 or i%5 == 0:
        sum += i
print(sum)
"""
"""
#Py_w1_18
n = 111

for i in range(2,n+1):
    if n%i == 0:
        print(i)
        break
"""
"""
#Py_w1_19
n = 5
for i in range(1, n + 1):
    print("*" * i)
    
for i in range(n - 1, 0, -1):
    print("*" * i)

print("a"*3)
"""

#Py_w1_20
n = 5
a, b = 0, 1

for i in range(2,n+1):
    a, b = b, a+b
print(f"{b}")
