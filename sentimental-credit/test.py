

#take input
def main():
    card_num_str = input("Card number: ")
    card_num_int = int(card_num_str)
    if (calc_checksum(card_num_int) == True):
        card_type(card_num_str)
    else:
        print("INVALID")


def calc_checksum(card_number):
    i = 0
    odd_sum = 0
    even_sum = 0
    final_sum = 0
    check_sum = 0
    first_digit = 0
    second_digit = 0
    digit = 0

    while (card_number > 0):
            i+=1
            digit = card_number %10

            if( i % 2 == 1):
                odd_sum = odd_sum + digit
            else:
                mod_even = digit * 2
                even_sum = int(mod_even / 10 + even_sum)
                even_sum = mod_even % 10 + even_sum
            card_number = int(card_number / 10)
            second_digit = first_digit
            first_digit = digit
            final_sum = even_sum + odd_sum
            check_sum = final_sum % 10

    if (check_sum == 0):
        return True
    else:
        return False

def card_type(card_number):
    card_length = len(card_number)

    if (card_number[0] == '4' and (card_length == 13 or card_length == 16)):
        print("VISA")
        return
    elif (card_number[0] == '3' and (card_number[1] == '4' or card_number[1] == '7')):
        print("AMEX")
        return
    elif (card_number[0] == '5' and (card_number[1] >= '1' and card_number[1] <= '5' )):
        print("MASTERCARD")
        return

if __name__ == "__main__":
    main()