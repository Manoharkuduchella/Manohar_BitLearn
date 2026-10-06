import re

with open("device.log","r") as lf:
    for line in lf:
        if re.search(r"ERROR",line):
            print(line.strip())
