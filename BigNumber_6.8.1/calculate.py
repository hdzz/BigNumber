#! /usr/bin/py
import subprocess, time

TNUM = 8

a1 = []
a2 = []

for i in range(0, TNUM):
	num = i * 12500
	a1.append(num)
	a2.append(12500 + num)

T = []

while True:
	for i in range(0, TNUM):
		start = time.time()
		for j in range(0, 10):
			subprocess.call(['./obj', str(a1[i]), str(a2[i])])
		end = time.time()
		T.append(int((end - start) * 1000))
	count = 0
	for each in T:
		count += each
	average = count / TNUM
	for i in range(0, TNUM):
		if T[i] < average:
			a2[i] += 500
			a1[i + 1] -= 500


print(T)
