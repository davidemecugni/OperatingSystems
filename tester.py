import sys
import re
import os

def check_exit_progressiveness(filename):
    try:
        with open(filename, 'r') as file:
            lines = file.readlines()
    except FileNotFoundError:
        print(f"File '{filename}' not found.")
        return
    if os.path.splitext(filename)[1] == '.c':
        exit_pattern = re.compile(r'\bexit\((\-?\d+)\);')
        file_type = 'c'
    elif os.path.splitext(filename)[1] == '.sh':
        exit_pattern = re.compile(r'exit (\-?\d+)')
        file_type = 'sh'
    else:
        print("Extension not found")
        exit()
        
    expected_value = 1
    previous_value = None

    for line_number, line in enumerate(lines, start=1):
        match = exit_pattern.search(line)
        if match:
            value = int(match.group(1))
            if value == 0:
                print(f"Exit value 0 at line {line_number}: {line.strip()}")
            elif value != -1:
                if previous_value is not None and value != previous_value + 1:
                    print(f"Progressiveness broken at line {line_number}: {line.strip()}")
                if value != expected_value:
                    print(f"Unexpected exit value at line {line_number}: {line.strip()}")
                expected_value = value + 1
                previous_value = value
            elif value == -1 and file_type == 'c':
                print(f"Exit value -1 at line {line_number}: {line.strip()}")
            else:
                print(f"Error exit value at line {line_number}: {line.strip()}")
    return expected_value - 1

def remove_comments(text):
    pattern = r"(\".*?\"|\'.*?\')|(/\*.*?\*/|//[^\r\n]*$)"
    regex = re.compile(pattern, re.MULTILINE|re.DOTALL)

    def _replacer(match):
        if match.group(2) is not None:
            return "" # so that the newline after the comment start will be preserved
        else:
            return match.group(1) 

    return regex.sub(_replacer, text)

def mallocReadWrite(filename):
    malloc_count = 0
    read_count = 0
    write_count = 0

    with open(filename, 'r') as file:
        text = file.read()
        text = remove_comments(text)
        lines = text.split('\n')
        for line in lines:
            malloc_count += line.count('malloc')
            read_count += line.count('read')
            write_count += line.count('write')

    return malloc_count, read_count, write_count

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: tester.py <filename>")
    else:
        total_exit = check_exit_progressiveness(sys.argv[1])
        print(f"Total exits found: {total_exit}")
        if os.path.splitext(sys.argv[1])[1] == '.c':
            malloc_count, read_count, write_count = mallocReadWrite(sys.argv[1])
            print(f"Malloc count: {malloc_count}")
            print(f"Read count: {read_count}")
            print(f"Write count: {write_count}")
            print(f"Total memory operations: {malloc_count + read_count + write_count}, exits found: {total_exit}")

