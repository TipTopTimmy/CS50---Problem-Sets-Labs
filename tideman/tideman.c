//personal access token: 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
#include <cs50.h>
#include <stdio.h>
#include <string.h>
// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle( int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

        if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    //Look for a candidates name i.e. iterate through candidates[] & update candidate ranking for this voter.
    for(int i = 0; i < candidate_count; i++)
    {
        if(strcmp(candidates[i], name) ==  0)//if name is found in array update ranks and return true
        {
            ranks[rank] = i;  //ranks[rank] = where j is the input of int rank of vote function. i represents the place value in the candidates array associated with candidate preference for that voter.

/*            for (int j = 0; j < candidate_count; j++)
            {
                printf("Rank Value: %i \n", ranks[j]);

            }
*/
            return true;
        }
    }



    // Candidate name not found in candidates[] & Return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for(int i = 0; i < candidate_count-1; i++ )           // because j = i+1 candidate count mush be restricted
    {
        for(int j = i+1; j < candidate_count; j++)      // voter prefers candidate i to candidate j
        {
            preferences[ranks[i]][ranks[j]]++;          //updates preferences[][] using ranks

        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //loop through preferences[][] to determine winners and losers  and update the global pair count.
    for( int i = 0; i < candidate_count; i++)
    {
        for( int j = 0; j < candidate_count; j++)
        {
            if( preferences[i][j] > preferences[j][i])  //compares votes of one candidate to another. If preferences[i][j] < preferences[j][i] the appropriate winner will be named as the for loop intereates
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory

void sort_pairs(void)
{
    // TODO
    int margin[pair_count];

    //determine margin of victory by subtracting prefs[winner][loser] from prefs[loser][winner]. Store result in array
    for( int i = 0; i < pair_count; i++ )
    {
        margin[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];

    }

    //use margin of victory to sort pairs[]
    for( int i = 0; i < pair_count; i++)
    {
        for( int j = 0; j < pair_count-1; j++)
        {
            if ( margin[j] < margin[j+1] )
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j+1];
                pairs[j+1] = temp;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for( int i = 0; i < pair_count; i++)
    {
        if (!cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        else
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    int counter = 0;
    for(int i=0; i<candidate_count; i++)
    {
        counter = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                counter++;
                if (counter == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }

    }
    return;
}

bool cycle(int winner, int loser)
{
    if (loser == winner)
    {
        // If the current loser is the cycle start
        // The entry makes a circle
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (cycle(winner, i))
            {
                // Forward progress through the circle
                return true;
            }
        }
    }

    return false;
}
/*/DEBUG
for(int i=0; i<candidate_count;i++)
{
    for(int j=0; j< candidate_count; j++)
    {
        printf("%i ", locked[i][j]);
    }
    printf("\n");
}
//DEBUG END*/