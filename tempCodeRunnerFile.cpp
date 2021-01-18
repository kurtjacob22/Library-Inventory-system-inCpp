 Book readBook;
    fstream readFile("HumptyDumpy.dat", ios::binary | ios::in | ios::out);
    readFile.seekg(0);
    if(!readFile.is_open()){
        cout << "error occured while opening the file";
    }else{  
        readFile.read((char *) &readBook, sizeof(Book));
    }

    cout << readBook.authorName << endl;