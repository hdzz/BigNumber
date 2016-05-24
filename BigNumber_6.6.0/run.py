import subprocess, time

start = time.time()

num = 10

for i in range(0, num):
	subprocess.call(['./obj'])

end = time.time()

print((end - start) * 1000 / num)
