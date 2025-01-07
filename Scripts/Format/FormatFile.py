import os
import sys
import subprocess


file_types = [
    ".h",
    ".cpp",
    ]


def check_need_format(file_name):
    for type in file_types:
        if file_name.lower().endswith(type):
            return True
    return False


def format_dir(root_dir):
    if os.path.exists(root_dir) == False:
        print("[error] not exist dir: ", root_dir)
    for root, dirs, files in os.walk(root_dir):
        for file in files:
            if check_need_format(file):
                filename = os.path.join(root, file)
                print("Format ", filename)
                subprocess.check_call(args=['clang-format', '-i', filename])


if __name__ == "__main__":
    if len(sys.argv) == 1:
        dir = os.getcwd() + '/Source'
    else:
        dir = sys.argv[1]
    format_dir(dir)
    sys.exit(0)
