#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector> 
#include <string>
#include <algorithm>
#include <cstring>

// #include "./Book.cpp"

using namespace std;

class MenuOptions{
    int windowSize = getScreenSize();

    public:
        int getScreenSize(){//to get the screen size
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            int windowSize;

            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            windowSize = csbi.srWindow.Right - csbi.srWindow.Left - 2;
            // windowSize / 2 - to center string

            return windowSize;
        }

        void buffer(int bufferSize, string symbol){//half version of the center function
            for(int j = 0; j<=bufferSize; j++){
                cout << symbol;
            }
        }

        void center(int bufferSize, string symbol, string text){// to have a more appealing interface
            for(int j = 0; j<=bufferSize - text.length() / 2; j++){
                cout << symbol;
            }

            cout << text;

            for(int j = 0; j<=bufferSize - text.length() / 2; j++){
                cout << symbol;
            }
            
            cout << endl;
        }

        inline bool exists(const std::string& name) {//checks if a certain file exists
            if (FILE *file = fopen(name.c_str(), "r")){
                fclose(file);
                return true;
            } else {
                return false;
            }   
        }

        void links(){
            vector<string> options = {
                "1. Add Book",
                "2. Search Book",
                "3. Delete Book Record",
                "4. Borrow Book",
                "5. Return Book",
                "6. View Record",
                "7. Exit"
            };
            cout << endl;
            center(windowSize/2, "-", "LIBRARY INVENTORY SYSTEM");
            cout << endl;
            for(string i : options){
                buffer(windowSize / 2.3, " ");
                cout << i << endl;
            }

        } 

        void backToMenu(){
            string bcktoMenu;
            cout << endl;
            buffer(windowSize / 3, " ");
            cout << "Enter B to transact again, Any key to exit: ";
            cin >> bcktoMenu;
            if(bcktoMenu == "B" || bcktoMenu == "b"){
                menuOptions();
            }else{
                system("exit");
            }
        }   
        
        void menuOptions(){
            system("cls");
            // system("color 70");
            int pickMenu;
            do{
                system("cls");
                links();//displays the menu's

                cout << endl;
                buffer(windowSize / 2.3, " ");
                cout << "Pick a Number: ";
                cin >> pickMenu;

            }while(pickMenu > 7 || pickMenu < 1);

            bool flag = true;
            while(flag){
                if(pickMenu == 1){
                    addBook();
                    flag = false;
                }else if(pickMenu == 2){
                    searchBook();
                    flag = false;
                }else if(pickMenu == 3){
                    deleteBookRecord();
                    flag = false;
                }else if(pickMenu == 4){
                    // borrowBook();
                    flag = false;
                }else if(pickMenu == 5){
                    // returnBook();
                    flag = false;
                }else if(pickMenu == 6){
                    // viewRecord();
                    flag = false;
                }else if(pickMenu == 7){
                    // exitProgram();
                    flag = false;
                }
            }
        }

        void addBook(){
            cin.clear();
            cin.sync();
            string nameBook, authorName, genre, isbn;
            int qty;
            
            system("cls");
            center(windowSize/2, "-", "Add Book");
            cout << endl;

            buffer(windowSize / 3, " ");
            cout << "Enter the ISBN of the Book: ";
            getline(cin, isbn);

            buffer(windowSize / 3, " ");
            cout << "Enter Name of the Book: ";
            getline(cin, nameBook);

            buffer(windowSize / 3, " ");
            cout << "Enter Name of the Author: ";
            getline(cin, authorName);

            buffer(windowSize / 3, " ");
            cout << "Enter the Genre: ";
            getline(cin, genre);

            buffer(windowSize / 3, " ");
            cout << "Enter the Quantity: ";
            cin >> qty;

            // for writing files
            Book newBook(nameBook, authorName, isbn, genre, qty);
            // cout << exists("HumptyD1umpy.dat");
            if(!exists(".\\src\\Database\\" + nameBook + ".dat")){
                fstream file(".\\src\\Database\\" + nameBook + ".dat" , ios::in | ios::out | ios:: trunc);
                
                if(!file.is_open()){
                    cout << endl;
                    center(windowSize/2, " ", "error occured while opening the file, Please try again");
                }else{  
                    // file.write((char *) &newBook, sizeof(Book));
                    file << nameBook << endl;
                    file << authorName << endl;
                    file << isbn << endl;
                    file << genre << endl;
                    file << qty;
                }
            }else{
                cout << endl;
                center(windowSize/2, " ", "Book Already Existed");
            }

            backToMenu();
        }

