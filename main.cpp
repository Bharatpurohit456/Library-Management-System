#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Book {
protected:
    int id;
    string title, author;
public:
    Book() {}
    Book(int i, string t, string a) {
        id = i;
        title = t;
        author = a;
    }
    void display() {
        cout << "Book ID: " << id << "\nTitle: " << title << "\nAuthor: " << author << endl;
    }
    int getID() { return id; }
    string getTitle() { return title; }

    bool match(int i) { return id == i; }
    bool match(string t) { return title == t; }

    friend void showBookDetails(Book b);
};

void showBookDetails(Book b) {
    cout << "\n[Friend Function] Book Info:\n";
    cout << "ID: " << b.id << " | Title: " << b.title << " | Author: " << b.author << endl;
}

class Library {
    Book books[50];
    int count;
public:
    Library() { count = 0; }

    void addBook(Book b) {
        if(count < 50) {
            books[count++] = b;
            cout << "Book added successfully!\n";
        } else cout << "Library full!\n";
    }

    void displayBooks() {
        if(count == 0) cout << "No books available.\n";
        else {
            for(int i = 0; i < count; i++) {
                cout << "\nBook " << i+1 << ":\n";
                books[i].display();
            }
        }
    }

    void searchBook(string name) {
        for(int i = 0; i < count; i++) {
            if(books[i].match(name)) {
                cout << "Book Found:\n";
                books[i].display();
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void searchBook(int id) { 
        for(int i = 0; i < count; i++) {
            if(books[i].match(id)) {
                cout << "Book Found:\n";
                books[i].display();
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void saveToFile() {
        ofstream fout("library.txt", ios::out);
        for(int i = 0; i < count; i++) {
            fout << books[i].getID() << "," << books[i].getTitle() << endl;
        }
        fout.close();
        cout << "Data saved to file.\n";
    }
};

class Student {
    string name;
    int roll;
public:
    Student(string n, int r) {
        name = n;
        roll = r;
    }
    void show() {
        cout << "Student: " << name << " | Roll: " << roll << endl;
    }
};

class Admin : public Library {
public:
    void welcomeMsg() {
        cout << "\nWelcome to Library Management System!\n";
    }
};

int main() {
    Admin lib;
    lib.welcomeMsg();
    Student s("Bharat", 101);
    s.show();

    int choice;
    do {
        cout << "\n1. Add Book\n2. Display Books\n3. Search by Title\n4. Search by ID\n5. Save & Exit\nEnter your choice: ";
        cin >> choice;

        if(choice == 1) {
            int id;
            string title, author;
            cout << "Enter Book ID: "; cin >> id;
            cin.ignore();
            cout << "Enter Title: "; getline(cin, title);
            cout << "Enter Author: "; getline(cin, author);
            Book b(id, title, author);
            lib.addBook(b);
            showBookDetails(b);
        }
        else if(choice == 2) lib.displayBooks();
        else if(choice == 3) {
            string name;
            cin.ignore();
            cout << "Enter Book Title: ";
            getline(cin, name);
            lib.searchBook(name);
        }
        else if(choice == 4) {
            int bid;
            cout << "Enter Book ID: ";
            cin >> bid;
            lib.searchBook(bid);
        }
        else if(choice == 5) {
            lib.saveToFile();
            cout << "Exiting...\n";
        }
        else cout << "Invalid choice!\n";
    } while(choice != 5);

    return 0;
}
