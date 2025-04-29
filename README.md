# 📚 Library Management System (C++ + SQLite3)

A simple and efficient **Library Management System** developed using **C++** and **SQLite3**. This project manages books in a library and keeps track of borrow and return operations, along with fine calculation for late returns.

---

## 🚀 Features

- 📖 Add new books
- 👤 Borrow books with borrower name and due date
- 🔁 Return books with automatic fine calculation (₹5/day late)
- 🔍 Search books by Title, Author, or ISBN
- 📋 Display all books with full details in tabular format
- 🗃️ Data persistence using **SQLite3**

---

## 💡 Functionalities

Each book record includes:
- Title
- Author
- ISBN
- Availability status
- Borrower name
- Borrow date
- Due date
- Return date
- Fine if returned late

---

## 🛠️ Tech Stack

- **C++** – Core logic and menu interface
- **SQLite3** – Persistent database storage
- **Standard Library (STL)** – For string/date formatting, I/O

---

## 🔧 Requirements

- C++ Compiler (like `g++`)
- SQLite3 installed

### 💻 Installing SQLite3 (Linux)

```bash
sudo apt-get install sqlite3 libsqlite3-dev
