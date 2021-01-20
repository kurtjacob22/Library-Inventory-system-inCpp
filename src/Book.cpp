#include <iostream>

using namespace std;

struct Book{
    
    string bookName;
    string authorName;
    string isbn;
    string genre;
    int quantity;

    public:
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

        // //!getters
        // string getBookName(){
        //     return bookName;
        // }

        // string getAuthorName(){
        //     return authorName;
        // }

        // string getISBN(){
        //     return isbn;
        // }

        // string getGenre(){
        //     return genre;
        // }

        // int getQuantity(){
        //     return quantity;
        // }

        // //!setters

        // void setBookName(string newName){
        //     bookName = newName;
        // }

        // void setAuthorName(string newAuthor){
        //     authorName = newAuthor;
        // }

        // void setISBN(string newISBN){
        //     isbn = newISBN;
        // }

        // void setGenre(string newGenre){
        //     genre = newGenre;
        // }

        // void setQuantity(int newQuantity){
        //     quantity = newQuantity;
        // }
};