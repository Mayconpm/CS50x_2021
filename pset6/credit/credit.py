def main():
    card_number = get_card()
    checksum = calc_checksun(card_number)
    check_card_type(card_number, checksum)


def get_card():
    while True:
        card_number = input("Number: ")
        if card_number.isnumeric():
            break

    return card_number


def calc_checksun(card_number):
    even_sum = 0
    odd_sum = 0
    card_number = reversed([int(digit) for digit in card_number])
    for i, digit in enumerate(card_number):
        if (i + 1) % 2 == 0:
            odd_digit = digit * 2
            if odd_digit > 9:
                odd_sum += int(odd_digit / 10) + odd_digit % 10
            else:
                odd_sum += odd_digit
        else:
            even_sum += digit
    checksum = even_sum + odd_sum
    return checksum


def check_card_type(card_number, checksum):
    start_number = int(card_number[0:2])
    card_lenght = len(card_number)
    checksum_last_digit = checksum % 10

    if checksum_last_digit == 0:
        if start_number in [34, 37] and card_lenght == 15:
            print("AMEX")
        elif (int(card_number[0]) == 4) and card_lenght in [13, 16]:
            print("VISA")
        elif (start_number in range(51, 56)) and card_lenght == 16:
            print("MASTERCARD")
        else:
            print("INVALID")
    else:
        print("INVALID")


main()
