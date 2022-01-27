import platform
import os


def checker(data1, data2, test):  # data1 = bad
    # return True
    return data1 == data2


EXT = '.exe' if platform.system() == 'Windows' else ''
RUN = '' if platform.system() == 'Windows' else './'

print('compiling...')
os.system(f'g++ -std=c++17 -DDEBUG main.cpp -o main{EXT}')
os.system(f'g++ -std=c++17 -DDEBUG main__Good.cpp -o main__Good{EXT}')
os.system(f'g++ -std=c++17 main__Generator.cpp -o testGen{EXT}')
print('compiled!')
test = 1
while True:
    print(f'{test} testing')
    os.system(f'{RUN}testGen{EXT} > task.in')
    # os.system(f'python3 gen.py > task.in')

    os.system(f'{RUN}main{EXT} < task.in > bad.txt')
    # os.system(f'python bad_sol.py < task.in > bad.txt')
    os.system(f'{RUN}main__Good{EXT} < task.in > good.txt')
    # os.system(f'python working_sol.py < task.in > good.txt')
    
    f1 = open('bad.txt', 'r').read().strip()
    f2 = open('good.txt', 'r').read().strip()
    nowTest = open('task.in', 'r').read().strip()
    if not checker(f1, f2, nowTest):
        print('DONE')
        break
    print(f'{test} OK')
    test += 1
