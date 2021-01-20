#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student{
    int id;
    string name;
    int marks;
    int age;
};

void insert_data(fstream &write){

    Student s1;
    cout << "Enter ID: ";
    cin >> s1.id;
    cout << endl << "Enter Name: ";
    cin.get();
    getline(cin, s1.name);
    cout << endl << "Enter Marks: ";
    cin >> s1.marks;
    cout << endl << "Enter Age: ";
    cin >> s1.age;

    write << s1.id << endl;
    write << s1.name << endl;
    write << s1.marks << endl;
    write << s1.age << endl;

    // write.write((char *) &s1, sizeof(Student));
}

Student get_data(fstream &read){
    Student obj;
    read >> obj.id;
    read.get();
    getline(read, obj.name);
    read >> obj.marks;
    read >> obj.age;

    cout << obj.id;
    cout << obj.name;
    // read.read((char *) &obj, sizeof(Student));
    return obj;
}

int main(){
    // ofstream f;//write
    // ifstream r;//read
    fstream write("record.txt", ios::in | ios::out);
    // insert_data(write);
    get_data(write);
} 