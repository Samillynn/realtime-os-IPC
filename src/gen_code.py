import sys

mode = sys.argv[1]
if mode == "ldp":
    for i in range(1, 30, 2):
        print(f"ldp x{i}, x{i + 1}, [x0], #16")

if mode == "ldr":
    for i in range(1, 31):
        print(f"ldr x{i}, [x0], #8")

if mode == "stp":
    for i in range(1, 30, 2):
        print(f"stp x{i}, x{i + 1}, [x0], #16")

if mode == "str":
    for i in range(1, 31):
        print(f"str x{i}, [x0], #8")

