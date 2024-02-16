#include <stdio.h>
#include <stdlib.h>

struct Note
{
    char last_name[100];
    char first_name[100];
    char phone_number[11];
    int date_of_birth[3];
};

typedef struct Note Note;
void fill_phone_book(Note **book, size_t size);
void print_phone_book(Note **book, size_t size);
void sort_phone_book_by_number(Note **book, size_t size);
Note **get_note_by_last_name(Note **book, size_t size, char *last_name);

int main()
{
    const int SIZE = 3;
    const int LAST_NAME_LENGTH = 100;
 
    Note **phone_book = (Note **)malloc(SIZE * sizeof(Note *));
    for (int i = 0; i < SIZE; i++)
    {
        phone_book[i] = (Note *)calloc(1, sizeof(Note));
    }

    fill_phone_book(phone_book, SIZE);
    sort_phone_book_by_number(phone_book, SIZE);
    print_phone_book(phone_book, SIZE);

    char *query = (char *)calloc(LAST_NAME_LENGTH, sizeof(char));
    Note **response = (Note **)malloc(sizeof(Note));

    printf("\nSearch in phone book by last name:\n");
    scanf("%s", query);

    response = (Note **)get_note_by_last_name(phone_book, SIZE, query);

    if (response == NULL)
    {
        printf("No note about this person. \n");
    }
    else
    {
        // int i = 0;
        // while(response[++i] != NULL)

        for (int i = 0; ; i++)
        {
            if (response[i] == NULL)
                break;

            printf("\nPerson %s \n", query);
            printf("Last name %s \n", response[i]->last_name);
            printf("First name %s \n", response[i]->first_name);
            printf("Phone Number %s \n", response[i]->phone_number);
            printf("Date of birth %d.%d.%d \n", response[i]->date_of_birth[0], response[i]->date_of_birth[1], response[i]->date_of_birth[2]);
        }
    }

    print_phone_book(phone_book, SIZE);
}

void fill_phone_book(Note **book, size_t size)
{
    for (int i = 0; i < size; i++)
    {
        printf("\nBOOK #%d. \nInput last name: \n", i + 1);
        scanf("%s", &book[i]->last_name);
        printf("Input first name: \n");
        scanf("%s", &book[i]->first_name);
        printf("Input phone number: \n");
        scanf("%s", &book[i]->phone_number);
        printf("Input date of birth: \nday: \n");
        scanf("%d", &book[i]->date_of_birth[0]);
        printf("month: \n");
        scanf("%d", &book[i]->date_of_birth[1]);
        printf("year: \n");
        scanf("%d", &book[i]->date_of_birth[2]);
    }
}

void print_phone_book(Note **book, size_t size)
{
    for (int i = 0; i < size; i++)
    {
        printf("\nBOOK #%d \n", i + 1);
        printf("Last name: %s \n", book[i]->last_name);
        printf("First name: %s \n", book[i]->first_name);
        printf("Phone number: %s \n", book[i]->phone_number);
        printf("Date of birth: %d.%d.%d \n", book[i]->date_of_birth[0], book[i]->date_of_birth[1], book[i]->date_of_birth[2]);
    }
}

void sort_phone_book_by_number(Note **book, size_t size)
{
    const int PHONE_NUMBER_LENGTH = 3;

    for (int i = 0; i < size; i++)
    {
        int min_index = i;

        for (int j = i + 1; j < size; j++)
        {
            int compareValue = 0;
            int power = 1;

            for (int k = PHONE_NUMBER_LENGTH - 1; k > 0; k--)
            {
                compareValue += (book[j]->phone_number[k] - '0') * power;
                compareValue -= (book[min_index]->phone_number[k] - '0') * power; 

                power *= 10; 
            }

            if (compareValue < 0)
            {
                min_index = j;
            }
        }

        Note *temp = book[i];
        book[i] = book[min_index];
        book[min_index] = temp;
    }
}

Note **get_note_by_last_name(Note **book, size_t size, char *last_name)
{
    const int MAX_LAST_NAME_LENGTH = 100;
    Note** notes = malloc(sizeof(Note));
    int index = 0;

    for (int i = 0; i < size; i++)
    {
        int is_found = 0;

        for (int j = 0; j < MAX_LAST_NAME_LENGTH; j++)
        {
            
            if (book[i]->last_name[j] != last_name[j])
            {
                is_found = 1;
                break;
            }
        }

        if (is_found == 0)
        {
            notes[index++] = book[i]; 
            notes = (Note**) realloc(notes, index);
        }
    }
    
    if (index == 0) 
        return NULL;
    
    notes = (Note**) realloc(notes, ++index);
    notes[index - 1] = NULL;

    return notes;
}