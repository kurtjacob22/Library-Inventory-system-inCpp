#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "./src/Book.cpp"

using namespace std;


inline bool exists(const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

// void writeFile(string filename, string bookName, string authorName, string isbn, string genre, int qty){
//     Book newBook(bookName, authorName, isbn, genre, qty);
//     cout << exists(filename);
//     if(!exists(filename)){
//         fstream file(filename, ios::binary | ios::in | ios::out | ios::trunc);
        
//         if(!file.is_open()){
//             cout << "error occured while opening the file";
//         }else{  
//             file.write((char *) &newBook, sizeof(Book));
//         }
//     }

    
// }

// void readFile(string filename){
//     Book readBook;
//     fstream readFile(filename, ios::binary | ios::in | ios::out);
//     readFile.seekg(0);
//     if(!readFile.is_open()){
//         cout << "error occured while opening the file";
//     }else{  
//         readFile.read((char *) &readBook, sizeof(Book));
//     }

//     cout << readBook.bookName << endl;
// }

int main(){

    // writeFile("HumptyDumpy.dat", "Starry Night", "Kurt Jacob", "s321a65", "Comedy", 100);
    // readFile("HumptyDumpy.dat");

    Book newBook("Starry Night", "Kurt Jacob", "s321a65", "Comedy", 100);
    cout << exists("HumptyDumpy.dat");
    if(!exists("HumptyDumpy.dat")){
        fstream file("HumptyDumpy.dat", ios::binary | ios::in | ios::out | ios::trunc);
        
        if(!file.is_open()){
            cout << "error occured while opening the file";
        }else{  
            file.write((char *) &newBook, sizeof(Book));
        }
    }


    Book readBook;
    fstream readFile("HumptyDumpy.dat", ios::binary | ios::in | ios::out);
    readFile.seekg(0);
    if(!readFile.is_open()){
        cout << "error occured while opening the file";
    }else{  
        readFile.read((char *) &readBook, sizeof(Book));
    }

    cout << readBook.bookName << endl;


}