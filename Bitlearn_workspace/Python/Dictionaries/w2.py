#Py_w2_1
stock = {'apples': 14, 'bananas': 22, 'rice': 12}
query = 'apples'

if query in stock:
    print(f"Yes, {query} are in stock!")

#Py_w2_2
pets = {'Harry': 'owl', 'Ron': 'rat'}
query = 'Hermione'

print(pets.get(query, "No record, maybe try another student!"))

#Py_w2_3
auction = {'lot1': 'coin', 'lot2': 'stamp', 'lot3': 'coin', 'lot4': 'comic'}
unique = list(set(auction.values()))
print("Unique collectibles:", unique)

#Py_w2_4
inventory = {'box': 30, 'crate': 22, 'pallet': 8}
print("Total items in warehouse:", sum(inventory.values()))

#Py_w2_5
north = {'Winterfell': 1000, 'The Eyrie': 800}
south = {'The Eyrie': 1200, "King's Landing": 2500}

north.update(south)
print(north)

#Py_w2_6
codes = {'alpha': 'ok', 'beta': 'wait'}
new_labels = {'alpha': 'red', 'beta': 'blue'}

result = {new_labels[k]: v for k, v in codes.items()}
print(result)

#Py_w2_7
spells = {'fireball': 5, 'healing': 10, 'curse': 2}
banned = ['curse', 'fireball']

for b in banned:
    spells.pop(b, None)

print(spells)

#Py_w2_8
orders = ['latte', 'espresso', 'latte', 'tea', 'espresso', 'latte']

freq = {}
for item in orders:
    freq[item] = freq.get(item, 0) + 1

print(freq)

#Py_w2_9
profile = {'info': {'name': 'Sam', 'phone': '555-1234'}}
profile['info']['phone'] = '555-9999'
print(profile)

#Py_w2_10
names = ['Alice', 'Bob', 'Eve']
seats = [5, 12, 8]

d = dict(zip(names, seats))
print(d)

#Py_w2_11
desk = {}

if not desk:
    print("Dictionary is empty!")

#Py_w2_12
valuables = {'ring': 5, 'necklace': 9, 'watch': 2}

max_key = max(valuables, key=valuables.get)
min_key = min(valuables, key=valuables.get)

print("Max:", max_key)
print("Min:", min_key)

#Py_w2_13
d = {'hello': 1, 'world': 2, 'hell': 3}
substring = 'hell'

result = [k for k in d if substring in k]
print("Keys containing 'hell':", result)

#Py_w2_14
d = {'x': 100, 'y': 200}
value = 200

for k, v in d.items():
    if v == value:
        print(f"Key for value {value}:", k)

#Py_w2_15
d = {'b': 2, 'a': 1, 'c': 3}
print(sorted(d.items()))

#Py_w2_16
lst = ['a', 'b', 'c', 'd']

nested = {}
for item in reversed(lst):
    nested = {item: nested}

print(nested)

#Py_w2_17
d = {'x': {'p': 1}, 'y': {'q': 2}}

result = {}
for outer, inner in d.items():
    for k, v in inner.items():
        result.setdefault(k, {})[outer] = v

print(result)

#Py_w2_18
d = {'math': {'john': 90, 'jane': 80}, 'science': {'john': 85, 'jane': 95}}

result = {}
for subject, students in d.items():
    for name, marks in students.items():
        result.setdefault(name, {})[subject] = marks

print(result)

#Py_w2_19
d = {'first': 1, 'second': 2, 'third': 3}
reversed_d = dict(reversed(list(d.items())))
print(reversed_d)

#Py_w2_20
d = {'a': 100, 'b': 200, 'c': 300}
lst = ['b', 'c', 'd']

result = {k: d[k] for k in lst if k in d}
print(result)

#Py_w2_21
d = {'a': 5, 'b': 10, 'c': 15, 'd': 'big'}
limit = 10

result = {k: v for k, v in d.items() if not isinstance(v, int) or v <= limit}
print(result)

#Py_w2_22
d = {'sun': 1, 'sunny': 2, 'rain': 3}
substring = 'sun'

result = {k: v for k, v in d.items() if substring not in k}
print(result)

#Py_w2_23
dicts = [{'a': 1, 'b': 2}, {'x': 1, 'y': 2, 'z': 3}, {'k': 9}]

largest = max(dicts, key=len)
print(largest)

#Py_w2_24
d1 = {'one': 1, 'two': 2}
d2 = {'three': 3, 'four': 4}

d1.update(d2)
print(d1)

#Py_w2_25
d = {'a': 1, 'b': 2, 'c': 2, 'd': 3}

unique = list(set(d.values()))
print(unique)

#Py_w2_26
d = {'m': 1, 'n': 2, 'o': 1}

result = {}
for k, v in d.items():
    result.setdefault(v, []).append(k)

print(result)

#Py_w2_27
d = {'x': 100, 'y': 'hello', 'z': 200}

result = {k: v for k, v in d.items() if isinstance(v, int)}
print(result)

#Py_w2_28
words = ['listen', 'silent', 'enlist', 'hello', 'ohlle']

groups = {}
for w in words:
    key = ''.join(sorted(w))
    groups.setdefault(key, []).append(w)

print(list(groups.values()))

#Py_w2_29
num1, num2 = 5, 6

b1 = bin(num1)[2:]
b2 = bin(num2)[2:]

print(sorted(b1) == sorted(b2))

#Py_w2_30
words = ['bat', 'tab', 'eat', 'tea', 'tan', 'nat']

groups = {}
for w in words:
    key = ''.join(sorted(w))
    groups.setdefault(key, []).append(w)

max_size = max(len(v) for v in groups.values())
print(max_size)

#Py_w2_31
nums = [11, 20, 12, 21, 3]

groups = {}
for n in nums:
    s = sum(map(int, str(n)))
    groups.setdefault(s, []).append(n)

print(max(len(v) for v in groups.values()))

#Py_w2_32
d = {'c': [3,1], 'a': [2,4], 'b': [5,1]}

result = [(k, sorted(v)) for k, v in sorted(d.items())]
print(result)

#Py_w2_33
d = {'x': [5,5], 'y': [1,2,3], 'z': [10]}

result = sorted(d.items(), key=lambda x: sum(x[1]))
print(result)

#Py_w2_34
dicts = [{'a': [5,1]}, {'a': [3,4]}, {'a': [7,0]}]
index = 1

result = sorted(dicts, key=lambda x: x['a'][index])
print(result)

#Py_w2_35
d = {'group1': {'b': 2, 'a': 1}, 'group2': {'c': 3, 'd': 0}}

result = {k: sorted(v.items(), key=lambda x: x[1]) for k, v in d.items()}
print(result)

#Py_w2_36
students = ['A', 'B']
subjects = ['math', 'sci']
scores = [[90, 80], [85, 95]]

result = {}
for i, student in enumerate(students):
    result[student] = dict(zip(subjects, scores[i]))

print(result)

#Py_w2_37
nums = [10, 15]

freq = {}
for n in nums:
    for i in range(1, n+1):
        if n % i == 0:
            freq[i] = freq.get(i, 0) + 1

print(freq)

#Py_w2_38
s = "abc"

subs = set()
for i in range(len(s)):
    for j in range(i+1, len(s)+1):
        subs.add(s[i:j])

print(len(subs))