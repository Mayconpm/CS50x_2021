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
} pair;

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
void create_strength_array(int strength[]);
void sort(int array[], int start, int end);
void merge(int array[], int start, int middle, int end);
void print_array(int array[], int array_size);
bool check_cycle(int winner, int loser);

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
    for (int candidate = 0; candidate < candidate_count; candidate++)
    {
        if (strcmp(name, candidates[candidate]) == 0)
        {
            ranks[rank] = candidate;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    int rank_1 = 0;
    int rank_2 = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            rank_1 = ranks[i];
            rank_2 = ranks[j];
            if (rank_1 != rank_2)
            {

                preferences[rank_1][rank_2]++;
            }
            else
            {
                preferences[rank_1][rank_2] = 0;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int comparison_1 = preferences[i][j];
            int comparison_2 = preferences[j][i];
            if (comparison_1 > comparison_2)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (comparison_1 < comparison_2)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int strength_array[pair_count];
    create_strength_array(strength_array);
    sort(strength_array, 0, pair_count - 1);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int winner;
    int loser;
    for (int i = 0; i < pair_count; i++)
    {
        winner = pairs[i].winner;
        loser = pairs[i].loser;
        if (!check_cycle(winner, loser))
        {
            locked[winner][loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int i = 0;
    int j = 0;
    bool edge;
    while (i < candidate_count)
    {
        edge = locked[j][i];
        if (j == candidate_count && !edge)
        {
            printf("%s\n", candidates[i]);
            break;
        }
        else if (!edge)
        {
            j++;
        }
        else
        {
            i++;
            j = 0;
        }
    }
}

void create_strength_array(int strength[])
{
    int winner;
    int loser;
    for (int i = 0; i < pair_count; i++)
    {
        winner = pairs[i].winner;
        loser = pairs[i].loser;
        strength[i] = preferences[winner][loser] - preferences[loser][winner];
    }
}

void sort(int array[], int start, int end)
{
    if (end > start)
    {
        int middle = (start + end) / 2;

        sort(array, start, middle);
        sort(array, middle + 1, end);

        merge(array, start, middle, end);
    }
}

void merge(int array[], int start, int middle, int end)
{
    int i = start;
    int j = middle + 1;
    int k = 0;

    typedef struct
    {
        int winner;
        int loser;
    } pair_temp;

    pair_temp pairs_temp[pair_count];

    while (i <= middle && j <= end)
    {
        if (array[i] >= array[j])
        {
            pairs_temp[k].winner = pairs[i].winner;
            pairs_temp[k].loser = pairs[i].loser;
            i++;
            k++;
        }
        else
        {
            pairs_temp[k].winner = pairs[j].winner;
            pairs_temp[k].loser = pairs[j].loser;
            j++;
            k++;
        }
    }

    while (i <= middle)
    {
        pairs_temp[k].winner = pairs[i].winner;
        pairs_temp[k].loser = pairs[i].loser;
        i++;
        k++;
    }

    while (j <= end)
    {
        pairs_temp[k].winner = pairs[j].winner;
        pairs_temp[k].loser = pairs[j].loser;
        j++;
        k++;
    }
    for (i = start; i <= end; i++)
    {
        pairs[i].winner = pairs_temp[i - start].winner;
        pairs[i].loser = pairs_temp[i - start].loser;
    }
}

void print_array(int array[], int array_size)
{
    for (int i = 0; i < array_size; i++)
    {
        printf("%i ", array[i]);
    }
    printf("\n");
}

bool check_cycle(int winner, int loser)
{
    if (locked[loser][winner] == true)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][winner] == true)
        {
            return check_cycle(i, loser);
        }
    }
    return false;
}