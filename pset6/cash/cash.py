def main():
    owed = get_owed()
    coins = calc_coins(owed)
    print(f"{coins}")


def get_owed():
    while True:
        try:
            owed = float(input("Cash owed: "))
            if owed > 0:
                break
        except ValueError:
            None

    return owed


def calc_coins(owed):
    cents = round(owed * 100)
    coins = 0

    while cents > 0:
        if cents >= 25:
            cents -= 25
        elif cents >= 10:
            cents -= 10
        elif cents >= 5:
            cents -= 5
        else:
            cents -= 1
        coins += 1
    return coins


main()