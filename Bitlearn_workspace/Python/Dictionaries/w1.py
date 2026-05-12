#Py_w1_1

dic_std = {101:'ravi', 102:'ammmit', 103:'amit' }
print(dic_std)

#Py_w1_2
d = {'x':1,'y':2, 'x':5}
print(d)

#Py_w1_3
ds = {'fruit': 'apple', 'veg': 'carrot'}
print('fruit' in ds)

#Py_w1_4
fruit = "apple"
fruit_dic = {}

for ch in fruit:
    if ch in fruit_dic:
        fruit_dic[ch] += 1
    else:
        fruit_dic[ch] = 1

print(fruit_dic)

#Py_w1_5
marks = {'math':75,'science':80}
print(marks['science'])

#Py_w1_6

#marks = {'math': 75}
#print(marks['english'])  # KeyError

#Py_w1_7

scores = {'math': 80, 'science': 90}
print(scores.get('history', 'Not found'))

#Py_w1_8

student = {'math': 90, 'english': 88, 'science': 92}
for k, v in student.items():
    print(k, v)

#Py_w1_9

ages = {'Anil': 21, 'Sunita': 20}
ages['Anil'] = 22
print(ages)

#Py_w1_10

info = {'a': 10, 'b': 20}
info['a'] = 100
info['b'] = 100
print(info)

#Py_w1_11

salaries = {'A': 20000, 'B': 30000}
for k in salaries:
    salaries[k] *= 1.1
print(salaries)

#Py_w1_12

salaries = {'A': 20000, 'B': 30000}
salaries['C'] = 25000
print(salaries)

#Py_w1_13

cities = {'Delhi': 18000000, 'Mumbai': 20000000}
cities['Bangalore'] = 12000000
print(cities)

#Py_w1_14

user = {'name': 'Riya'}
if 'status' not in user:
    user['status'] = 'active'
print(user)

#Py_w1_15

words = ['dog', 'cat', 'rabbit']
d = {w: len(w) for w in words}
print(d)

#Py_w1_16

d1 = {'x': 1}
d2 = {'y': 2}
d1.update(d2)
print(d1)

#Py_w1_17

marks = {'math': 80, 'science': 85}
del marks['math']
print(marks)

#Py_w1_18

info = {'name': 'Amit', 'city': 'Pune'}
val = info.pop('name')
print(val)
print(info)

#Py_w1_19

d = {'x': 1, 'y': 2}
d.clear()
print(d)

#Py_w1_20

d = {'x': 1, 'y': 2}
if 'z' in d:
    del d['z']
else:
    print('Key not found')

#Py_w1_21

d = {'a': 10, 'b': 20, 'c': 30}
for k in d:
    print(k)

#Py_w1_22

d = {'a': 10, 'b': 20, 'c': 30}
for v in d.values():
    print(v)

#Py_w1_23

d = {'a': 10, 'b': 20, 'c': 30}
for k, v in d.items():
    print(k, v)

#Py_w1_24

scores = {'math': 75, 'science': 55, 'english': 82}
for k, v in scores.items():
    if v > 60:
        print(k)

#Py_w1_25

d = {'p': 2, 'q': 3}
copy_d = d.copy()
print(copy_d)

#Py_w1_26

a = {'x': [1, 2]}
b = a
b['x'].append(3)
print("a:", a)
print("b:", b)

#Py_w1_27

original = {'car': 'red', 'bike': 'blue'}
copy_dict = original.copy()
copy_dict['car'] = 'green'
print("Original:", original)
print("Copy:", copy_dict)

#Py_w1_28
# Shallow vs Deep copy
import copy

d = {'x': [1, 2]}

shallow = copy.copy(d)
deep = copy.deepcopy(d)

shallow['x'].append(3)
print("After shallow change:", d)

deep['x'].append(4)
print("After deep change:", d)

#Py_w1_29

students = {
    'Rahul': {'age': 16, 'marks': {'math': 90, 'english': 88}},
    'Simran': {'age': 15, 'marks': {'math': 95, 'english': 92}}
}
print(students)

#Py_w1_30

students = {
    'Rahul': {'age': 16, 'marks': {'math': 90, 'english': 88}},
    'Simran': {'age': 15, 'marks': {'math': 95, 'english': 92}}
}
print(students['Rahul']['marks']['english'])

#Py_w1_31

students = {
    'Rahul': {'age': 16, 'marks': {'math': 90, 'english': 88}},
    'Simran': {'age': 15, 'marks': {'math': 95, 'english': 92}}
}

for name, data in students.items():
    print(name)
    for subject, marks in data['marks'].items():
        print(subject, marks)

#Py_w1_32

students = {
    'Rahul': {'age': 16, 'marks': {'math': 90, 'english': 88}},
    'Simran': {'age': 15, 'marks': {'math': 95, 'english': 92}}
}

students['Simran']['marks']['science'] = 93
print(students)