        void searchBook(){
            system("cls");
            cin.clear();
            cin.sync();

            center(windowSize/2, "-", "Search Book");
            cout << endl;

            string nameSearch;

            buffer(windowSize / 3, " ");
            cout << "Enter the name of the Book: ";
            getline(cin, nameSearch);

            if(!exists(".\\src\\Database\\" + nameSearch + ".dat")){
                cout << endl;
                center(windowSize/2, " ", "No Book Found");
                backToMenu();
            }else{
                cout << endl;
                center(windowSize/2, " ", "Book Found");
                // for reading files
                Book readBook;
                fstream readFile(".\\src\\Database\\" + nameSearch + ".dat", ios::in | ios::out);
                readFile.seekg(0);
                if(!readFile.is_open()){
                    cout << endl;
                    center(windowSize/2, " ", "error occured while opening the file, Please try again");
                }else{  
                    getline(readFile, readBook.bookName);
                    getline(readFile, readBook.authorName);
                    getline(readFile, readBook.isbn);
                    getline(readFile, readBook.genre);
                    readFile >> readBook.quantity;
                }
                int buffAllowance = 50;

                buffer(windowSize / 3.8, " ");
                cout << "BOOK TITLE: ";
                buffer(buffAllowance - readBook.bookName.length() + 3, "-");
                cout <<  " " << readBook.bookName << endl;

                buffer(windowSize / 3.8, " ");
                cout << "AUTHOR: ";
                buffer(buffAllowance - readBook.authorName.length() + 7, "-");
                cout << " " << readBook.authorName << endl;

                buffer(windowSize / 3.8, " ");
                cout << "BOOK ISBN: ";
                buffer(buffAllowance - readBook.isbn.length() + 4, "-");
                cout << " " << readBook.isbn << endl;

                buffer(windowSize / 3.8, " ");
                cout << "BOOK GENRE: ";
                buffer(buffAllowance - readBook.genre.length() + 3, "-");
                cout << " " << readBook.genre << endl;

                buffer(windowSize / 3.8, " ");
                cout << "BOOK QUANTITY: ";
                buffer(buffAllowance - to_string(readBook.quantity).length(), "-");
                cout << " " << readBook.quantity << endl;
                

                backToMenu();
            }
        }
        
        void deleteBookRecord(){
            system("cls");
            cin.clear();
            cin.sync();

            center(windowSize/2, "-", "Delete Book Record");
            cout << endl;

            string deleteSearch;

            buffer(windowSize / 3, " ");
            cout << "Enter the name of the Book: ";
            getline(cin, deleteSearch);

            if(!exists(".\\src\\Database\\" + deleteSearch + ".dat")){
                cout << endl;
                center(windowSize/2, " ", "No Book Found");
                backToMenu();
            }else{
                cout << endl;
                center(windowSize/2, " ", "Book Found");
                // for reading files
                Book readBook;
                fstream readFile(".\\src\\Database\\" + deleteSearch + ".dat", ios::in | ios::out);
                readFile.seekg(0);
                if(!readFile.is_open()){
                    cout << endl;
                    center(windowSize/2, " ", "error occured while opening the file, Please try again");
                }else{  
                    getline(readFile, readBook.bookName);
                    getline(readFile, readBook.authorName);
                    getline(readFile, readBook.isbn);
                    getline(readFile, readBook.genre);
                    readFile >> readBook.quantity;
                }
                int buffAllowance = 50;

                buffer(windowSize / 3.8, " ");
                cout << "BOOK TITLE: ";
                buffer(buffAllowance - readBook.bookName.length() + 3, "-");
                cout << " " << readBook.bookName << endl;

                buffer(windowSize / 3.8, " ");
                cout << "AUTHOR: ";
                buffer(buffAllowance - readBook.authorName.length() + 7, "-");
                cout << " " << readBook.authorName << endl;

                buffer(windowSize / 3.8, " ");
                cout << "BOOK ISBN: ";
                buffer(buffAllowance - readBook.isbn.length() + 4, "-");
                cout << " " << readBook.isbn << endl;

                buffer(windowSize / 3.8, " ");
                cout << "BOOK GENRE: ";
                buffer(buffAllowance - readBook.genre.length() + 3, "-");
                cout << " " << readBook.genre << endl;

                buffer(windowSize / 3.8, " ");
                cout << "BOOK QUANTITY: ";
                buffer(buffAllowance - to_string(readBook.quantity).length(), "-");
                cout << " " << readBook.quantity << endl;

                string deleteAns;

                center(windowSize/2, " ", "Are you sure you want to delete this file?");
                buffer(windowSize / 3, " ");
                cout << "(Enter Y to delete, any key to not delete)";
                cin >> deleteAns;

                if(deleteAns == "Y" || deleteAns == "y"){
                    //delete
                    cout << endl;
                    
                    char path[] = "./Database/";
                    char filename[50];
                    // char command[70] = "del ";
                    strcat(filename, readBook.bookName.c_str());
                    strcat(filename, ".dat");
                    strcat(path, filename);
                    // strcat(command, path);
                    
                    if(remove(path) != 0){
                        cout << "There's an error in deleting the file.";
                    }else{
                        cout << "File Deleted!";
                    }//fix these

                    backToMenu();
                }else{
                    cout << endl;
                    center(windowSize/2, " ", "Have a Nice Day!");
                    backToMenu();
                }

                
            }

        }
        
};
