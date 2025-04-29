#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <ctime>
using namespace std;

struct Book {
    string title;
    string author;
    string isbn;
    string borrowerName = "N/A";
    bool available = true;
    tm borrowDate{};
    tm dueDate{};
    tm returnDate{};
    double fine = 0.0;
};

vector<Book> books;

// Utility: Get current date
tm getCurrentDate() {
    time_t t = time(nullptr);
    tm current = *localtime(&t);
    current.tm_hour = 0;
    current.tm_min = 0;
    current.tm_sec = 0;
    return current;
}

// Utility: Add days to a date
tm addDays(tm date, int days) {
    time_t t = mktime(&date);
    t += days * 24 * 60 * 60;
    return *localtime(&t);
}


double calculateFine(const tm& dueDate, const tm& returnDate) {
    time_t due = mktime(const_cast<tm*>(&dueDate));
    time_t ret = mktime(const_cast<tm*>(&returnDate));
    double secondsLate = difftime(ret, due);
    int daysLate = secondsLate / (60 * 60 * 24);
    return daysLate > 0 ? daysLate * 5.0 : 0.0;
}

// Utility: Format date as dd-mm-yyyy
string formatDate(const tm& date) {
    if (date.tm_year <= 0) return "N/A";
    char buf[11];
    strftime(buf, sizeof(buf), "%d-%m-%Y", &date);
    return string(buf);
}

void addBook() {
    Book book;
    cin.ignore();
    cout << "Enter Book Title: ";
    getline(cin, book.title);
    cout << "Enter Book Author: ";
    getline(cin, book.author);
    cout << "Enter Book ISBN: ";
    getline(cin, book.isbn);
    books.push_back(book);
    cout << " Book added successfully!\n";
}

void displayAllBooks() {
    if (books.empty()) {
        cout << " No books in library.\n";
        return;
    }

    cout << left << setw(15) << "Title"
         << setw(15) << "Author"
         << setw(12) << "ISBN"
         << setw(10) << "Available"
         << setw(12) << "Borrower"
         << setw(12) << "Borrowed On"
         << setw(12) << "Due Date"
         << setw(12) << "Returned On"
         << setw(6)  << "Fine" << "\n";
    cout << string(92, '-') << "\n";

    for (const auto& book : books) {
        cout << left << setw(15) << book.title
             << setw(15) << book.author
             << setw(12) << book.isbn
             << setw(10) << (book.available ? "Yes" : "No")
             << setw(12) << book.borrowerName
             << setw(12) << formatDate(book.borrowDate)
             << setw(12) << formatDate(book.dueDate)
             << setw(12) << formatDate(book.returnDate)
             << fixed << setprecision(2)
             << setw(6) << book.fine << "\n";
    }
}

void borrowBook() {
    string query, name;
    cin.ignore();
    cout << "Enter Title, Author, or ISBN to borrow: ";
    getline(cin, query);
    cout << "Enter borrower's Name: ";
    getline(cin, name);

    for (auto& book : books) {
        if ((book.title == query || book.author == query || book.isbn == query) && book.available) {
            book.available = false;
            book.borrowerName = name;
            book.borrowDate = getCurrentDate();
            book.dueDate = addDays(book.borrowDate, 7);
            book.returnDate = {};
            book.fine = 0.0;
            cout << " Book borrowed successfully. Return by: " << formatDate(book.dueDate) << "\n";
            return;
        }
    }

    cout << " Book not found or already borrowed.\n";
}

void returnBook() {
    string query;
    cin.ignore();
    cout << "Enter Title, Author, or ISBN to return: ";
    getline(cin, query);

    for (auto& book : books) {
        if ((book.title == query || book.author == query || book.isbn == query) && !book.available) {
            tm returnDate = getCurrentDate();
            double finePaid = calculateFine(book.dueDate, returnDate);

            book.available = true;
            book.returnDate = returnDate;
            book.fine = finePaid;

            cout << " Book returned on " << formatDate(book.returnDate)
                 << ". Fine to pay:" << fixed << setprecision(2) << finePaid << "\n";
            return;
        }
    }

    cout << " Book not found or already returned.\n";
}

void searchBook() {
    string query;
    cin.ignore();
    cout << "Enter Title, Author, or ISBN to search: ";
    getline(cin, query);

    bool found = false;

    cout << left << setw(15) << "Title"
         << setw(15) << "Author"
         << setw(12) << "ISBN"
         << setw(10) << "Available"
         << setw(12) << "Borrower"
         << setw(12) << "Borrowed On"
         << setw(12) << "Due Date"
         << setw(12) << "Returned On"
         << setw(6)  << "Fine" << "\n";
    cout << string(92, '-') << "\n";

    for (const auto& book : books) {
        if (book.title == query || book.author == query || book.isbn == query) {
            found = true;
            cout << left << setw(15) << book.title
                 << setw(15) << book.author
                 << setw(12) << book.isbn
                 << setw(10) << (book.available ? "Yes" : "No")
                 << setw(12) << book.borrowerName
                 << setw(12) << formatDate(book.borrowDate)
                 << setw(12) << formatDate(book.dueDate)
                 << setw(12) << formatDate(book.returnDate)
                 << fixed << setprecision(2)
                 << setw(6) << book.fine << "\n";
        }
    }

    if (!found)
        cout << " No matching books found.\n";
}

int main() {
    int choice;

    while (true) {
        cout << "\n Library Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Borrow Book\n";
        cout << "3. Return Book\n";
        cout << "4. Search Book\n";
        cout << "5. Display All Books\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: borrowBook(); break;
            case 3: returnBook(); break;
            case 4: searchBook(); break;
            case 5: displayAllBooks(); break;
            case 6: cout << " Exiting...\n"; return 0;
            default: cout << " Invalid choice. Try again.\n";
        }
    }
}
