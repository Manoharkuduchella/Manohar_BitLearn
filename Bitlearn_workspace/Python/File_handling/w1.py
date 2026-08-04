# try:
#     with open("log.txt","r") as f:
#         print(f.read())
    
# except FileNotFoundError:
#     print("File missing")

# #reading and printing line
# with open("log.txt","r") as f:
#     for line in f:
#         print(line, end="")

#search for a pattern in logs
# pattern = "timeout"

# with open("uart.log","r") as f:
#     for lineno, line in enumerate(f,start=1):
#         if pattern in line.lower():
#             print(f"Line {lineno}: {line.strip()}")

# #copying a file from srcfile to destfile
# with open("uart.log","r") as uf, open("log.txt","a") as lf:
#     for line in uf:
#         lf.write(line)

#list and changing directories
# import os

# print(os.getcwd())

# os.chdir("/home/manohar/Manohar_BitLearn/Bitlearn_workspace")
# print(os.getcwd())

# files = os.listdir()
# print(files)

# #executing cmds
# import os

# os.system("ls")


# import os

# if os.path.exists("log.txt"):
#     print("Exists")
# else:
#     print("Missing")


# #csv files reading
# import csv

# with open("firm.csv") as firmf:
#     reader = csv.reader(firmf)

#     for row in reader:
#         print(row)

#csv files writing
# import csv

# tests = [("spi_thread","46","PASS"),
#         ("i2c_thread","47","FAIL"),("uart_thread","55","PASS")]

# with open("firm_res.csv","a") as fres:
#     writer = csv.writer(fres)

#     writer.writerow(["Thread", "Irqno", "Status"])
#     writer.writerows(tests)

# #csv files and dictionaries
# import csv

# with open("firm_res.csv",newline="") as file:

#     reader = csv.DictReader(file)

#     for r in reader:
#         print(r["Thread"],end=" ")
#         print(r["Status"])


#compare two register dumps
import csv

before = {}

with open("Uart_before.csv",newline="") as file:
    reader = csv.DictReader(file)

    for row in reader:
        before[row["Address"]] = row["Value"]


with open("Uart_after.csv", newline="") as file:
    reader = csv.DictReader(file)

    for row in reader:
        if before[row["Address"]] != row["Value"]:
            print(row["Address"],before[row["Address"]],"->",row["Value"])