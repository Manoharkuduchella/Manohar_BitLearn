"""
#Py_w1_1

#str[start:stop:step] -> dealing with strings
def check_string(str):

    ispalindrome = str == str[::-1]

    n = len(str)

    mid = n//2

    if n%2 == 0:
        first_half = str[:mid]
        second_half = str[mid:]
    else:
        first_half = str[:mid]
        second_half = str[mid+1:]

    is_symmetrical = first_half == second_half

    return ispalindrome, is_symmetrical

print(check_string("madam"))

#Py_w1_2
strg = "hello world"
print(len(strg))
"""
"""
#Py_w1_3
input = "i love python"

tok = input.split()
print(tok)
rev = tok[::-1]
print(rev)
res = " ".join(rev)
print(res)

#Py_w1_4
str = "Python"
i = 2
str = str[:2]+str[4:]
print(str)
"""

"""
#Py_w1_5
def cnt_vowels(i):
    s = set("aeiou")
    cnt = sum(1 for char in i.lower() if char in s)
    return cnt

ip = "education"
res = cnt_vowels(ip)
print(f"Vowels cnt:{res}")

"""
"""
#Py_w1_6

def unique_chars(ip):
    seen = set()
    res = []

    for ch in ip:
        if ch not in seen:
            seen.add(ch)
            res.append(ch)
    return "".join(res)

input = "programming"
out = unique_chars(input)
print(out)
"""
"""
#Py_w1_7
from collections import Counter

s = "statistics"

freq = Counter(s)

min_freq = min(freq.values())

least_freq = [char for char,count in freq.items() if count == min_freq]

print(f"least freq char : {least_freq} with frequency {min_freq}")

#Py_w1_8
from collections import Counter

input_str = "banana"

counts = Counter(input_str)

max_char = counts.most_common(1)[0][0]

print(f"Maximum freq char: '{max_char}'")
"""
"""
#Py_w1_9
text = "hell@123"

if not text.isalnum():
    print("contains")
else:
    print("doesn't contain")

#Py_w1_10

import random
import string

target = "abc"
generated = ""

attempts =0

while generated != target:
    generated = ''.join(random.choices(string.ascii_lowercase, k=len(target)))
    attempts += 1

print(f"Randomly generated '{target}' after {attempts} attempts")
"""
"""
#Py_w1_11
text = "101101"

is_binary = set(text).issubset({'0','1'})

if is_binary:
    print("is binary")
else:
    print("no")


#Py_w1_12
import difflib

target = "apple"
possibilities = ["apply", "apples", "ape", "maple"]

matches = difflib.get_close_matches(target, possibilities, n=2, cutoff=0.6)

print(f"Close matches: {matches}")



#Py_w1_13
str1 = "red blue green"
str2 = "blue yellow red"

set1 = set(str1.split())
set2 = set(str2.split())

uncommon = list(set1 ^ set2)

print(f"Uncommon words: {uncommon}")

#Py_w1_14
text = "23,45.89,78.90"

translation_table = str.maketrans({',': '.', '.': ','})

swapped = text.translate(translation_table)

print(f'"{swapped}"')

#Py_w1_15
from itertools import permutations

text = "abc"

result = [''.join(p) for p in permutations(text)]

print(f"Permutations: {result}")
"""

#Py_w1_16

import re

text = "Check this link: https://openai.com and http://github.com"

url_pattern = r'https?://\S+'

urls = re.findall(url_pattern, text)

print(f"URLs found: {urls}")


"""
#Py_w1_17
code_string = "print(5+2)"

exec(code_string)

#Py_w1_18
text = "python"
length = len(text)
mid = length // 2

if length % 2 == 0:
    middle = text[mid - 1 : mid + 1]
else:
    middle = text[mid]

print(f"Middle character: {middle}")

#Py_w1_19
num = 123
text_num = "456"

int_to_str = str(num)

str_to_int = int(text_num)

print(f"Integer to string: '{int_to_str}'")
print(f"String to integer: {str_to_int}")

#Py_w1_20
text = "dog"
characters = list(text)

print(characters)
"""
"""
#Py_w1_21
chars = ['p', 'y', 't', 'h', 'o', 'n']

result = "".join(chars)
print(f'"{result}"')

#Py_w1_22
fruits = ["pear", "apple", "banana"]

sorted_fruits = sorted(fruits)

print(sorted_fruits)
"""
"""
#Py_w1_23
text = "balloon"

unique_chars = set(text)

print(unique_chars)

#Py_w1_24
def restore_ip_addresses(s):
    res = []
    n = len(s)
    
    # Iterate through possible lengths for the 4 segments (1-3 digits each)
    for i in range(1, 4):
        for j in range(1, 4):
            for k in range(1, 4):
                # Calculate length of the last segment
                l = n - i - j - k
                
                # Check if the 4th segment length is valid (1-3)
                if 1 <= l <= 3:
                    segments = [
                        s[:i], 
                        s[i:i+j], 
                        s[i+j:i+j+k], 
                        s[i+j+k:]
                    ]
                    
                    # Validate each segment: 0-255 and no leading zeros
                    if all(0 <= int(seg) <= 255 and str(int(seg)) == seg for seg in segments):
                        res.append(".".join(segments))
    return res

input_str = "25525511135"
print(f"Possible IP addresses: {restore_ip_addresses(input_str)}")
"""
"""
#Py_w1_25
import re

text = "I have one apple and two oranges."

num_map = {
    "one": "1",
    "two": "2",
    "three": "3",
    "four": "4",
    "five": "5"
}

pattern = re.compile(r'\b(' + '|'.join(num_map.keys()) + r')\b')

result = pattern.sub(lambda x: num_map[x.group()], text)

print(result)
"""
"""
#Py_w1_26
text = "welcome to python"
word = "python"

# .find() returns the starting index of the first occurrence
position = text.find(word)

print(f"Position: {position}")
"""
"""
#Py_w1_27

from itertools import groupby

text = "aabccddd"

result = {char: len(list(group)) for char, group in groupby(text)}

print(result)

#Py_w1_28
text = "hello"
k=3

shifted = text[-k:]+text[:-k]

print(shifted)
"""
"""
#Py_w1_29
text = "abcde"

def count_rotations_to_original(s):
    if not s:
        return 0
    
    original = s
    s = s[1:] + s[0]
    count = 1
    
    while s != original:
        s = s[1:] + s[0]
        count += 1
        
    return count

print(f"Rotations needed: {count_rotations_to_original(text)}")
"""

#Py_w1_30
from collections import Counter

text = "apple apple orange"

word_counts = Counter(text.split())

print(dict(word_counts))
