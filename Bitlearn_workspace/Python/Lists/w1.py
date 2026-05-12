"""
#Py_w1_1
fruits = ["apple","banana","cherry"]

print(fruits[1])

fruits[1] = "kiwi"

print(fruits)

print(len(fruits))


#Py_w1_2
fruits.append("orange")
print(fruits)
fruits.insert(1,"mango")
print(fruits)
fruits.remove("apple")
print(fruits)
fruits.pop()
print(fruits)
fruits.clear()

print(fruits)
"""
"""
#Py_w1_3
num = [1,2, 3, 4, 5]

for n in num:
    print(n, end=" ")

i =0
while i <len(num):
    print(num[i],end=" ")
    i+=1

#list comprehension for creating new list
squares = [n**2 for n in num]
print(squares)

"""
"""
#Py_w1_4
frt = ["apple", "banana", "cherry", "kiwi", "mango"]

frt_a = [f for f in frt if "a" in f]

frt_a = [f.upper() for f in frt]

frt_a = [f if f != "babanana" else "orange" for f in frt]
"""
"""
#Py_w1_5
numbers = [3,1,4,2,5]

numbers.sort()
print(numbers)

#sort in desc
numbers.sort(reverse=True)


desc_list = numbers.copy()

print(desc_list)
print(numbers)
"""

"""
#Py_w1_6
list1 = ["a","b","c"]
list2 = [1,2,3]

new_list = list1+list2
print(new_list)

#adding inplace
list1.extend(list2)
print(list1)
print(list2)
"""

#Py_w1_7
colors = ["red", "green", "blue", "green"]

green_count = colors.count("green")
print(f"Count of 'green': {green_count}")

blue_index = colors.index("blue")
print(f"Index of 'blue': {blue_index}")

colors.reverse()
print(f"Reversed list: {colors}")

colors.clear()
print(f"Cleared list: {colors}")