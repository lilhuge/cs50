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
        for (int rank = 0; rank < candidate_count; rank++)
        {
            string name = get_string("Rank %i: ", rank + 1);

            if (!vote(rank, name, ranks))
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
    for (int k = 0; k < candidate_count; k++)     // Run through all candidates
    {
        if (strcmp(name, candidates[k]) == 0)
        {
            ranks[rank] = k;                    // Updates rank
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int j = 0; j < candidate_count; j++)                   
    {
        for (int k = 0; k < candidate_count; k++)
        {
            if (ranks[j] == k)
            {
                for (int l = j + 1; l < candidate_count; l++)
                {
                    for (int m = 0; m < candidate_count; m++)
                    {
                        if (ranks[l] == m)                          // If match
                        {
                            preferences[k][m]++;                    // Update preferences
                        }
                    }
                }
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int a = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])      // If winner and not draw
            {
                pairs[a].winner = i;                        // Assign winner and loser to pairs array
                pairs[a].loser = j;
                a++;                                        // Increase array index
            }
        }
    }
    pair_count = a;                                         // Update pair count
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{

    for (int i = 0; i < (candidate_count * (candidate_count - 1) / 2) - 1; i++)         // Use select sort algorithm to sort pairs
    {
        int max_idx = i;
        for (int j = i + 1; j < (candidate_count * (candidate_count - 1) / 2); j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[i].winner][pairs[i].loser])
            {
                max_idx = j;
            }
        }
        pair temp = pairs[i];               // Code to swap appropriate pairs for reordering
        pairs[i] = pairs[max_idx];
        pairs[max_idx] = temp;

    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    for (int n = 0; n < (candidate_count * (candidate_count - 1) / 2); n++)
    {
        locked[pairs[n].winner][pairs[n].loser] = true;                         // Adds arrow in order of pairs array
        int start = pairs[n].winner;

        for (int j1 = 0; j1 < candidate_count; j1++)    // Checks for cycles by running through all possible paths of up to 9 in length
        {
            if (locked[pairs[n].loser][j1] == true)
            {
                if (j1 == start)                                    // If path leads back to starting position, then remove the last arrow as cycle is present
                {
                    locked[pairs[n].winner][pairs[n].loser] = false; // loop is present
                }
                else
                {
                    for (int j2 = 0; j2 < candidate_count; j2++)            // Else carry on down path
                    {
                        if (locked[j1][j2] == true)
                        {
                            if (j2 == start)
                            {
                                locked[pairs[n].winner][pairs[n].loser] = false; // loop is present
                            }
                            else
                            {
                                for (int j3 = 0; j3 < candidate_count; j3++)
                                {
                                    if (locked[j2][j3] == true)
                                    {
                                        if (j3 == start)
                                        {
                                            locked[pairs[n].winner][pairs[n].loser] = false; // loop is present
                                        }
                                        else
                                        {
                                            for (int j4 = 0; j4 < candidate_count; j4++)
                                            {
                                                if (locked[j3][j4] == true)
                                                {
                                                    if (j4 == start)
                                                    {
                                                        locked[pairs[n].winner][pairs[n].loser] = false; // loop is present
                                                    }
                                                    else
                                                    {
                                                        for (int j5 = 0; j5 < candidate_count; j5++)
                                                        {
                                                            if (locked[j4][j5] == true)
                                                            {
                                                                if (j5 == start)
                                                                {
                                                                    locked[pairs[n].winner][pairs[n].loser] = false; // loop is present
                                                                }
                                                                else
                                                                {
                                                                    for (int j6 = 0; j6 < candidate_count; j6++)
                                                                    {
                                                                        if (locked[j5][j6] == true)
                                                                        {
                                                                            if (j6 == start)
                                                                            {
                                                                                locked[pairs[n].winner][pairs[n].loser] = false; // loop is present
                                                                            }
                                                                            else
                                                                            {
                                                                                for (int j7 = 0; j7 < candidate_count; j7++)
                                                                                {
                                                                                    if (locked[j6][j7] == true)
                                                                                    {
                                                                                        if (j7 == start)
                                                                                        {
                                                                                            locked[pairs[n].winner][pairs[n].loser] = false; // loop is present
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            for (int j8 = 0; j8 < candidate_count; j8++)
                                                                                            {
                                                                                                if (locked[j7][j8] == true)
                                                                                                {
                                                                                                    if (j8 == start)
                                                                                                    {
                                                                                                        locked[pairs[n].winner][pairs[n].loser] = false; // loop is present
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }

                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    string winner;
    for (int j = 0; j < candidate_count; j++)       
    {
        int count_false = 0;
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j] == false)          // Identify candidate with no arrows in
            {
                count_false++;
            }
        }
        if (count_false == candidate_count)
        {
            winner = candidates[j];             // Declare winners if multiple
        }
    }
    printf("%s\n", winner);                     // Print (multiple) winners
    return;
}

