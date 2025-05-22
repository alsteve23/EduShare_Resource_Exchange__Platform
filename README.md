# 🎓 Academic Resource Management System

A terminal-based academic file manager developed in C++ that allows students to upload, download, and organize study resources efficiently. The system uses **SQLite** as its database engine and supports both **binary file storage (BLOBs)** and external links (e.g., Google Drive).

---

## 🚀 Features

- 📁 **Upload Resources**  
  Add academic resources to the system, associating them with schools, careers, and subjects.

- 🔍 **Browse & Search Resources**  
  List and filter resources by school, career, subject, or ID.

- ⬇️ **Download Files**  
  Retrieve files stored in the database or access them via external URLs.

- 🏫 **Academic Structure Navigation**  
  Navigate through schools, careers, and subjects.

- 🗑️ **Delete Records**  
  Safely remove obsolete or incorrect entries (schools, careers, subjects, or resources).

---

## 🛠️ Tech Stack

- **C++17**
- **SQLite** (compiled using `sqlite3.c` and `sqlite3.h`)
- **CMake** for build configuration
- **Ninja** as the build system

---

## 📁 Project Structure

My_First_Big_Project/
│
├── build/ # Compiled files
├── DataBase/ # SQLite database
├── libraries/ # SQLite C source files
│ ├── sqlite3.c
│ └── sqlite3.h
├── mainEntities/ # Core entity classes
│ ├── career.{h,cpp}
│ ├── resource.{h,cpp}
│ ├── school.{h,cpp}
│ ├── subject.{h,cpp}
│ ├── user.{h,cpp}
│ └── Entities.h
├── main_menu/ # Menus and prompts
├── systemFunctions/ # Logic and operations
│ ├── ResourceSystem.{h,cpp}
├── CMakeLists.txt # CMake build file
└── README.md # Project description
---

## 📦 Build Instructions

1. **Clone the repository:**

   ```bash
   git clone https://github.com/yourusername/My_First_Big_Project.git
   cd My_First_Big_Project
