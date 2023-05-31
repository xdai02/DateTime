import datetime

d = datetime.date.fromordinal(1)
print(d)

d = datetime.date.fromordinal(100)
print(d)

d = datetime.date.fromordinal(1000)
print(d)

d = datetime.date.fromordinal(10000)
print(d)

d = datetime.date.fromordinal(100000)
print(d)

d = datetime.date.fromordinal(730920) # 730920th day after 1. 1. 0001
print(d)

d = datetime.date.fromordinal(740000)
print(d)