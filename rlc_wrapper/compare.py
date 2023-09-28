from subprocess import run
import time
import matplotlib.pyplot as plt

repeat_count=10

runtimes = {'bin/fuzzer_static_4': [], 'bin/fuzzer_static_64': [], 'bin/fuzzer_dynamic': []}

suit_count_values = [2 ** i for i in range(10)]

for suit_count in suit_count_values:
    run(['make', 'clean'])
    run(['make', f'SUIT_COUNT={suit_count}'])
    for fuzzer_name in ['bin/fuzzer_static_4', 'bin/fuzzer_static_64', 'bin/fuzzer_dynamic']:
        start = time.time()
        for i in range(repeat_count):
            run(f'{fuzzer_name} -detect_leaks=0 >/dev/null 2>&1', shell=True)
        end = time.time()
        avg = (end - start) / repeat_count
        runtimes[fuzzer_name].append(avg)


fig, ax = plt.subplots() 
ax.plot(suit_count_values, runtimes['bin/fuzzer_static_4'], 'g-', label='static 4 bits')
ax.plot(suit_count_values, runtimes['bin/fuzzer_static_64'], 'b-', label='static 64 bits')
ax.plot(suit_count_values, runtimes['bin/fuzzer_dynamic'], 'r-', label='dynamic')
ax.legend()
plt.savefig('plot.png')
print(runtimes)