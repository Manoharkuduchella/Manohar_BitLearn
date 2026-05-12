"""
#Py_w1_31
text = "my_variable_name"

result = "".join(word.title() for word in text.split("_"))
print(f'"{result}"')


#Py_w1_32
words = ["hello", "world"]
k = 2
char = "r"
target_word = words[k - 1]
position = target_word.find(char)

print(f"Position: {position}")


#Py_w1_33
iput = "abcd"
print(iput[::-1])
"""

"""
#Py_w1_34
text = "I like apples and bananas."
replacements = {"apples": "oranges", "bananas": "grapes"}

for old_word, new_word in replacements.items():
    text = text.replace(old_word, new_word)

print(text)
"""
"""
#Py_w1_35
import string

text = "Hello, world! How are you?"

clean_text = "".join(char for char in text if char not in string.punctuation)

print(clean_text)
"""
"""
#Py_w1_36
str1 = "abcde"
str2 = "cdeab"

is_rotation = len(str1) == len(str2) and str2 in (str1 + str1)

if is_rotation:
    print("Rotationally equivalent: Yes")
else:
    print("Rotationally equivalent: No")
"""
"""
#Py_w1_37
import random

length = 8

binary_string = ''.join(random.choices(['0', '1'], k=length))

print(f'"{binary_string}"')
"""
"""
#Py_w1_38
text = "python"

sorted_chars = sorted(text, reverse=True)

result = "".join(sorted_chars)

print(f'"{result}"')


#Py_w1_39
import re

password = "MyPass123@"

length_ok = len(password) >= 8
has_upper = any(char.isupper() for char in password)
has_lower = any(char.islower() for char in password)
has_digit = any(char.isdigit() for char in password)
has_special = bool(re.search(r"[!@#$%^&*(),.?\":{}|<>]", password))

# Check if all conditions are met
if all([length_ok, has_upper, has_lower, has_digit, has_special]):
    print("Valid password: Yes")
else:
    print("Valid password: No")
"""
"""
#Py_w1_40
text = "cat"
length = 6
pad_char = "*"

result = text.rjust(length, pad_char)

print(f'"{result}"')


#Py_w1_41
text = "E = mc2"

superscript_map = str.maketrans("0123456789", "⁰¹²³⁴⁵⁶⁷⁸⁹")

result = text.translate(superscript_map)

print(f'"{result}"')
"""
"""
#Py_w1_42
import string

text = "The quick brown fox jumps over the lazy dog"

letters_in_text = set(char.lower() for char in text if char.isalpha())

is_pangram = len(letters_in_text) == 26

print(f"Is pangram: {'Yes' if is_pangram else 'No'}")


#Py_w1_43
dates = ["2021-05-21", "2019-01-12", "2020-12-15"]

sorted_dates = sorted(dates)

print(sorted_dates)
"""
"""
#Py_w1_44
text = "abcdefgh"
n = 3

chunks = [text[i : i + n] for i in range(0, len(text), n)]

print(chunks)

#Py_w1_45
text = "abracadabra"
sub = "abra"
positions = []
start = 0

while True:
    pos = text.find(sub, start)
    
    if pos == -1:
        break
        
    positions.append(pos)
    start = pos + 1 

print(positions)
"""
"""
#Py_w1_46
text = "abcdeFGhiJK"
sub = "FG"

before, match, after = text.partition(sub)

result = before + match

print(f'"{before}"')
"""
"""
#Py_w1_47
def simplify(s):
    n = len(s)
    for i in range(1, n // 2 + 1):
        if n % i == 0:
            pattern = s[:i]
            if pattern * (n // i) == s:
                return pattern
    return s

input_list = ["hellohello", "world", "testtesttest"]
output = [simplify(s) for s in input_list]

print(output)
"""
#Py_w1_48
items = ["applebanana", "apple", "banana", "applebananacherry"]
substrings = ["apple", "banana"]

result = [item for item in items if all(sub in item for sub in substrings)]

print(result)


