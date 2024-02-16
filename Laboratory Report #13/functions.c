#include "functions.h"

/* laboratory report 12 */
void write_phone_book_in_file(char path[], Note **phone_book, size_t size)
{
    FILE *file;

    if ((file = fopen(path, "w")) == NULL)
    {
        printf("Error attempting to write to a file: ");
        return;
    }

    for (size_t i = 0; i < size; i++)
    {
        Note *note = phone_book[i];
        fprintf(file, "%s %s %s %d %d %d\n",
                note->last_name,
                note->first_name,
                note->phone_number,
                note->date_of_birth[0],
                note->date_of_birth[1],
                note->date_of_birth[2]);
    }

    fclose(file);
}

void write_phone_book_in_binary_file(char path[], Note **phone_book, size_t size)
{
    FILE *file;
    const char *new_line = "\n";

    if ((file = fopen(path, "wb+")) == NULL)
    {
        printf("Error attempting to write to a binary file: ");
        return;
    }

    fwrite(&size, sizeof(size_t), 1, file);

    for (size_t i = 0; i < size; i++)
    {
        fwrite(&phone_book[i]->last_name, sizeof(char), 100, file);
        fwrite(&phone_book[i]->first_name, sizeof(char), 100, file);
        fwrite(&phone_book[i]->phone_number, sizeof(char), 11, file);
        fwrite(&phone_book[i]->date_of_birth[0], sizeof(int), 1, file);
        fwrite(&phone_book[i]->date_of_birth[1], sizeof(int), 1, file);
        fwrite(&phone_book[i]->date_of_birth[2], sizeof(int), 1, file);
    }

    fclose(file);
}

void print_phone_book_from_any_file(char path[], bool is_binary)
{
    Note **phone_book;
    int index = 0;

    if (is_binary)
    {
        printf("------------BINARY FILE------------\n");
        phone_book = phone_book_from_binary_file(path);
    }
    else
    {
        printf("----------NOT BINARY FILE----------\n");
        phone_book = phone_book_from_file(path);
    }

    if (phone_book != NULL)
    {
        while (phone_book[index] != NULL)
        {
            print_note(phone_book[index]);
            printf("\n");
            index++;
        }
    }
}

void print_notes_from_any_file_by_phone_number(char path[], bool is_binary) 
{
    Note **phone_book;
    int index = 0;
    char *phone_number = (char *)calloc(11, sizeof(char));

    if (is_binary)
    {
        phone_book = phone_book_from_binary_file(path);
        printf("\nSearch in binary file by phone number: ");
    }
    else
    {
        phone_book = phone_book_from_file(path);
        printf("\nSearch in file by phone number: ");
    }

    scanf("%s", phone_number);

    if (phone_book != NULL)
    {
        while (phone_book[index] != NULL)
        {
            if (strcmp(phone_book[index]->phone_number, phone_number) == 0)
            {
                print_note(phone_book[index]);
                printf("\n");
            }
            index++;
        }        
    }
}

void is_note_exist_handler(char path[])
{
    int num = 0;
    printf("Input number of note: ");
    scanf("%d", &num);

    if (is_note_exist(path, num))
    {
        printf("Note exists.\n");
    }
    else
    {
        printf("Not doesn't exist.\n");
    }
}


// low-level of processing
bool is_note_exist(char path[], int num)
{
    int max;
    FILE *file;

    if ((file = fopen(path, "rb+")) == NULL)
    {
        printf("Error attempting to write to a binary file: ");
        return false;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0L, SEEK_SET);

	size -= sizeof(int);
	max = size / (sizeof(char) * 211 + sizeof(int) * 3);

    if (num > 0 && num <= max)
        return true;

    return false;
}

Note **phone_book_from_binary_file(char path[])
{
    Note **phone_book = create_phone_book(1);
    int index = 0;
    FILE *file;
    size_t lines_count;
    char *buffer = malloc(100 * sizeof(char));
    int bufferInt;

    if ((file = fopen(path, "rb")) == NULL)
    {
        printf("%s\n", path);
        perror("Error attempting to get phone book from file: file is empty or not exist");
        return NULL;
    }

    fread(&lines_count, sizeof(size_t), 1, file);

    for (size_t i = 0; i < lines_count; i++)
    {
        Note *new_note = (Note *)malloc(sizeof(Note));

        fread(buffer, sizeof(char), 100, file);
        strcpy(new_note->last_name, buffer);

        fread(buffer, sizeof(char), 100, file);
        strcpy(new_note->first_name, buffer);

        fread(buffer, sizeof(char), 11, file);
        strcpy(new_note->phone_number, buffer);

        fread(&bufferInt, sizeof(int), 1, file);
        new_note->date_of_birth[0] = bufferInt;

        fread(&bufferInt, sizeof(int), 1, file);
        new_note->date_of_birth[1] = bufferInt;

        fread(&bufferInt, sizeof(int), 1, file);
        new_note->date_of_birth[2] = bufferInt;

        phone_book[index] = new_note;
        phone_book = realloc(phone_book, ++index);
    }

    if (index == 0)
        return NULL;

    phone_book[index] = NULL;
    // fclose(file);
    return phone_book;
}

