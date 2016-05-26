import subprocess
import time

beg = time.time()

num = 1

for i in range(0, num):
	subprocess.call(['./obj'])

end = time.time()

print((end - beg) * 1000 / num)
