# import subprocess

# subprocess.run(["ls","-al"])

# import subprocess

# result = subprocess.run(["ls","-al"],capture_output=True,text=True)

# print(result.stdout)

# import subprocess

# res = subprocess.run(["ls"],capture_output=True,text=True)

# print(res.returncode)


# import subprocess

# res = subprocess.run(["sudo","dmesg"],capture_output=True,text=True)

# print(res.stdout)


# import subprocess

# res = subprocess.run(["lsmod"],capture_output=True,text=True)

# print(res.stdout)

# if "i2c_i801" in res.stdout:
#     print("i2c_i801 loaded...")


# import subprocess

# res = subprocess.run("sudo dmesg | tail -10",shell=True,capture_output=True,text=True)

# print(res.stdout)


# import subprocess

# res = subprocess.run(["cat","missing.txt"],capture_output=True,text=True)

# print(res.stderr)



# import subprocess

# try:
#     res = subprocess.run(["false"],check=True)
# except subprocess.CalledProcessError:
#     print("Command failure")

# import subprocess
# import re

# res = subprocess.run(["sudo","dmesg"],capture_output=True,text=True)

# logs = res.stdout

# r = re.search("^*wlp0s20f3: associated.*$",logs,re.M)
# print(r.group())


# import subprocess

# logs = subprocess.run(["sudo","dmesg"],capture_output=True,text=True).stdout

# with open("dmesg_log.txt","w") as lf:
#     lf.write(logs)



# import subprocess

# modules = subprocess.run(["lsmod"],capture_output=True,text=True).stdout

# if "intel_lpss" in modules:
#     print("intel_lpss loaded..")
# else:
#     print("intel_lpss not loaded...")


import subprocess

res = subprocess.run(["uname","-r"],capture_output=True,text=True).stdout

print(res.strip())