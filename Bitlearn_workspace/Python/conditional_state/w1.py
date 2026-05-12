"""
#Py_w1_1
a = float(input("enter number"))
if a < 3.0:
    print("under voltage")
elif a > 3.3:
    print("Over voltage")
else :
    print("Nominal")

#Py_w1_2
b = 0b10010010
mask = 0x80
if b & mask:
    print("MSB set")
else :
    print("MSB not set")
"""
"""
#Py_w1_3
a = int(input("enter temparature"))
if a > 75:
    print("overheat")
elif a >=25 and a <=75:
    print("Normal")
else:
    print("Low temp")
"""

#Py_w1_4
a ,b = 0,1
print(a and b)
print(a or b)
print(a ^ b)

#Py_w1_8
a = 77

if a >= 192 and a <= 255:
    print("192-255")
elif a >= 128 and a <= 191:
    print("128–191")
elif a >= 64 and a <= 127:
    print("64–127")
elif a >= 0 and a <= 63:
    print("0–63")
else:
    print("its -ve")

#Py_w1_14
mode = 1

match mode:
    case 0:
        print("standby")
    case 1:
        print("active")
    case 2:
        print("fault")


#Py_w1_15
val1 = 98
val2 = 101

if abs(val1-val2) <= 5:
    print("Match")
else:
    print("No Match")
