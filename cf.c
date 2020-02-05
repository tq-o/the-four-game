#include <stdio.h>
#include <stdlib.h>

//Print out gameboard initial state, passing in gameboard and list of moves:
void initialBoard(char gameboard[6][7], char move[])
{
    char letter = 'A';
    int number = 6;
    for (int a = 0; a < 7; a++)
    {
        for (int b = 0; b < 8; b++)
        {
            if (a == 0 & b == 0)
                printf("  ");
            else if (a == 0)
            {
                printf(" %c", letter);
                letter++;
            }
            else if (b == 0)
            {
                printf(" %i", number);
                number--;
            }
            else
            {
                gameboard[a - 1][b - 1] = '.';
                printf(" %c", gameboard[a - 1][b - 1]);
            }
        }
        printf("\n");
    }
}

//Change and print the state of the game, passing in gameboard:
void board(char gameboard[6][7])
{
    char letter = 'A';
    int number = 6;

    for (int a = 0; a < 7; a++)
    {
        for (int b = 0; b < 8; b++)
        {
            if (a == 0 & b == 0)
                printf("  ");
            else if (a == 0)
            {
                printf(" %c", letter);
                letter++;
            }
            else if (b == 0)
            {
                printf(" %i", number);
                number--;
            }
            else
            {
                printf(" %c", gameboard[a - 1][b - 1]);
            }
        }
        printf("\n");
    }
}

//Check if the AI or player wins, return 1 if so, passing in game board array and column and row of the player or AI bot.
_Bool checkwin(char gameboard[6][7], int row, int col)
{
    char ele = gameboard[row][col];
    int count = 0;

    //Horizontal Check:
    for (int j = 0; j < 7 - 3; j++)
    {
        for (int i = 0; i < 6; i++)
        {
            if (gameboard[i][j] == ele && gameboard[i][j + 1] == ele && gameboard[i][j + 2] == ele && gameboard[i][j + 3] == ele)
            {
                return 1;
            }
        }
    }
    // Vertical Check:
    for (int i = 0; i < 6 - 3; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (gameboard[i][j] == ele && gameboard[i + 1][j] == ele && gameboard[i + 2][j] == ele && gameboard[i + 3][j] == ele)
            {
                return 1;
            }
        }
    }
    // Ascending Diagonal Check:
    for (int i = 3; i < 6; i++)
    {
        for (int j = 0; j < 7 - 3; j++)
        {
            if (gameboard[i][j] == ele && gameboard[i - 1][j + 1] == ele && gameboard[i - 2][j + 2] == ele && gameboard[i - 3][j + 3] == ele)
                return 1;
        }
    }
    // Descending Diagonal Check:
    for (int i = 3; i < 6; i++)
    {
        for (int j = 3; j < 7; j++)
        {
            if (gameboard[i][j] == ele && gameboard[i - 1][j - 1] == ele && gameboard[i - 2][j - 2] == ele && gameboard[i - 3][j - 3] == ele)
                return 1;
        }
    }
    return 0;
}

// Check if the state is a draw game, return 1 if it is, passing in the gameboard array:
_Bool checkdraw(char gameboard[6][7], char move[], int *len)
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (gameboard[i][j] == '.')
                return 0;
        }
    }
    //if the game is a draw:
    printf("This game is a draw.\n");
    printf("Final State:\n\n");
    board(gameboard);
    printf("\nMoves list:\n");
    for (int i = 0; i < *len; i++)
        printf(" %c", move[i]);
    printf("\n");

    return 1;
}

// Check if the chosen move is valid, passing in the gameboard array:
_Bool checkvalid(char gameboard[6][7], char choose)
{

    if (choose == 'A' && gameboard[0][0] == '.')
        return 1;
    else if (choose == 'B' && gameboard[0][1] == '.')
        return 1;
    else if (choose == 'C' && gameboard[0][2] == '.')
        return 1;
    else if (choose == 'D' && gameboard[0][3] == '.')
        return 1;
    else if (choose == 'E' && gameboard[0][4] == '.')
        return 1;
    else if (choose == 'F' && gameboard[0][5] == '.')
        return 1;
    else if (choose == 'G' && gameboard[0][6] == '.')
        return 1;
    return 0;
}

