# import re

# with open("bbb.log","r") as log:
#     for line in log:
#         if re.search(r"probe",line):
#             print(line)

# import re

# text = "GPIO Error"

# print(re.match("Error",text)) #matches from the beginning returns None

# print(re.match("GPIO",text)) #matches from the beginning returns object


# import re

# text = "GPIO UART GPIO SPI GPIO CAN"

# list = re.findall("GPIO",text)

# print(len(list))



# import re

# text = "GPIO SPI GPIO CAN GPIO"

# for st in re.finditer("GPIO",text):
#     print(st,":",st.start(),st.end())

# import re

# text = """The rain in spain
# The spain in rain 
# The spain
# spain."""

# text2 = "The rain in spain"

# res = re.findall("^The.*spain$",text, re.MULTILINE)
# print(res)

# for line in res:
#     print(line)

# res = re.search("^The.*Spain$",text2,re.I)
# print(res.span())
# print(res.group())

# import re

# text = "The rain in Spain"

# match = re.search("\s",text)

# print(match.start())


# import re

# text = "GPIO21 UART7 UART5"

# res = re.findall(r"\d+",text)

# print(res)

# import re

# text = "GPIO21 UART7 UART5"

# res = re.findall("[a-zA-Z]+",text)

# print(res)


# import re

# text = "Address=0x1004 Value=0xAB"

# res = re.findall("0x[0-9a-fA-F]+",text)

# print(res)

# import re

# text = "GPIO12 GPIO13 GPIO4"

# match = re.search("GPIO(\d+)",text)

# print(match.group(1))

# import re

# text = "GPIO=0x10 UART=0xAB SPI=0xFF"

# lm = re.findall("0x[0-9A-Fa-f]+",text)

# print(lm)


# import re

# text = "gpio_driver: probe successful"

# m = re.search("(\w+):",text)

# print(m.string)
# print(m.groups())

# import re

# text = "Linux device driver"

# res = re.sub("Linux","Windows",text)

# print(res)



# import re

# text = "Version 5.10"

# res = re.sub("\d","x",text)

# print(res)


# import re

# text = "Hello   World"

# res = re.sub("\s+"," ",text)

# print(res)


# import re

# text = "Hello python world"

# res = re.split("o",text)

# print(res)

import re

text = "one,two;three four"

res = re.split("[,; ]",text)

print(res)