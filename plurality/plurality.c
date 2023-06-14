#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    //Iterate through candidates.name structs and compare vote to candidate names.
   for (int i = 0; i < candidate_count; i++)
   {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes ++;
            //printf("Candidate: %s \n", candidates[i].name);
            //printf("Number of Votes: %i \n", candidates[i].votes);
            return true;
        }

   }
    return false;


}
// Print the winner (or winners) of the election
void print_winner(void)
{
    candidate winner[MAX] = { 0 };
    // TODO
    winner[0] = candidates[0];
    for (int i = 0; i < candidate_count-1; i++)     //This loops through the number of iterations required for a full sort.
    {
        for (int j = 0; j < candidate_count-1; j++) //This loops through the candidates to scompare and sort adjacent candidates.
        {
            if (candidates[j].votes < candidates[j+1].votes)
            {
                winner[j] = candidates[j+1];
                candidates[j+1] = candidates[j];
                candidates[j] = winner[j];
            }
        }

    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == candidates[0].votes)
        {
            printf ("%s\n", candidates[i].name);
        }

    }
}

