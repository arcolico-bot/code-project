#include <iostream>
using namespace std;

void clearScreen() {
    for (int i=0; i<50; i++) cout << "\n";
}

void copyText(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

bool isEqual(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

class Book {
public:
    char title[50];
    char author[50];
    char ISBN[20];
    bool available;
    Book() { available = true; }
    void set(const char* t, const char* a, const char* i) {
        copyText(title, t);
        copyText(author, a);
        copyText(ISBN, i);
        available = true;
    }
    void show() {
        cout << title << " by " << author 
             << " (" << ISBN << ") - "
             << (available ? "Available" : "Borrowed") << endl;
    }
};

class User {
public:
    char id[10];
    char name[50];
    char borrowedISBN[20];
    bool hasBook;
    User() { hasBook = false; }
    void set(const char* i, const char* n) {
        copyText(id, i);
        copyText(name, n);
        hasBook = false;
    }
    void show() {
        cout << "User: " << name << " (" << id << ")";
        if (hasBook) cout << " borrowed " << borrowedISBN;
        cout << endl;
    }
};

class Library {
public:
    Book books[100];
    User users[50];
    int bookCount, userCount;
    Library() { bookCount = 0; userCount = 0; }

    void addBook(const char* t, const char* a, const char* i) {
        books[bookCount].set(t,a,i);
        bookCount++;
        cout << "Book added successfully.\n";
    }

    void addUser(const char* id, const char* n) {
        users[userCount].set(id,n);
        userCount++;
        cout << "User added successfully.\n";
    }

    void borrowBook(const char* isbn, const char* uid) {
        int bookIndex = -1, userIndex = -1;
        for (int i=0; i<bookCount; i++) {
            if (isEqual(books[i].ISBN, isbn)) {
                bookIndex = i;
                break;
            }
        }
        for (int j=0; j<userCount; j++) {
            if (isEqual(users[j].id, uid)) {
                userIndex = j;
                break;
            }
        }

        if (bookIndex == -1) {
            cout << "Book not found.\n";
            return;
        }
        if (!books[bookIndex].available) {
            cout << "Book is already borrowed or unavailable.\n";
            return;
        }
        if (userIndex == -1) {
            cout << "User not found.\n";
            return;
        }
        if (users[userIndex].hasBook) {
            cout << "User already has a borrowed book, return it if you want to borrow again.\n";
            return;
        }

        books[bookIndex].available = false;
        copyText(users[userIndex].borrowedISBN, isbn);
        users[userIndex].hasBook = true;
        cout << users[userIndex].name << " borrowed " << books[bookIndex].title << endl;
    }

    void returnBook(const char* isbn, const char* uid) {
        for (int i=0; i<bookCount; i++) {
            if (isEqual(books[i].ISBN, isbn) && !books[i].available) {
                for (int j=0; j<userCount; j++) {
                    if (isEqual(users[j].id, uid) && users[j].hasBook) {
                        books[i].available = true;
                        users[j].hasBook = false;
                        cout << users[j].name << " returned " << books[i].title << endl;
                        return;
                    }
                }
            }
        }
        cout << "Return failed.\n";
    }

    void showBooks() {
        cout << "\nBooks in Library:\n";
        for (int i=0; i<bookCount; i++) books[i].show();
    }

    void showUsers() {
        cout << "\nLibrary Users:\n";
        for (int i=0; i<userCount; i++) users[i].show();
    }
};

int main() {
    Library lib;
    int choice;
    char t[50], a[50], i[20], id[10], n[50];

    lib.addBook("1984","George Orwell","111");
    lib.addBook("To Kill a Mockingbird","Harper Lee","222");
    lib.addBook("The Great Gatsby","F. Scott Fitzgerald","333");
    lib.addUser("U1","Andrew");
    lib.addUser("U2","Arjay");

    do {
        clearScreen();
        cout << "===== Library Menu =====\n";
        cout << "1. Add Book\n";
        cout << "2. Add User\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. Show All Books\n";
        cout << "6. Show All Users\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        clearScreen();

        if (choice == 1) {
            cout << "Enter title: "; cin.getline(t,50);
            cout << "Enter author: "; cin.getline(a,50);
            cout << "Enter ISBN: "; cin.getline(i,20);
            lib.addBook(t,a,i);
        }
        else if (choice == 2) {
            cout << "Enter user ID: "; cin.getline(id,10);
          cout << "Enter name: "; cin.getline(n,50);
            lib.addUser(id,n);
        }
        else if (choice == 3) {
            cout << "Enter ISBN: "; cin.getline(i,20);
            cout << "Enter user ID: "; cin.getline(id,10);
            lib.borrowBook(i,id);
        }
        else if (choice == 4) {
            cout << "Enter ISBN: "; cin.getline(i,20);
            cout << "Enter user ID: "; cin.getline(id,10);
            lib.returnBook(i,id);
        }
        else if (choice == 5) {
            lib.showBooks();
        }
        else if (choice == 6) {
            lib.showUsers();
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
    } while (choice != 0);

    return 0;
}