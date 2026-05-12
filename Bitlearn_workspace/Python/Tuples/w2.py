#Py_w1_31
t1 = (1, 2, 3, 4)
t2 = (3, 5, 2, 1)
t3 = (2, 2, 3, 1)

result = tuple(a + b + c for a, b, c in zip(t1, t2, t3))
print(result) 

#Py_w1_32
t = (4, 3, 2, 2, -1, 18)

product = 1
for num in t:
    product *= num

print(product)   
#Py_w1_33
t = (1, 2, 3)

result = int(''.join(map(str, t)))
print(result)

#Py_w1_34
t = (('item1', '12.20'), ('item2', '15.10'), ('item3', '24.5'))

result = sorted(t, key=lambda x: float(x[1]), reverse=True)
print(result)

#Py_w1_35
t1 = (1, 2)
t2 = (3, 4)

result = [(a, b) for a in t1 for b in t2]
print(result)

#Py_w1_36
t = (1, 2, 2, 3, 3, 3)

freq = {}
for num in t:
    freq[num] = freq.get(num, 0) + 1

print(freq)

#Py_w1_37
lst = [(1, 2, 3), (4, 5), (6, 7, 8)]

result = [x for x in lst if len(x) == 3]
print(result)  

#Py_w1_38
t = (('Red', 'White', 'Blue'),
     ('Green', 'Pink', 'Purple'),
     ('Orange', 'Yellow', 'Lime'))

value = 'White'

result = any(value in inner for inner in t)
print(result)   

#Py_w1_39
t = (('a', 1), ('b', 2), ('c', 3))

result = dict(t)
print(result) 


#Py_w1_40
t1 = (1, 2, 3)
t2 = (2, 2, 2)

and_result = tuple(a & b for a, b in zip(t1, t2))
xor_result = tuple(a ^ b for a, b in zip(t1, t2))

print("AND:", and_result) 
print("XOR:", xor_result)   
