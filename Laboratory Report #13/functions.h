#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef NOTE_STRUCT
#define NOTE_STRUCT
struct Note
{
    char last_name[100];
    char first_name[100];
    char phone_number[11];
    int date_of_birth[3];
};

typedef struct Note Note;
#endif // !NOTE_STRUCT

#ifndef FUNCTIONS
#define FUNCTIONS
void fill_phone_book(Note **book, size_t size);
void print_phone_book(Note **book, size_t size);
void sort_phone_book_by_number(Note **book, size_t size, size_t phone_number_length);
Note **get_notes_by_last_name(Note **book, size_t size, char *last_name, size_t last_name_length);
Note **create_phone_book(size_t size);
void print_note(Note *note);
void search_notes_by_last_name(Note **phone_book, size_t size, size_t last_name_length);
void write_phone_book_in_file(char path[], Note **phone_book, size_t size);
void write_phone_book_in_binary_file(char path[], Note **phone_book, size_t size);
void print_phone_book_from_any_file(char path[], bool is_binary);
void print_notes_from_any_file_by_phone_number(char path[], bool is_binary);
void is_note_exist_handler(char path[]);
char *get_file_content(FILE *file);
Note **phone_book_from_file(char path[]);
Note **phone_book_from_binary_file(char path[]);
bool is_note_exist(char path[], int num);
#endif // !FUNCTIONS
