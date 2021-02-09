#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector> 
#include <string>
#include <algorithm>

using namespace std;
class MenuOptions{
    int windowSize = getScreenSize();//* initialize a global variable for the windowSize
    int buffAllowance = 50;

    public:
        int getScreenSize(){ //? to get the screen size
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            int windowSize;

            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            windowSize = csbi.srWindow.Right - csbi.srWindow.Left - 2;
            // windowSize / 2 - to center string

            return windowSize;
        }

        void buffer(int bufferSize, string symbol){ //? half version of the center function
            for(int j = 0; j<=bufferSize; j++){
                cout << symbol;
            }
        }

        void center(int bufferSize, string symbol, string text){ //? to have a more appealing interface
            for(int j = 0; j<=bufferSize - text.length() / 2; j++){
                cout << symbol;
            }

            cout << text;

            for(int j = 0; j<=bufferSize - text.length() / 2; j++){
                cout << symbol;
            }
            
            cout << endl;
        }

        inline bool exists(const string& name) { //? checks if a certain file exists
            if (FILE *file = fopen(name.c_str(), "r")){
                fclose(file);
                return true;
            } else {
                return false;
            }   
        }
        
        string convertToUnderScore(string text){ //? convert spaces to underscores 
            int x = 0;
            string fixed;

            while(x != text.size()) {
                string letter = text.substr(x, 1);
                if (letter == " ") {
                    letter = "_";}
                    fixed = fixed + letter;
                    x = x + 1;
            }

            return fixed;
        }

        void headerTitle(){ //? HEADER File for the links
            system("Color 70");
            center(windowSize/2, "-", "-");
            center(windowSize/2, "+", "PLM LIBRARY SYSTEM");
            center(windowSize/2, "-", "-");
        }

        void links(){ //? list of links using vector array
            vector<string> options = {
                "1. Add Book",
                "2. Search Book",
                "3. Delete Book Record",
                "4. Borrow Book",
                "5. Return Book",
                "6. Edit Record",
                "7. View All Books",
                "8. View Books by Genre",
                "9. Exit"
            };
            center(windowSize/2, "-", "SERVICES:");
            center(windowSize/2, "-", "-");
            cout << endl;
            for(string i : options){
                buffer(windowSize / 2.3, " ");
                cout << i << endl;
            }

        } 

        bool isInArray(string &value, vector<string> &array){ //? checks if the string is inside an array
            return find(array.begin(), array.end(), value) != array.end();
        }

        void backToMenu(){ //* redirects user to menu
            string bcktoMenu;
            cout << endl;
            buffer(windowSize / 3, " ");
            cout << "Enter B to transact again, Any key to exit: ";
            cin >> bcktoMenu;
            if(bcktoMenu == "B" || bcktoMenu == "b"){
                menuOptions();
            }else{
                exit(0);
            }
        }   

        void menuOptions(){ //* links for menu
            system("cls");
            vector<string> choices = {"1","2","3","4","5","6","7","8","9"};// limit of the menu
            string pickMenu;
            do{
                system("cls");// clear screen
                headerTitle(); //header title
                links();//displays the menu's
                
                cout << endl;
                buffer(windowSize / 2.3, " ");
                cout << "Pick a Number: ";
                getline(cin, pickMenu);
                

            }while(pickMenu == "" || !isInArray(pickMenu, choices));

            while(true){
                if(pickMenu == "1"){
                    addBook();
                }else if(pickMenu == "2"){
                    searchBook();
                }else if(pickMenu == "3"){
                    deleteBookRecord();
                }else if(pickMenu == "4"){
                    borrowBook();
                }else if(pickMenu == "5"){
                    returnBook();
                }else if(pickMenu == "6"){
                    editRecord();
                }else if(pickMenu == "7"){
                    displayAllBooks();
                }else if(pickMenu == "8"){
                    viewBooksByGenre();
                }else if(pickMenu == "9"){
                    exitProgram();
                }
            }
        }

