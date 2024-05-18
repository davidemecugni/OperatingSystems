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
                
if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: tester.py <filename>")
    else:
        check_exit_progressiveness(sys.argv[1])
