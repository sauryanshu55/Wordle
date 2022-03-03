// SAURYANSHU KHANAL, 2nd March 2022.
//WORDLE
// Library declarations
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void get_guess(int turn, char *guess)
{
    printf("Guess %d: ", turn);
    char ch;
    while ((ch = getchar()) != '\n')
    {
        *guess = ch;
        guess++;
    }
    *guess = '\0';
}
// check_char_pos(char ch, const char *target) retruns bool true if the char ch is in *target
//& false if char ch is not in *target
bool check_char_pos(char ch, const char *target)
{
    int i;
    for (i = 0; i <= 4; i++)
    {
        if (ch == target[i])
        {
            return true;
        }
    }
    return false;
}
// check_char_equal(char ch, const char *target, int idx) returns bool true if the char ch is
// equal to the ith index of target. Else, returns false
bool check_char_equal(char ch, const char *target, int idx)
{
    if (ch == target[idx])
    {
        return true;
    }
    return false;
}
// Populates the array results[] with either x, y, or z, based upon the rules of wordle
int check_guess(const char *guess, const char *target, char result[])
{
    int match_count = 0;
    for (int i = 0; i <= 4; i++)
    {
        int idx = i;
        char guess_char = guess[i];
        bool character_pos_check = check_char_pos(guess_char, target);
        bool character_equal_check = check_char_equal(guess_char, target, idx);

        if (character_equal_check == true)
        {
            result[i] = 'g';
            match_count++;
        }
        if ((character_equal_check == false) && (character_pos_check == true))
        {
            result[i] = 'y';
        }
        if ((character_equal_check) == false && (character_pos_check == false))
        {
            match_count = match_count;
            result[i] = 'x';
        }
    }
    return match_count;
}
// print_report(const char *guess, const char *result) Color codes the result array and prints it out
void print_report(const char *guess, const char *result)
{
    for (int i = 0; i <= 5; i++)
    {
        if (result[i] == 'g')
        {
            printf("\033[1;37;42m%c\033[0m ", guess[i]);
        }
        if (result[i] == 'y')
        {
            printf("\033[1;37;43m%c\033[0m ", guess[i]);
        }
        if (result[i] == 'x')
        {
            printf("%c ", guess[i]);
        }
    }
    printf("\n");
}
// check_valid_userinput(char *guess) Checks if the userinput is valid
bool check_valid_userinput(char *guess)
{
    int userinput_len = strlen(guess);
    if (userinput_len == 5)
    {
        return true;
    }
    printf("Invalid input, please input again! \n");
    return false;
}
// play_game(char *guess, const char *target, char result[]) puts it all together
// for a complete wordle game
void play_game(char *guess, const char *target, char result[])
{
    int turn_counter = 1;
    bool win_check = false;

    while ((turn_counter <= 5) && win_check == false)
    {
        bool valid_userinput = false;
        while (valid_userinput == false)
        {
            get_guess(turn_counter, guess);
            valid_userinput = check_valid_userinput(guess);
        }
        int match_output = check_guess(guess, target, result);
        print_report(guess, result);
        turn_counter++;
        if (match_output == 5)
        {
            win_check = true;
            printf("Congratulations! You completed the wordle successfully!! \n");
        }
        else
        {
            win_check = false;
        }
    }

    if (win_check == false)
    {
        printf("The word to be guessed was '%s'. Better luck next time! \n", target);
    }
}
// MAIN FUNCTION
void main(int argc, char *argv[])
{
    //Declaration to seed to use rand()
    srand(time(NULL));

    // VARIABLE DECLARATIONS
    char *dictionary[23] = {"piano", "house", "alone", "above", "media", "radio", "voice", "value", "alive", "ocean", "olive", "quiet", "video", "cause", "sauce", "movie", "juice", "noise", "abuse", "opera", "naive", "email", "azure"};
    char guess[6];
    char *target = dictionary[rand() % 23];
    char result[6];

    // FUNCTION CALLS
    play_game(guess, target, result);
}
