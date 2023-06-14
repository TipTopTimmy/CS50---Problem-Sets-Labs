# TODO
def main():
    height = get_height()

    constant = height
    builder(height, constant)

def builder(blocks, constant):

    if blocks == 0:
        return

    builder(blocks-1, constant)

    for i in range(constant-blocks, 0, -1):
        print(" ", end="")

    for i in range(0, blocks, 1):
        print("#", end="")

    print("  ", end="")

    for i in range(0, blocks, 1):
        print("#", end="")

    print()


def get_height():
    while True:
        try:
            n = int(input("Pyramid Height: "))
            if n > 0 and n < 9:
                return n
        except ValueError:
            print("Invalid Input")

if __name__ == "__main__":
    main()