        void addBook(){ //* links for add book
            cin.clear();
            cin.sync();
            headerTitle();
            string nameBook, authorName, genre, isbn;
            int qty;
            
            //header Part
            system("cls");
            headerTitle();
            center(windowSize/2, "-", "Add Book");
            center(windowSize/2, "-", "-");
            cout << endl;

            // get book details
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
            string origNameBook = nameBook;
            transform(nameBook.begin(), nameBook.end(), nameBook.begin(), ::tolower);
            // cout << exists("HumptyD1umpy.dat");
            if(!exists(".\\src\\Database\\" + convertToUnderScore(nameBook) + ".dat")){
                fstream file(".\\src\\Database\\" + convertToUnderScore(nameBook) + ".dat" , ios::in | ios::out | ios:: trunc);
                
                if(!file.is_open()){
                    cout << endl;
                    center(windowSize/2, " ", "error occured while opening the file, Please try again");
                }else{  
                    file << origNameBook << endl;
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
            writeFilesAsListOfBooks(nameBook);

            backToMenu();
        }

        void searchBook(){ //* links for searching a book
            system("cls");
            cin.clear();
            cin.sync();
            headerTitle();
            center(windowSize/2, "-", "Search Book");
            center(windowSize/2, "-", "-");
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

                readFile.close();
            
                backToMenu();
            }
        }
        
        void deleteBookRecord(){ //* links for deleting a book record
            system("cls");
            cin.clear();
            cin.sync();
            headerTitle();
            center(windowSize/2, "-", "Delete Book Record");
            center(windowSize/2, "-", "-");
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

        void borrowBook(){ //* links for borrowing a book
            system("cls");
            cin.clear();
            cin.sync();
            headerTitle();
            center(windowSize/2, "-", "Borrow Book");
            center(windowSize/2, "-", "-");
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
                                    
                                    addToBorrowersList(readBook.bookName, booksToBorrowCount);

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

        void addToBorrowersList(string filename, int Bookcount){
            cin.clear();
            cin.sync();
            string borrower;
            cout << endl;
            buffer(windowSize/3, " ");
            cout << "Enter your Name: ";
            getline(cin, borrower);
            transform(borrower.begin(), borrower.end(), borrower.begin(), ::tolower);

            fstream file(".\\src\\Database\\BorrowerData\\" + convertToUnderScore(filename) + ".dat", ios::in | ios::out | ios::app);
            file << convertToUnderScore(borrower) << endl;
            file.close();

        }

        void editBorrowerList(string filename, int Bookcount, string name){
            string path = "./src/Database/BorrowerData/" + convertToUnderScore(filename) + ".dat";
            fstream readFile(".\\src\\Database\\BorrowerData\\" + convertToUnderScore(filename) + ".dat" , ios::in | ios::out);
            vector<string> borrowers;
            string input;
            while(getline(readFile, input)){//check every lines
                transform(input.begin(), input.end(), input.begin(), ::tolower);
                borrowers.push_back(input);
            }
            if (find(borrowers.begin(), borrowers.end(), name) != borrowers.end()){
                readFile.close();
            }else{
                readFile.close();
                center(windowSize/2, " ", "Invalid Name!");
                backToMenu();
            }
            // use for edit files
            if(remove(path.c_str()) != 0){
                buffer(windowSize / 3, " ");
                perror("There's an error in deleting the file.");
                // cout << "There's an error in deleting the file.";
            }else{
                fstream file(".\\src\\Database\\BorrowerData\\" + convertToUnderScore(filename) + ".dat" , ios::in | ios::out | ios::trunc);
                
                if(!file.is_open()){
                    cout << endl;
                    center(windowSize/2, " ", "error occured while opening the file, Please try again");
                }else{


                
                    for(int i = 0; i < borrowers.size(); i++){
                        if(borrowers.at(i) != convertToUnderScore(name)){
                            file << borrowers.at(i) << endl;
                        }
                    }
                }
                file.close();
            }
        }

        void returnBook(){ //* links for returning a book
            system("cls");
            cin.clear();
            cin.sync();
            headerTitle();
            center(windowSize/2, "-", "Return Book");
            center(windowSize/2, "-", "-");
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
                string borrowersName;
                int booksToReturnCount;
                center(windowSize/2, " ", "You are returning " + returnBook);

                buffer(windowSize / 3, " ");
                cout << "Please Enter your name: ";
                getline(cin, borrowersName);
                transform(borrowersName.begin(), borrowersName.end(), borrowersName.begin(), ::tolower);
                
                

                buffer(windowSize / 3, " ");
                cout << "How many books do you want to return? ";
                cin >> booksToReturnCount;

                if(booksToReturnCount > 0){
                    if(booksToReturnCount + readBook.quantity <= 100){

                        editBorrowerList(readBook.bookName, booksToReturnCount, borrowersName);

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

        void editRecord(){ //* links for editing a record
            //edit record
            system("cls");
            cin.clear();
            cin.sync();
            headerTitle();
            center(windowSize/2, "-", "Edit Record");
            center(windowSize/2, "-", "-");
            cout << endl;

            string editBook;

            buffer(windowSize / 3, " ");
            cout << "Enter the name of the Book: ";
            getline(cin, editBook);

            if(!exists(".\\src\\Database\\" + convertToUnderScore(editBook) + ".dat")){
                cout << endl;
                center(windowSize/2, " ", "No Book Found");
                backToMenu();
            }else{
                cout << endl;
                center(windowSize/2, " ", "Book Found");
                // for reading files
                Book readBook;
                fstream readFile(".\\src\\Database\\" + convertToUnderScore(editBook) + ".dat", ios::in | ios::out);
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
                
                int pickEdit;
                cout << endl;
                buffer(windowSize / 3, " ");
                cout << "1. TITLE" << endl;
                buffer(windowSize / 3, " ");
                cout << "2. AUTHOR" << endl;
                buffer(windowSize / 3, " ");
                cout << "3. ISBN" << endl;
                buffer(windowSize / 3, " ");
                cout << "4. GENRE" << endl;
                buffer(windowSize / 3, " ");
                cout << "5. QUANTITY" << endl;
                buffer(windowSize / 3, " ");
                cout << "6. CHANGE ALL" << endl;
                buffer(windowSize / 3, " ");
                cout << "What do you want to edit? pick a number: ";
                cin >> pickEdit;

                while(pickEdit > 6 || pickEdit < 0){
                    buffer(windowSize / 3, " ");
                    cout << "Please pick a number between 1-5: ";
                    cin >> pickEdit;
                }

                string bookName = readBook.bookName;
                transform(bookName.begin(), bookName.end(), bookName.begin(), ::toupper);
                
                if(pickEdit == 1){
                    string editElement;
                    cin.clear();
                    cin.sync();
                    cout << endl;
                    buffer(windowSize / 3, " ");
                    cout << "TITLE~" << endl;
                    buffer(windowSize / 3, " ");
                    
                    cout << "Change " << readBook.bookName << " to: ";
                    getline(cin, editElement);
                    readBook.bookName = editElement;
                }else if(pickEdit == 2){
                    string editElement;
                    cin.clear();
                    cin.sync();
                    cout << endl;
                    buffer(windowSize / 3, " ");
                    cout << "AUTHOR~" << endl;
                    buffer(windowSize / 3, " ");
                    
                    cout << "Change " << readBook.authorName << " to: ";
                    getline(cin, editElement);
                    readBook.authorName = editElement;
                }else if(pickEdit == 3){
                    string editElement;
                    cin.clear();
                    cin.sync();
                    cout << endl;
                    buffer(windowSize / 3, " ");
                    cout << "ISBN~" << endl;
                    buffer(windowSize / 3, " ");

                    cout << "Change " << readBook.isbn << " to: ";
                    getline(cin, editElement);
                    readBook.isbn = editElement;
                }else if(pickEdit == 4){
                    string editElement;
                    cin.clear();
                    cin.sync();
                    cout << endl;
                    buffer(windowSize / 3, " ");
                    cout << "GENRE~" << endl;
                    buffer(windowSize / 3, " ");

                    cout << "Change " << readBook.genre << " to: ";
                    getline(cin, editElement);
                    readBook.isbn = editElement;
                }else if(pickEdit == 5){
                    int editElement;
                    cin.clear();
                    cin.sync();
                    cout << endl;
                    buffer(windowSize / 3, " ");
                    cout << "QUANTITY~" << endl;
                    buffer(windowSize / 3, " ");

                    cout << "Change " << readBook.quantity << " pc/pcs to: ";
                    cin >> editElement;
                    while(editElement > 100 || editElement < 0){
                        cout << endl;
                        buffer(windowSize / 3, " ");
                        cout << "Change " << readBook.quantity << " pc/pcs to: ";
                        cin >> editElement;
                        readBook.quantity = editElement;
                    }

                    readBook.quantity = editElement;
                    
                }else if(pickEdit == 6){
                    string newBookName, newAuthorName, newISBN, newGenre;
                    int newQuantity;
                    cin.clear();
                    cin.sync();

                    //BOOK TITLE
                    cout << endl;
                    buffer(windowSize / 3, " ");
                    cout << "TITLE~" << endl;
                    buffer(windowSize / 3, " ");
                    
                    cout << "Change " << readBook.bookName << " to: ";
                    getline(cin, newBookName);

                    //AUTHOR
                    cout << endl;
                    buffer(windowSize / 3, " ");
                    cout << "AUTHOR~" << endl;
                    buffer(windowSize / 3, " ");
                    
                    cout << "Change " << readBook.authorName << " to: ";
                    getline(cin, newAuthorName);

                    //BOOK ISBN
                    cout << endl;
                    buffer(windowSize / 3, " ");
                    cout << "ISBN~" << endl;
                    buffer(windowSize / 3, " ");

                    cout << "Change " << readBook.isbn << " to: ";
                    getline(cin, newISBN);

                    //GENRE
                    cout << endl;
                    buffer(windowSize / 3, " ");
                    cout << "GENRE~" << endl;
                    buffer(windowSize / 3, " ");

                    cout << "Change " << readBook.genre << " to: ";
                    getline(cin, newGenre);

                    //QUANTITY
                    cout << endl;
                    buffer(windowSize / 3, " ");
                    cout << "QUANTITY~" << endl;
                    buffer(windowSize / 3, " ");

                    cout << "Change " << readBook.quantity << " pc/pcs to: ";
                    cin >> newQuantity;
                    while(newQuantity > 100 || newQuantity < 0){
                        cout << endl;
                        buffer(windowSize / 3, " ");
                        cout << "Change " << readBook.quantity << " pc/pcs to: ";
                        cin >> newQuantity;
                    }

                    readBook.bookName = newBookName;
                    readBook.authorName = newAuthorName;
                    readBook.isbn = newISBN;
                    readBook.genre = newGenre;
                    readBook.quantity = newQuantity;

                }
                vector<string> handler;
                string convertToLower = readBook.bookName;
                transform(convertToLower.begin(), convertToLower.end(), convertToLower.begin(), ::tolower);
                string input;
                fstream checkIfContains(".\\src\\Database\\ListOfBooks_Cache.dat", ios::in | ios::out | ios::app);
                while(checkIfContains >> input){//check every lines
                    handler.push_back(input);
                }

                string path = "./src/Database/" + convertToUnderScore(editBook) + ".dat";
                string newFilename = readBook.bookName;

                // use for edit files
                if(remove(path.c_str()) != 0){
                    buffer(windowSize / 3, " ");
                    perror("There's an error in deleting the file.");
                    // cout << "There's an error in deleting the file.";
                }else{
                    Book newBook(readBook.bookName, readBook.authorName, readBook.isbn, readBook.genre, readBook.quantity);
                    transform(newFilename.begin(), newFilename.end(), newFilename.begin(), ::tolower);
                    // cout << exists("HumptyD1umpy.dat");
                    if(!exists(".\\src\\Database\\" + convertToUnderScore(newFilename) + ".dat")){
                        fstream file(".\\src\\Database\\" + convertToUnderScore(newFilename) + ".dat" , ios::in | ios::out | ios:: trunc);
                        
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
                for(string i : handler){
                    if(i == convertToUnderScore(convertToLower)){
                        backToMenu();
                        break;
                    }
                }
                writeFilesAsListOfBooks(convertToLower);
                backToMenu();
            }
        }

        void exitProgram(){ //* links for exiting the program
            system("cls");
            exit(0);
        }

        void displayAllBooks(){ //* links for displaying all books
            //Diplays all the books
            system("cls");
            cin.clear();
            cin.sync();
            headerTitle();
            center(windowSize/2, "-", "List of Books");
            center(windowSize/2, "-", "-");
            cout << endl;

            vector<string> bookTitles;
            fstream readFile(".\\src\\Database\\ListOfBooks_Cache.dat", ios::in | ios::out | ios::app);
            if(!readFile.is_open()){
                cout << endl;
                center(windowSize/2, " ", "error occured while opening the file, Please try again");
            }else{
                cout << endl;
                center(windowSize/2, " ", "Here are the list of our books");
                string input;
                while(readFile >> input){//check every lines
                    bookTitles.push_back(input);
                }

                for(string i : bookTitles){
                    // cout << i << endl;
                    if(exists(".\\src\\Database\\" + i + ".dat")){
                        Book readBook;
                        fstream readBookFile(".\\src\\Database\\" + i + ".dat", ios::in | ios::out);
                        getline(readBookFile, readBook.bookName);
                        getline(readBookFile, readBook.authorName);
                        getline(readBookFile, readBook.isbn);
                        getline(readBookFile, readBook.genre);
                        readBookFile >> readBook.quantity;

                        int buffAllowance = 80;

                        // cout << readBook.bookName << readBook.quantity << endl;
                        buffer(windowSize / 7, " ");
                        cout << readBook.isbn;
                        buffer(20 - readBook.isbn.length(), " ");
                        cout << readBook.bookName;
                        buffer(buffAllowance - readBook.bookName.length(), "-");
                        if(readBook.quantity == 0){
                            cout << "BOOK NOT AVAILABLE" << endl;
                        }else{
                            if(readBook.quantity == 1){
                                cout << readBook.quantity << "pc" << endl;
                            }else{
                                cout << readBook.quantity << "pcs" << endl;
                            }
                        }
                    }
                }
                backToMenu();
            }
        }

        void viewBooksByGenre(){ //* links for displaying books by user's input genre
            //Diplays all the books
            system("cls");
            cin.clear();
            cin.sync();
            headerTitle();
            center(windowSize/2, "-", "List of Books");
            center(windowSize/2, "-", "-");
            cout << endl;

            buffer(windowSize / 3, " ");
            string genreInput;
            cout << "Enter Genre: ";
            cin >> genreInput;

            vector<string> bookTitles;
            fstream readFile(".\\src\\Database\\ListOfBooks_Cache.dat", ios::in | ios::out | ios::app);
            if(!readFile.is_open()){
                cout << endl;
                center(windowSize/2, " ", "error occured while opening the file, Please try again");
            }else{
                cout << endl;
                center(windowSize/2, " ", "Here are the list of our books with the genre of " + genreInput);
                string input;
                while(readFile >> input){//check every lines
                    bookTitles.push_back(input);
                }

                for(string i : bookTitles){
                    // cout << i << endl;
                    if(exists(".\\src\\Database\\" + i + ".dat")){
                        Book readBook;
                        fstream readBookFile(".\\src\\Database\\" + i + ".dat", ios::in | ios::out);
                        getline(readBookFile, readBook.bookName);
                        getline(readBookFile, readBook.authorName);
                        getline(readBookFile, readBook.isbn);
                        getline(readBookFile, readBook.genre);
                        readBookFile >> readBook.quantity;
                        transform(genreInput.begin(), genreInput.end(), genreInput.begin(), ::tolower);
                        transform(readBook.genre.begin(), readBook.genre.end(), readBook.genre.begin(), ::tolower);
                        if(genreInput == readBook.genre){
                            int buffAllowance = 80;

                            // cout << readBook.bookName << readBook.quantity << endl;
                            buffer(windowSize / 7, " ");
                            cout << readBook.isbn;
                            buffer(20 - readBook.isbn.length(), " ");
                            cout << readBook.bookName;
                            buffer(buffAllowance - readBook.bookName.length(), "-");
                            if(readBook.quantity == 0){
                                cout << "BOOK NOT AVAILABLE" << endl;
                            }else{
                                if(readBook.quantity == 1){
                                    cout << readBook.quantity << "pc" << endl;
                                }else{
                                    cout << readBook.quantity << "pcs" << endl;
                                }
                            }
                        }  
                    }
                }
                backToMenu();
            }
        }

        void writeFilesAsListOfBooks(string bookName){ //* to append title into ListOfBooks_Cache.dat
            fstream file(".\\src\\Database\\ListOfBooks_Cache.dat", ios::in | ios::out | ios::app);\
                
            // file.seekg(0);
                if(!file.is_open()){
                    cout << endl;
                    center(windowSize/2, " ", "error occured while opening the file, Please try again");
                }else{
                    file << convertToUnderScore(bookName) << endl;
                }
            file.close(); 
        }
};
