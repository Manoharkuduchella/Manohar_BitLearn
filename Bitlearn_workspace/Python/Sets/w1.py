#set is mutable and follows unordered and allows unique elements
#list is mutable and follows insertion order and allows duplicates
#tuples are immutable and allows duplicates

"""
#Py_w1_1
bag = {"ball", "car", "puzzle", "car", "yo-yo"}

print(len(bag))#4

#Py_w1_2
animals = {"lion","tiger","bear"}
for an in animals:
    print(an)

#Py_w1_3
scores = {3,7,10,2,9}
print(max(scores),min(scores))

#Py_w1_4
toys = {"robot", "car","doll"}
toys.remove("doll")
print(toys)

#Py_w1_5
my_favs = ["tom","Jerry","Ben 10"]
frnd_favs = ["powerpuff","Jerry","scooby"]

common = set(my_favs) & set(frnd_favs)

match = list(common)[0]

if common:
    print(f'Yes {match} is common.')
else:
    print("No common cartoons.")
"""
#Py_w1_6
a = ["Toy Story", "Frozen", "Moana"]
b = ["Moana", "Coco", "Frozen"]
c = ["Frozen", "Moana", "Up"]

#cmn = set(a) & set(b) & set(c)
#print(list(cmn))
#or
result = set(a).intersection(b,c)
print(list(result))




"""
#Py_w1_7
old_hw = ["math", "science", "art"]
new_hw = ["math", "history", "science"] 

set_old = set(old_hw)
set_new = set(new_hw)

missing = set_old - set_new
additional = set_new - set_old

print(f'MISSING:missing', f'Additional: additional')
"""

#Py_w1_8
last_week = ["hide", "seek", "tag"]
this_week = ["hide", "seek", "jump", "run"]

print(list(set(this_week) - set(last_week))) 

#Py_w1_9
yesterday = [1, 2, 3, 4]
today = [1, 4, 2]

missing = set(yesterday) - set(today)
print(*missing)

#Py_w1_10
msg = "hello world"
vowels = set("aeiou")

count = sum(1 for ch in msg if ch in vowels)
print(count)

#Py_w1_11
word1 = "apple"
word2 = "orange"

result = ''.join(set(word1) ^ set(word2))
print(result)

#Py_w1_12
words = ["education", "python", "sequoia"]
vowels = set("aeiou")

result = [w for w in words if vowels.issubset(set(w))]
print(result)

#Py_w1_13
note = "101010"

if set(note) <= {"0", "1"}:
    print("Yes")
else:
    print("No")

#Py_w1_14
import string

sentence = "The quick brown fox jumps over a lazy dog"
letters = set(sentence.lower()) & set(string.ascii_lowercase)

if len(letters) == 26:
    print("Yes")

#Py_w1_15
import string

A = {"abc", "defg", "xyz"}
B = {"mnopq", "rstuv", "wxyz"}

alphabet = set(string.ascii_lowercase)

for a in A:
    for b in B:
        if set(a + b) >= alphabet:
            print((a, b))

#Py_w1_16
word = "lamp"

if len(set(word)) == len(word):
    print("Yes")
else:
    print("No")

#Py_w1_17
toys_set = {"teddy", "robot", "ball"}

toys_tuple = tuple(toys_set)
print(toys_tuple)

print(set(toys_tuple))

#Py_w1_18
badges = {"star", "moon", "heart"}

print(list(badges))

#Py_w1_19
letters = {"A", "B", "C"}

print(''.join(sorted(letters)))

#Py_w1_20
myname = "samantha"

print(set(myname))

#Py_w1_21
pets = {"dog", "cat", "fish"}

d = {k: i for i, k in enumerate(pets)}
print(d)

#Py_w1_22
friends_colors = [
    ["red", "blue"],
    ["green", "red"],
    ["yellow", "blue"]
]

result = set()
for lst in friends_colors:
    result.update(lst)

print(result)

#Py_w1_23
mine = ["dino", "star", "moon"]
yours = ["star", "rocket", "moon"]

print(set(mine) & set(yours))

#Py_w1_24
from itertools import combinations

kids = {"Amy", "Bob", "Cara", "Dan", "Eva"}
size = 3

for combo in combinations(kids, size):
    print(combo)
    break  # one example

#Py_w1_25
from collections import Counter

marbles = ["red", "blue", "red", "green", "blue", "red"]

freq = Counter(marbles)
print(max(freq.values()))

