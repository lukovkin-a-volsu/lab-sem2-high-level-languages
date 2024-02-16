#include <stdio.h>
#include <stdlib.h>

int are_brackets_correct(char *brackets);
int is_bracket_open(char bracket);
int is_bracket_close(char bracket);
char get_reverse_bracket(char bracket);

int main()
{
    char *string = (char *)malloc(sizeof(char) * 21);

    printf("Input a string of brackets: ");

    scanf("%s", string);

    int is_correct = are_brackets_correct(string);

    is_correct == 0 ? printf("Correct!") : printf("Incorrect!");

    return 0;
}

int are_brackets_correct(char *brackets)
{
    char *stack = (char *)malloc(sizeof(char) * 21);
    int index = -1;

    for (; *brackets != '\0'; brackets++)
    {
        if (is_bracket_open(*brackets) == 0)
        {
            *(stack + ++index) = get_reverse_bracket(*brackets);
        }
        else if (is_bracket_close(*brackets) == 0)
        {
            char last_bracket;

            if (index == -1)
                last_bracket = '\0';
            else
                last_bracket = *(stack + index--);

            if (last_bracket != *brackets)
                return 1;
        }
        else
        {
            printf("String is incorrect \n");
            return 1;
        }
    }

    return index == -1 ? 0 : 1;
}

int is_bracket_open(char bracket)
{
    char round_bracket = '(';
    char square_bracket = '[';
    char curly_bracket = '{';

    if (bracket == round_bracket || bracket == square_bracket || bracket == curly_bracket)
        return 0;

    return 1;
}

int is_bracket_close(char bracket)
{
    char round_bracket = ')';
    char square_bracket = ']';
    char curly_bracket = '}';

    if (bracket == round_bracket || bracket == square_bracket || bracket == curly_bracket)
        return 0;

    return 1;
}

char get_reverse_bracket(char bracket)
{
    char open_round_bracket = '(';
    char open_square_bracket = '[';
    char open_curly_bracket = '{';
    char closed_round_bracket = ')';
    char closed_square_bracket = ']';
    char closed_curly_bracket = '}';

    if (bracket == open_round_bracket)
        return closed_round_bracket;

    if (bracket == open_square_bracket)
        return closed_square_bracket;

    if (bracket == open_curly_bracket)
        return closed_curly_bracket;

    if (bracket == closed_round_bracket)
        return open_round_bracket;

    if (bracket == closed_square_bracket)
        return open_square_bracket;

    if (bracket == closed_curly_bracket)
        return open_curly_bracket;

    return 1;
}