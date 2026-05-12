"""
#Py_w1_1
mytuple = (10,3.14,"python",True)

print(mytuple)


#Py_w1_2
tup = (10,20,30,40,50)

first = tup[0]
last = tup[-1]

print(first,last)

#Py_w1_3
t = (1,2,3)

x, y, z = t

print(x)
print(y)
print(z)

#Py_w1_4
my_tuple = ('a', 'b', 'c')
print('b' in my_tuple)

#Py_w1_5
t = (0, 1, 2, 3, 4, 5)
print(t[1:4])
"""
"""
#Py_w1_6
t = (10, 20, 30, 40)
print(len(t))

#Py_w1_7
t = ("apple", "banana", "cherry")
for item in t:
    print(item)

#Py_w1_8
t1 = (1, 2)
t2 = (3, 4)
print(t1 + t2)


#Py_w1_9
t = (5, 6)
print(t * 3)

#Py_w1_10
t = (11, 3, 55, 21)
print(max(t))
print(min(t))


#Py_w1_11
lst = [1, 2, 3]
tup = (4, 5, 6)

print(f"Tuple: {tuple(lst)}")
print(f"List: {list(tup)}")
"""

"""
#Py_w1_12
t = (1, 2, 3)
lst = list(t)
lst.append(4)
t = tuple(lst)
print(t)

#Py_w1_13
t = (1, 2, 3, 4)
lst = list(t)
lst.remove(2)
t = tuple(lst)
print(t)


#Py_w1_14
t = ('P', 'y', 't', 'h', 'o', 'n')

s = "".join(t)
print(f'String: "{s}"')

t_new = tuple(s)
print(f"Tuple: {t_new}")

#Py_w1_15
t = (("11", "22"), ("33", "44"))

result = tuple(tuple(int(x) for x in sub) for sub in t)
print(result)


#Py_w1_16
t = ("cat", "dog", "rabbit")
print(t.index("dog"))

#Py_w1_17
t = (1, 2, 3, 2, 2, 4)
print(t.count(2))
"""
"""
#Py_w1_18
t = (10, 20, 30, 40)
print(t[::-1])

#Py_w1_19
t = (2, 4, 6, 2, 8, 4, 6, 2)
duplicates = sorted(set(x for x in t if t.count(x) > 1), key=t.index)

print(", ".join(map(str, duplicates)))

#Py_w1_20
t = (1, 2, 3, 4, 5)
print(len(t) == len(set(t)))
"""
"""
#Py_w1_21
lst = [("Alice", 25), ("Bob", 20), ("Eve", 22)]

sorted_lst = sorted(lst, key=lambda x: x[1])
print(sorted_lst)

"""
"""
#Py_w1_22
lst = [(1, 2), (10, 11), (3, 44)]

def count_digits(t):
    return sum(len(str(abs(x))) for x in t)

sorted_lst = sorted(lst, key=count_digits)
print(sorted_lst)

#Py_w1_23
lst = [(10, 20, 40), (40, 50, 60), (70, 80, 90)]
new_val = 100

output = [t[:-1] + (new_val,) for t in lst]

print(output)
"""
#Py_w1_24
lst = [(), (), ('a', 'b'), ('c',)]

output = [t for t in lst if t]

print(output)


#Py_w1_25
lst = [(3, 6), (9, 12, 15), (4, 8)]
K = 3

count = sum(1 for t in lst if all(x % K == 0 for x in t))
print(count)

#Py_w1_26
lst = [(1, 2), (-3, 4), (5, 6)]

output = [t for t in lst if all(x > 0 for x in t)]

print(output)

#Py_w1_27
lst = [(1, 2), (2, 3), (3, 4)]

output = [sum(t) for t in lst]

print(output)

#Py_w1_28
lst = [(1, 'a'), (2, 'b'), (3, 'c')]

list1, list2 = zip(*lst)

print(list(list1))
print(list(list2))

#Py_w1_28
t = ((1, 2), (3, 4), (5, 6))
output = tuple(item for sub in t for item in sub)

print(output)

#Py_w1_29
t = ((1, 2), (2, 3), (4, 5))

unique_elements = set()
for inner_tuple in t:
    unique_elements.update(inner_tuple)

print(unique_elements)
# Output: {1, 2, 3, 4, 5}


#Py_w1_30
t = ((1, 2), (2, 3), (4, 5))

unique_elements = {item for sub in t for item in sub}

print(unique_elements)

