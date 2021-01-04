import string
import re
from cs50 import get_string

def main():

    text = get_string("Text: ")

    letters = len(re.findall('[a-zA-Z]', text))
    words = len(text.split());
    sentences = len(re.findall(r'[.!?]+', text))

    index = readability_index(letters, words, sentences)

    print_grade(index)


def readability_index(letters, words, sentences):

    words_per_100 = words / 100
    l = letters / words_per_100
    s = sentences / words_per_100

    index = round(0.0588 * l - 0.296 * s - 15.8)

    return index


def print_grade(index):
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


main()

