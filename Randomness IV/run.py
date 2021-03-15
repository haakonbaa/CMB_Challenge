import time
from subprocess import Popen, PIPE

correct = [
    (b"1\n20 3 365\n","3 5 7"),
    (b"1\n20 3 500\n","3 1 8"),
    (b"2\n560 12 343\n357 2 232\n","5 164 337\r\n9 15 104")
]

timedata = [
    b"1\n20 3 365\n",
    b"1\n20 3 500\n",
    b"2\n560 12 343\n357 2 232\n",
    b"1\n1000 6 343\n"
]

def timer(func):
    _start = time.time()
    func()
    return time.time()-_start

def execute():
    for data in timedata:
        sub = Popen(["smart.exe"],stdout=PIPE,stdin=PIPE).communicate(data)
        sub[0].decode()


if __name__ == "__main__":
    for inp, outp in correct:
        sub = Popen(["smart.exe"],stdout=PIPE,stdin=PIPE).communicate(inp)
        if not (sub[0].decode().strip() == outp):
            print(bytes(sub[0].decode().strip(),"utf-8"))
            print(bytes(outp,"utf-8"))
            print("TEST FAILED! ABORT!\n")

    total = 0
    for i in range(100):
        total += timer(execute)
    

    print(f"Average time {total / 100} seconds.")


# text = b"1\n20 3 365\n"

# sub = Popen(["smart.exe"],stdout=PIPE,stdin=PIPE).communicate(text)
# print(sub[0].decode())