//Function for AI bot, making moves in defensive mode, if not, attacking, or else making random moves. If AI bot win return 1; if has not, return 0
//passing in gameboard and list of moves, length of the list, and the character of AI bot:
_Bool player1(char gameboard[6][7], char move[], int *len, char ele)
{
    //Letter collumn chosen:
    char choose;
    //Column and row chosen by this AI:
    int col;
    int row;
    //Opponent's character representation:
    char opp;

    if (ele == 'O')
        opp = 'X';
    else if (ele == 'X')
        opp = 'O';

    //Condition to make a move or not
    _Bool stop = 0;
    //Defensing moves:
    //Vertical: check if there are 3 elements of opponents in a row, defend the player from making a four:
    for (int i = 5; i >= 3 && stop == 0; i--)
    {
        for (int j = 0; j < 7 && stop == 0; j++)
        {
            if (gameboard[i][j] == opp && gameboard[i - 1][j] == opp && gameboard[i - 2][j] == opp)
            {
                if (gameboard[i - 3][j] == '.')
                {
                    gameboard[i - 3][j] = ele;
                    row = i - 3;
                    col = j;
                    stop = 1;
                    break;
                }
            }
        }
    }

    //Horizontal: check if there are 3 elements of opponents in a row, defend the player from making a four, by limiting on the left or right:
    if (stop == 0)
    {
        for (int j = 0; j < 7 - 3 && stop == 0; j++)
        {
            for (int i = 0; i < 6 && stop == 0; i++)
            {
                if (gameboard[i][j] == opp && gameboard[i][j + 1] == opp && gameboard[i][j + 2] == opp)
                {
                    if (j - 1 >= 0 && gameboard[i][j - 1] == '.')
                    {
                        col = j - 1;
                        // choose an appropriate row:
                        for (int i = 5; i >= 0; i--)
                        {
                            if (gameboard[i][col] == '.')
                            {
                                gameboard[i][col] = ele;
                                row = i;
                                break;
                            }
                        }
                        stop = 1;
                        break;
                    }

                    else if (j + 3 <= 6 && gameboard[i][j + 3] == '.')
                    {
                        col = j + 3;
                        // choose an appropriate row:
                        for (int i = 5; i >= 0; i--)
                        {
                            if (gameboard[i][col] == '.')
                            {
                                gameboard[i][col] = ele;
                                row = i;
                                stop = 1;
                                break;
                            }
                        }
                        stop = 1;
                        break;
                    }
                }
            }
        }
    }

    //attack: if cannot defend
    if (stop == 0)
    {
        // vertical: try to make a 3, then 4 elements in a row:
        for (int i = 5; i >= 3 && stop == 0; i--)
        {
            for (int j = 0; j < 7 && stop == 0; j++)
            {
                if (gameboard[i][j] == ele && gameboard[i - 1][j] == ele)
                {
                    if (gameboard[i - 2][j] == '.')
                    {
                        gameboard[i - 2][j] = ele;
                        row = i - 2;
                        col = j;
                        stop = 1;
                        break;
                    }
                    else if (gameboard[i - 2][j] == ele && gameboard[i - 3][j] == '.')
                    {
                        gameboard[i - 3][j] = ele;
                        row = i - 3;
                        col = j;
                        stop = 1;
                        break;
                    }
                }
            }
        }
    }

    //horizontal: if cannot make any vertical moves, try to make a 3 or 4 in a row either left or right:
    if (stop == 0)
    {
        for (int j = 0; j < 7 - 2 && stop == 0; j++)
        {
            for (int i = 0; i < 6 && stop == 0; i++)
            {
                if (gameboard[i][j] == ele && gameboard[i][j + 1] == ele)
                {

                    if (j - 1 >= 0 && gameboard[i][j - 1] == '.')
                    {
                        col = j - 1;
                        // choose an appropriate row:
                        for (int i = 5; i >= 0; i--)
                        {
                            if (gameboard[i][col] == '.')
                            {
                                gameboard[i][col] = ele;
                                row = i;
                                stop = 1;
                                break;
                            }
                        }
                        stop = 1;
                        break;
                    }

                    if (j + 2 <= 6 && gameboard[i][j + 2] == '.')
                    {
                        col = j + 2;
                        // choose an appropriate row:
                        for (int i = 5; i >= 0; i--)
                        {
                            if (gameboard[i][col] == '.')
                            {
                                gameboard[i][col] = ele;
                                row = i;
                                stop = 1;
                                break;
                            }
                        }
                        stop = 1;
                        break;
                    }
                }
            }
        }
    }

    // if cannot defend or attack, go random:
    if (stop == 0)
    {
        col = rand() % (6 + 1 - 0) + 0;
        // choose an appropriate row:
        for (int i = 5; i >= 0; i--)
        {
            if (gameboard[i][col] == '.')
            {

                gameboard[i][col] = ele;
                row = i;
                break;
            }
        }
    }

    // Print the move chosen:
    printf("The computer has made its moved:\n");

    // Convert numeric column to letter:
    // A -> 0
    // B -> 1
    // C -> 2
    // D -> 3
    // E -> 4
    // F -> 5
    // G -> 6
    if (col == 0)
        choose = 'A';
    else if (col == 1)
        choose = 'B';
    else if (col == 2)
        choose = 'C';
    else if (col == 3)
        choose = 'D';
    else if (col == 4)
        choose = 'E';
    else if (col == 5)
        choose = 'F';
    else if (col == 6)
        choose = 'G';

    //Store in 1D Array:
    move[*len] = choose;
    (*len)++;

    //Print out the current game state:
    board(gameboard);
    printf("Computer chose: %c\n", choose);
    //Check for winning:
    if (checkwin(gameboard, row, col) == 1)
    {
        printf("Sorry player, try again next time. Congrats, you win, computer!\n");
        printf("Final State:\n\n");
        board(gameboard);
        printf("\nMoves list:\n");
        for (int i = 0; i < *len; i++)
            printf(" %c", move[i]);
        printf("\n");
        return 1;
    }
    return 0;
}