Note **phone_book_from_file(char path[])
{
    Note **phone_book = create_phone_book(1);
    int index = 0;
    FILE *file;

    if ((file = fopen(path, "r")) == NULL)
    {
        printf("%s\n", path);
        perror("Error attempting to get phone book from file: file is empty or not exist");
        return NULL;
    }

    char *content = get_file_content(file);
    // printf("%s\n", content);
    char *end_line;
    char *line = strtok_r(content, "\n", &end_line);

    while (line != NULL)
    {
        char *end_word;
        char *word = strtok_r(line, " ", &end_word);
        Note *new_note = (Note *)malloc(sizeof(Note));
        int count = 0;

        while (word != NULL)
        {
            if (count == 0)
                strcpy(new_note->last_name, word);
            else if (count == 1)
                strcpy(new_note->first_name, word);
            else if (count == 2)
                strcpy(new_note->phone_number, word);
            else if (count == 3)
                new_note->date_of_birth[0] = atoi(word);
            else if (count == 4)
                new_note->date_of_birth[1] = atoi(word);
            else if (count == 5)
                new_note->date_of_birth[2] = atoi(word);

            ++count;
            word = strtok_r(NULL, " ", &end_word);
        }

        phone_book[index] = new_note;
        phone_book = realloc(phone_book, ++index);
        line = strtok_r(NULL, "\n", &end_line);
    }

    if (index == 0)
        return NULL;

    phone_book[index] = NULL;
    
    // fclose(file);
    return phone_book;
}

char *get_file_content(FILE *file)
{
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    char *content = (char *)malloc(size + 1);
    fread(content, sizeof(char), size, file);
    content[size] = '\0';

    // fclose(file);

    return content;
}
/* laboratory report 12 */

/* changed */
Note **create_phone_book(size_t size)
{
    Note **phone_book = (Note **)malloc(size * sizeof(Note *));

    for (size_t i = 0; i < size; i++)
    {
        phone_book[i] = (Note *)calloc(1, sizeof(Note));
    }

    return phone_book;
}

void print_note(Note *note)
{
    printf("Last name: %s \n", note->last_name);
    printf("First name: %s \n", note->first_name);
    printf("Phone Number: %s \n", note->phone_number);
    printf("Date of birth: %d.%d.%d \n", note->date_of_birth[0], note->date_of_birth[1], note->date_of_birth[2]);
}

void search_notes_by_last_name(Note **phone_book, size_t size, size_t last_name_length)
{
    char *query = (char *)calloc(last_name_length, sizeof(char));
    printf("\nSearch in phone book by last name: ");
    scanf("%s", query);

    Note **response = (Note **)get_notes_by_last_name(phone_book, size, query, last_name_length);

    int index = 0;

    if (response == NULL)
    {
        printf("No notes");
    }
    else
    {
        while (response[index] != NULL)
        {
            print_note(response[index]);
            printf("\n");
            index++;
        }
    }
}
/* changed */

void fill_phone_book(Note **book, size_t size)
{
    for (size_t i = 0; i < size; i++)
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
    for (size_t i = 0; i < size; i++)
    {
        printf("\nBOOK #%d \n", i + 1);
        printf("Last name: %s \n", book[i]->last_name);
        printf("First name: %s \n", book[i]->first_name);
        printf("Phone number: %s \n", book[i]->phone_number);
        printf("Date of birth: %d.%d.%d \n", book[i]->date_of_birth[0], book[i]->date_of_birth[1], book[i]->date_of_birth[2]);
    }
}

void sort_phone_book_by_number(Note **book, size_t size, size_t phone_number_length)
{
    for (size_t i = 0; i < size; i++)
    {
        int min_index = i;

        for (size_t j = i + 1; j < size; j++)
        {
            int compareValue = 0;
            int power = 1;

            for (size_t k = phone_number_length - 1; k > 0; k--)
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

Note **get_notes_by_last_name(Note **book, size_t size, char *last_name, size_t max_last_name)
{
    Note **notes = malloc(sizeof(Note));
    int index = 0;

    for (size_t i = 0; i < size; i++)
    {
        int is_found = 0;

        for (size_t j = 0; j < max_last_name; j++)
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
            notes = (Note **)realloc(notes, index);
        }
    }

    if (index == 0)
        return NULL;

    notes = (Note **)realloc(notes, ++index);
    notes[index - 1] = NULL;

    return notes;
}
