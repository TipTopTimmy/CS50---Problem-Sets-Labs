import csv
import sys


def main():
    match_database = []
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py DATABASE PATH SEQUENCE PATH")
    # TODO: Read database file into a variable by storing each person as a dictionary
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for name in reader:
            match_database.append(name)
    #print("Database:", match_database)


    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as file:
        dna_sequence = file.read()
    #print("Sequence:", dna_sequence)

    # TODO: Find longest match of each STR in DNA sequence
    STR_types = list(match_database[0].keys())
    STR_types.remove(STR_types[0])
    #print("STR Types:", STR_types)

    pattern_match = []
    for strand in range(0, len(STR_types), 1):
       pattern_match.append(longest_match(dna_sequence, STR_types[strand]))
    #print(pattern_match)

    match_result = dict(zip(STR_types, pattern_match))
    #print(match_result)

    # TODO: Check database for matching profiles
    for dicts in match_database:
        list_dict = list(dicts.values())
        list_dict.remove(list_dict[0])
        list_dict = [int(x) for x in list_dict]
        if list_dict == pattern_match:
            print(dicts["name"])
            return
    print("No match")
    return





def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
