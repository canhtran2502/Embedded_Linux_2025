#include "stdio.h"
#include "book.h"

int main()
{
    english_book();
    math_book();
    return 0;
}

void info_book(char* book)
{
    printf("The book name is: %s \n",book);
}