//Human player, scan the input and print out the current state of the game. Return 1 if player wins, else, return 0
//passing in gameboard and list of moves, length of the list, and the character of the player:
_Bool player2(char gameboard[6][7], char move[], int *len, char ele)
{
    //Letter collumn chosen:
    char choose;
    //Column and row chosen by this AI:
    int col;
    int row;
    //Check if need to choose another move:
    _Bool valid = 0;

    while (valid == 0)
    {
        printf("Which column do you choose? (A-G): ");
        scanf(" %c", &choose);
        // if letter is not valid
        if (choose != 'A' && choose != 'B' && choose != 'C' && choose != 'D' &&
            choose != 'E' && choose != 'F' && choose != 'G')
        {
            printf("You have to choose a letter from A to G.\n");
        }

        else if (checkvalid(gameboard, choose) == 1)
        {
            if (choose == 'A')
                col = 0;
            else if (choose == 'B')
                col = 1;
            else if (choose == 'C')
                col = 2;
            else if (choose == 'D')
                col = 3;
            else if (choose == 'E')
                col = 4;
            else if (choose == 'F')
                col = 5;
            else if (choose == 'G')
                col = 6;
            valid = 1;
            break;
        }
        //Check if letter column chosen is full:
        else if (checkvalid(gameboard, choose) == 0)
        {
            printf("You have to choose another letter column from A to G, your current choice is full.\n");
        }
    }

    //Find the appropriate row:
    for (int i = 5; i >= 0; i--)
    {
        if (gameboard[i][col] == '.')
        {
            gameboard[i][col] = ele;
            row = i;
            break;
        }
    }
    //Store in 1D array:
    move[*len] = choose;
    (*len)++;
    //Print the curent game state:
    board(gameboard);
    printf("Player chose: %c\n", choose);
    //Check for winning:
    if (checkwin(gameboard, row, col) == 1)
    {
        printf("Congrats, you win, player!\n");
        printf("Final State:\n\n");
        board(gameboard);
        printf("\nMoves list:\n");
        for (int i = 0; i < *len; i++)
            printf(" %c", move[i]);
        printf("\n");
        return 1;
    }

    return 0;
}

//Thi is the main method, mostly for the intial state. handle the game, and print out the final state:
int main(void)
{
    //Arrays for recording moves:
    char gameboard[6][7];
    char move[6 * 7];
    //Index of the empty element to add for 1D array:
    int len = 0;
    //Condition to stop playing:, if either the player or the bot wins
    _Bool win = 0;
    //Choosing to go first or not:
    char dir;
    //Print out the initial game board:
    initialBoard(gameboard, move);
    printf("Welcome to Connect The Four!\n");
    printf("Reminder: Please input everything in capital letter! Thank you so much!\n");
    printf("Would you like to go first? (Y/N): ");
    scanf(" %c", &dir);
    //If "N", AI bot goes first:
    if (dir == 'N')
    {
        while (win == 0)
        {
            //Check if the game is a draw:
            if (checkdraw(gameboard, move, &len) == 1)
            {
                win = 1;
                break;
            }

            //Check if the AI bot wins:
            if (player1(gameboard, move, &len, 'X') == 1)
            {
                win = 1;
                break;
            }

            //Check if the game is a draw:
            if (checkdraw(gameboard, move, &len) == 1)
            {
                win = 1;
                break;
            }

            //Check if the player wins:
            if (player2(gameboard, move, &len, 'O') == 1)
            {
                win = 1;
                break;
            }

            printf("_________________\n\n");
        }
    }

    //If "Y", player goes first:
    else if (dir == 'Y')
    {
        while (win == 0)
        {
            //Check if the game is a draw:
            if (checkdraw(gameboard, move, &len) == 1)
            {
                win = 1;
                break;
            }

            //Check if the player wins:
            if (player2(gameboard, move, &len, 'X') == 1)
            {
                win = 1;
                break;
            }

            //Check if the game is a draw:
            if (checkdraw(gameboard, move, &len) == 1)
            {
                win = 1;
                break;
            }

            //Check if the AI bot wins:
            if (player1(gameboard, move, &len, 'O') == 1)
            {
                win = 1;
                break;
            }
            printf("_________________\n\n");
        }
    }
}