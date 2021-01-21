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
        
        string convertToUnderScore(string text){
            int length = text.size();
            int x = 0;
            string fixed;

            while(x != length) {
                string letter = text.substr(x, 1);
                if (letter == " ") {
                    letter = "_";}
                    fixed = fixed + letter;
                    x = x + 1;
            }

            return fixed;
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
                    borrowBook();
                    flag = false;
                }else if(pickMenu == 5){
                    returnBook();
                    flag = false;
                }else if(pickMenu == 6){
                    editRecord();
                    flag = false;
                }else if(pickMenu == 7){
                    exitProgram();
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
            while(qty > 100){
                buffer(windowSize / 3, " ");
                cout << "Enter the Quantity, The limit is 100 copies only: ";
                cin >> qty;
            }

            // for writing files
            Book newBook(nameBook, authorName, isbn, genre, qty);
            transform(nameBook.begin(), nameBook.end(), nameBook.begin(), ::tolower);
            // cout << exists("HumptyD1umpy.dat");
            if(!exists(".\\src\\Database\\" + convertToUnderScore(nameBook) + ".dat")){
                fstream file(".\\src\\Database\\" + convertToUnderScore(nameBook) + ".dat" , ios::in | ios::out | ios:: trunc);
                
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
                    file.close();
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

            if(!exists(".\\src\\Database\\" + convertToUnderScore(nameSearch) + ".dat")){
                cout << endl;
                center(windowSize/2, " ", "No Book Found");
                backToMenu();
            }else{
                cout << endl;
                center(windowSize/2, " ", "Book Found");
                // for reading files
                Book readBook;
                fstream readFile(".\\src\\Database\\" + convertToUnderScore(nameSearch) + ".dat", ios::in | ios::out);
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

            if(!exists(".\\src\\Database\\" + convertToUnderScore(deleteSearch) + ".dat")){
                cout << endl;
                center(windowSize/2, " ", "No Book Found");
                backToMenu();
            }else{
                cout << endl;
                center(windowSize/2, " ", "Book Found");
                // for reading files
                Book readBook;
                fstream readFile(".\\src\\Database\\" + convertToUnderScore(deleteSearch) + ".dat", ios::in | ios::out);
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
                readFile.close();
                string deleteAns;

                center(windowSize/2, " ", "Are you sure you want to delete this file?");
                buffer(windowSize / 3, " ");
                cout << "(Enter Y to delete, any key to not delete)";
                cin >> deleteAns;

                if(deleteAns == "Y" || deleteAns == "y"){
                    //delete book
                    cout << endl;
                    
                    string path = "./src/Database/" + convertToUnderScore(deleteSearch) + ".dat";
                    // cout << path << endl;//to print the pathname
                    if(remove(path.c_str()) != 0){
                        buffer(windowSize / 3, " ");
                        perror("There's an error in deleting the file.");
                        // cout << "There's an error in deleting the file.";
                    }else{
                        center(windowSize/2, " ", "File Deleted!");
                    }

                    backToMenu();
                }else{
                    cout << endl;
                    center(windowSize/2, " ", "Have a Nice Day!");
                    backToMenu();
                }
                
            }

        }

        void borrowBook(){
            system("cls");
            cin.clear();
            cin.sync();

            center(windowSize/2, "-", "Borrow Book");
            cout << endl;

            string borrowBook;

            buffer(windowSize / 3, " ");
            cout << "Enter the name of the Book: ";
            getline(cin, borrowBook);

            if(!exists(".\\src\\Database\\" + convertToUnderScore(borrowBook) + ".dat")){
                cout << endl;
                center(windowSize/2, " ", "No Book Found");
                backToMenu();
            }else{
                cout << endl;
                center(windowSize/2, " ", "Book Found");
                // for reading files
                Book readBook;
                fstream readFile(".\\src\\Database\\" + convertToUnderScore(borrowBook) + ".dat", ios::in | ios::out);
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

                readFile.close();

                int booksToBorrowCount;
                center(windowSize/2, " ", "You are borrowing " + borrowBook);
                buffer(windowSize / 3, " ");
                cout << "How many books do you want to borrow? ";
                cin >> booksToBorrowCount;

                if(booksToBorrowCount > 0){
                    if(booksToBorrowCount <= readBook.quantity){
                        cout << endl;
                        center(windowSize/2, " ", "You've Borrowed " + to_string(booksToBorrowCount) + " pc/pcs of " + readBook.bookName);

                        readBook.quantity -= booksToBorrowCount;
                        // cout << readBook.quantity;
                        string path = "./src/Database/" + convertToUnderScore(borrowBook) + ".dat";

                        // use for edit files
                        if(remove(path.c_str()) != 0){
                            buffer(windowSize / 3, " ");
                            perror("There's an error in deleting the file.");
                            // cout << "There's an error in deleting the file.";
                        }else{
                            Book newBook(readBook.bookName, readBook.authorName, readBook.isbn, readBook.genre, readBook.quantity);
                            transform(readBook.bookName.begin(), readBook.bookName.end(), readBook.bookName.begin(), ::tolower);
                            // cout << exists("HumptyD1umpy.dat");
                            if(!exists(".\\src\\Database\\" + convertToUnderScore(readBook.bookName) + ".dat")){
                                fstream file(".\\src\\Database\\" + convertToUnderScore(readBook.bookName) + ".dat" , ios::in | ios::out | ios:: trunc);
                                
                                if(!file.is_open()){
                                    cout << endl;
                                    center(windowSize/2, " ", "error occured while opening the file, Please try again");
                                }else{  
                                    // file.write((char *) &newBook, sizeof(Book));
                                    file << readBook.bookName << endl;
                                    file << readBook.authorName << endl;
                                    file << readBook.isbn << endl;
                                    file << readBook.genre << endl;
                                    file << readBook.quantity;
                                }
                                file.close();
                            }
                        }
                        // for writing files
                        

                        backToMenu();
                    }else{
                        cout << endl;
                        center(windowSize/2, " ", "Book Count Exceeded!");
                        backToMenu();
                    }
                }else{
                    cout << endl;
                    center(windowSize/2, " ", "Have a Nice Day!");
                    backToMenu();
                }
                
            }

        }

        void returnBook(){
            system("cls");
            cin.clear();
            cin.sync();

            center(windowSize/2, "-", "Return Book");
            cout << endl;

            string returnBook;

            buffer(windowSize / 3, " ");
            cout << "Enter the name of the Book: ";
            getline(cin, returnBook);

            if(!exists(".\\src\\Database\\" + convertToUnderScore(returnBook) + ".dat")){
                cout << endl;
                center(windowSize/2, " ", "No Book Found");
                backToMenu();
            }else{
                cout << endl;
                center(windowSize/2, " ", "Book Found");
                // for reading files
                Book readBook;
                fstream readFile(".\\src\\Database\\" + convertToUnderScore(returnBook) + ".dat", ios::in | ios::out);
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

                readFile.close();

                int booksToReturnCount;
                center(windowSize/2, " ", "You are returning " + returnBook);
                buffer(windowSize / 3, " ");
                cout << "How many books do you want to return? ";
                cin >> booksToReturnCount;

                if(booksToReturnCount > 0){
                    if(booksToReturnCount + readBook.quantity <= 100){
                        cout << endl;
                        center(windowSize/2, " ", "You've Returned " + to_string(booksToReturnCount) + " pc/pcs of " + readBook.bookName);

                        readBook.quantity += booksToReturnCount;
                        // cout << readBook.quantity;
                        string path = "./src/Database/" + convertToUnderScore(returnBook) + ".dat";

                        // use for edit files
                        if(remove(path.c_str()) != 0){
                            buffer(windowSize / 3, " ");
                            perror("There's an error in deleting the file.");
                            // cout << "There's an error in deleting the file.";
                        }else{
                            Book newBook(readBook.bookName, readBook.authorName, readBook.isbn, readBook.genre, readBook.quantity);
                            transform(readBook.bookName.begin(), readBook.bookName.end(), readBook.bookName.begin(), ::tolower);
                            // cout << exists("HumptyD1umpy.dat");
                            if(!exists(".\\src\\Database\\" + convertToUnderScore(readBook.bookName) + ".dat")){
                                fstream file(".\\src\\Database\\" + convertToUnderScore(readBook.bookName) + ".dat" , ios::in | ios::out | ios:: trunc);
                                
                                if(!file.is_open()){
                                    cout << endl;
                                    center(windowSize/2, " ", "error occured while opening the file, Please try again");
                                }else{  
                                    // file.write((char *) &newBook, sizeof(Book));
                                    file << readBook.bookName << endl;
                                    file << readBook.authorName << endl;
                                    file << readBook.isbn << endl;
                                    file << readBook.genre << endl;
                                    file << readBook.quantity;
                                }
                                file.close();
                            }
                        }
                        // for writing files
                        

                        backToMenu();
                    }else{
                        cout << endl;
                        center(windowSize/2, " ", "Book Count Exceeded!");
                        backToMenu();
                    }
                }else{
                    cout << endl;
                    center(windowSize/2, " ", "Have a Nice Day!");
                    backToMenu();
                }
                
            }

        }

        void editRecord(){
            //edit
        }

        void exitProgram(){
            system("cls");
            exit(0);
        }

};
