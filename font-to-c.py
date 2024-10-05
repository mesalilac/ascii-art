# convert font.ascii to c code

file_name = "banner-font.ascii"
const_name = "DEFAULT_FONT"


def main():
    print(f"const char {const_name}[] = ")
    with open(file_name, "r") as f:
        for line in f.readlines():
            line = line.replace("\n", "")
            print(f'"{line}\\n"', end="")
        print(";", end="")


if __name__ == "__main__":
    main()
