#include "functions.h"

int main()
{
    const int SIZE = 3;
    const int LAST_NAME_LENGTH = 100;
    const int PHONE_NUMBER_LENGTH = 3;
    const char PATH[] = "phone_book.txt";
    const char PATH_BINARY[] = "phone_book_binary.txt";

    Note **phone_book = create_phone_book(SIZE);

    fill_phone_book(phone_book, SIZE);
    sort_phone_book_by_number(phone_book, SIZE, PHONE_NUMBER_LENGTH);
    /* laboratory report 12*/
    write_phone_book_in_file(PATH, phone_book, SIZE);
    print_phone_book_from_any_file(PATH, false);
    write_phone_book_in_binary_file(PATH_BINARY, phone_book, SIZE);
    print_phone_book_from_any_file(PATH_BINARY, true);
    print_notes_from_any_file_by_phone_number(PATH, false);
    print_notes_from_any_file_by_phone_number(PATH_BINARY, true);
    is_note_exist_handler(PATH_BINARY);
    /* laboratory report 12*/
    // print_phone_book(phone_book, SIZE);
    // search_notes_by_last_name(phone_book, SIZE, LAST_NAME_LENGTH);
}
