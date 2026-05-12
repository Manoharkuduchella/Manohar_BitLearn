import math
"""
#Py_w1_1
def print_details(name,age):
    print(f"Name:{name}, Age:{age}")

print_details("Alice",25)

#Py_w1_2
def multiply(a,b):
    return (a*b)

result = multiply(4,5)
print(result)


#Py_w1_3
def greet_person(name, greeting):
    print(F"{greeting} {name}!")

greet_person("Jhon","Hi")

#Py_w1_4
def area_of_circle(radius):
    return (math.pi*(radius**2))

print(area_of_circle(3))


#Py_w1_5
def is_negative(number):
    if number > 0:
        return False
    elif number < 0:
        return True
    
print(is_negative(5))
"""
"""
#Py_w1_6
def grade(scr):
    if scr >= 90:
        return 'A'
    elif scr >= 80:
        return 'B'
    elif scr >= 70:
        return 'C'
    else:
        return 'F'

print(grade(85))
print(grade(72))
print(grade(50))

#Py_w1_7
def sign(num):
    if num > 0:
        return 'Positive'
    elif num < 0:
        return 'Negative'
    else: 
        return 'Zero'

print(sign(10))
print(sign(-4))
print(sign(0))
"""
"""
#Py_w1_8
def power(base, exponent=2):
    return base**exponent

print(power(3))
print(power(2,5))
"""
"""
#Py_w1_9
def introduction(name, country='India'):
    print(F"My name is {name} and I am from {country}")

introduction("sara")
introduction("sara","England")


#Py_w1_10
def return_multiple(a,b):
    return a,b

p, q = return_multiple(5,6)

print(p,q)
"""
"""
#Py_w1_11
def string_stat(s):
    vowels_list = "aeiouAEIOU"

    v_cnt=c_cnt=d_cnt=0

    for ch in s:
        if ch.isalpha():

            if ch in vowels_list:
                v_cnt += 1
            else:
                c_cnt +=1
        elif ch.isdigit():
            d_cnt += 1

    return (v_cnt, c_cnt, d_cnt)

print(string_stat("Hello123"))
"""
"""
#Py_w1_12
def factorial(n):
    if n==0 or n==1:
        return 1
    else:
        return n*factorial(n-1)

print(factorial(5))
"""
"""
#Py_w1_13
def sum_list(lst):
    if not lst:
        return 0
    return lst[0] + sum_list(lst[1:])

print(sum_list([1,2,3,4]))

#Py_w1_14
def rev_string(s):
    if len(s) <= 1:
        return s
    return rev_string(s[1:])+s[0]

print(rev_string("python"))


#Py_w1_15
def fibonacci(n):
    if n <= 2:
        return 1
    else:
        return fibonacci(n-1)+fibonacci(n-2)
    
print(fibonacci(5))
"""
#Py_w1_16
def min_max(numbers):
    return min(numbers),max(numbers)

small, large = min_max([8,3,4,3,20])
print("smallest:",small)
print("largest:",large)