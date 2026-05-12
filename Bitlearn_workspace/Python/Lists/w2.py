"""
#Py_w2_1
numbers = [1, 2, 3, 4, 5]
total = sum(numbers)
print(total)

#Py_w2_2
import math

numbers = [1, 2, 3, 4]
result = math.prod(numbers)
print(result)


#Py_w2_3
numbers = [1, 2, 3, 4, 5]
largest = max(numbers)

print(largest)

#Py_w2_4
numbers = [1, 2, 3, 4, 5]
largest = min(numbers)

print(largest)

#Py_w2_5
words = ['abc', 'xyz', 'aba', '1221']
count = sum(1 for word in words if len(word) >= 2 and word[0] == word[-1])

print(count)

#Py_w2_6
data = [(2, 5), (1, 2), (4, 4), (2, 3), (2, 1)]

out = sorted(data, key=lambda x: x[-1])
print(out)
"""
"""
#Py_w2_7
def remove_duplicates(input_list):
    seen = set()
    result = []
    for item in input_list:
        if item not in seen:
            result.append(item)
            seen.add(item)
    return result

sample_input = [1, 2, 3, 2, 4, 3, 5]
print(remove_duplicates(sample_input))

#Py_w2_8
def check_empty(my_list):
    if not my_list:
        print("List is empty")
    else:
        print("List is not empty")


sample_input = []
check_empty(sample_input) 
"""
"""
#Py_w2_9
original_list = [1, 2, 3, 4]
copied_list = original_list[:]

print(copied_list)

#Py_w2_10
def filter_long_words(words, n):
    return [word for word in words if len(word) > n]

words_list = ['hello', 'world', 'python', 'is', 'great']
n = 4

print(filter_long_words(words_list, n))

#Py_w2_11
def find_common(list1, list2):
    common = set(list1) & set(list2)
    return list(common)

list_a = [1, 2, 3, 4]
list_b = [3, 4, 5, 6]

print(find_common(list_a, list_b))

#Py_w2_12
def flatten_list(nested_list):
    return [item for sublist in nested_list for item in sublist]

sample_input = [[1, 2], [3, 4], [5, 6]]
print(flatten_list(sample_input))


#Py_w2_13
squares = [x**2 for x in range(1, 11)]
print(squares)

#Py_w2_14
def get_even_numbers(numbers):
    return [n for n in numbers if n % 2 == 0]

sample_input = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

print(get_even_numbers(sample_input))

#Py_w2_15
def remove_all(input_list, target):
    return [x for x in input_list if x != target]

nums = [1, 2, 3, 2, 4, 2, 5]
to_remove = 2

print(remove_all(nums, to_remove))

#Py_w2_16
def insert_element(my_list, element, position):
    my_list.insert(position, element)
    return my_list

nums = [1, 2, 3, 4]
elem = 5
pos = 2

print(insert_element(nums, elem, pos))

#Py_w2_17
def lists_to_dict(keys, values):
    return dict(zip(keys, values))

keys_list = ['a', 'b', 'c']
values_list = [1, 2, 3]

print(lists_to_dict(keys_list, values_list))
"""
"""
#Py_w2_18
def unzip_list(tuple_list):
    list1, list2 = zip(*tuple_list)
    return list(list1), list(list2)

sample_input = [(1, 'a'), (2, 'b'), (3, 'c')]

result1, result2 = unzip_list(sample_input)
print(result1, result2)

#Py_w2_19
result = [x**2 if x % 2 == 0 else x**3 for x in range(1, 21)]

print(result)

#Py_w2_20
matrix = [[i for _ in range(3)] for i in range(3)]
print(matrix)

#Py_w2_21
def reverse_at_position(my_list, position):
    return my_list[:position] + my_list[position:][::-1]

nums = [1, 2, 3, 4, 5, 6]
pos = 3

print(reverse_at_position(nums, pos))
"""

#Py_w2_22

"""
#Py_w2_23
import itertools
def get_permutations(my_list):
    return [list(p) for p in itertools.permutations(my_list)]

sample_input = [1, 2, 3]

print(get_permutations(sample_input))


#Py_w2_24
def find_kth_smallest(nums, k):
    sorted_nums = sorted(nums)
    return sorted_nums[k-1]

nums = [7, 10, 4, 3, 20, 15]
k = 3

print(find_kth_smallest(nums, k))

#Py_w2_25
def is_palindrome(my_list):
    return my_list == my_list[::-1]

sample_input = [1, 2, 3, 2, 1]

print(is_palindrome(sample_input))

#Py_w2_26
def get_union_intersection(list1, list2):
    set1 = set(list1)
    set2 = set(list2)

    union = list(set1 | set2)

    intersection = list(set1 & set2)
    
    return union, intersection

list_a = [1, 2, 3, 4]
list_b = [3, 4, 5, 6]

u, i = get_union_intersection(list_a, list_b)

print(f"Union: {u}")
print(f"Intersection: {i}")
"""

#Py_w2_27
def remove_duplicates_ordered(input_list):
    seen = set()
    result = []
    for item in input_list:
        if item not in seen:
            result.append(item)
            seen.add(item)
    return result

sample_input = [1, 2, 2, 3, 4, 4, 5, 6, 5]

print(remove_duplicates_ordered(sample_input))

#Py_w2_28
def max_sum_subsequence(nums):
    positive_nums = [x for x in nums if x > 0]
    return sum(positive_nums) if positive_nums else max(nums)

sample_input = [2, -1, 2, 3, 4, -5]

print(max_sum_subsequence(sample_input))

