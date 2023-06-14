# TODO

def main():
    user_string = input("Text:")

    words = count_words(user_string)
    #print("words:", words)
    sentences = count_sentences(user_string)
    #print("sentences: ", sentences)
    letters = letter_count(user_string)
    #print("letters: ", letters)
    score = Coleman_Liau(letters, words, sentences)

    grade_level(round(score))


##Count the number of spaces in string
def count_words(string):
    spaces = 1
    for i in range(0, len(string)):
        if (string[i] == " "):
            spaces += 1
    #print(spaces)
    return spaces


##Count the number of sentences per string
def count_sentences(string):
    punctuation = 0
    for i in range (0, len(string)):
        if (string[i] == '.' or string[i] =='?' or string[i] == '!'):
            punctuation +=1
    #print(punctuation)
    return punctuation


def letter_count(string):
    alpha_count =0
    for i in range(0, len(string)):
        if((ord(string[i]) >= 65 and ord(string[i])<=90) or (ord(string[i]) >= 97 and ord(string[i]) <= 122)):
            alpha_count += 1
    return alpha_count

"""##Count additional punctuation
def other_punct(string):
    punctuation = 0
    for i in range(0, len(string)):
        if (string[i] == "," or string[i] == ';' or string[i] ==':' or string[i] == '"'):
            punctuation+=1
    return punctuation"""


def Coleman_Liau(letters, words, sentences):
    L = letters / words * 100
    S = sentences / words * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    return round(index)

def grade_level(index):

    if (index > 16):
        print("Grade 16+")
        return
    elif (index < 1):
        print("Before Grade 1")
        return
    else:
        print(f"Grade {index}")
        return

if __name__ == "__main__":
    main()
