#include <iostream>

using namespace std;

struct Book{
    
    string bookName;
    string authorName;
    string isbn;
    string genre;
    int quantity;

    Book(){
        bookName = "noname";
        authorName = "";
        isbn = "";
        genre = "";
        quantity = 0;
    }

    Book(string nameBook, string nameAuthor, string refId, string genre, int qty){
        bookName = nameBook;
        authorName = nameAuthor;
        isbn = refId;
        this->genre = genre;
        quantity = qty;
    }
};