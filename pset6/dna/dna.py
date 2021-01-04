import csv
import re
from sys import argv, exit


if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

with open(argv[1], newline="") as csvfile:
    database_reader = csv.reader(csvfile, delimiter=",", quotechar="|")
    for i, row in enumerate(database_reader):
        if i == 0:
            with open(argv[2], "r") as txtfile:
                line = next(txtfile)
                longest_strs = []
                for i in range(1, len(row)):
                    pattern = row[i]
                    matches = (
                        match[0] for match in re.finditer(fr"(?:{pattern})+", line)
                    )
                    try:
                        longest = int(len(max(matches, key=len)) / len(pattern))
                        longest_strs.append(longest)
                    except ValueError:
                        longest_strs.append(0)
        else:
            list_database_strs = list(map(int, row[1:]))
            if list_database_strs == longest_strs:
                print(row[0])
                break
    else:
        print("No match")
