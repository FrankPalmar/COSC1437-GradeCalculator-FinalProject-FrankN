# Grade Calculator (OOP Edition)

A C++ console application that tracks graded items, calculates final grades, and saves data between sessions. The program uses an object-oriented design with a `GradedItem` base class and derived classes for Homework, Quiz, and Exam items.

## Author
Frank Nava - COSC 1437, Spring 2026

## Description
This program is for students who want to track grades from homework, quizzes, and exams. It lets the user add graded items, view them in a table, remove items, adjust the grading scheme, and calculate the final grade using either total points or weighted category averages.

## Features
- Menu-driven interface that loops until the user exits
- Three graded-item categories: Homework, Quiz, Exam
- Custom grading scheme: category weights + letter-grade cutoffs
- Two grade modes: points-based and weighted
- Save and load grades to/from `grades.txt`
- Input validation for bad numbers, empty lists, and out-of-range choices
- Confirmation prompt before removing an item
- Aligned table output using `<iomanip>`
- Colored letter grades using ANSI color codes
- Sort items by percentage
- Search items by name
- Statistics dashboard with highest and lowest graded items
- GPA scale conversion for the calculated letter grade

## Files
| File | Purpose |
|------|---------|
| `main.cpp` | Driver program: menu loop, helper functions, file I/O, grade calculations |
| `GradedItem.h` | Abstract base class for all graded items |
| `Homework.h` | Derived class for homework items |
| `Quiz.h` | Derived class for quiz items |
| `Exam.h` | Derived class for exam items |
| `greeting.h` | Header file for the greeting function |
| `greeting.cpp` | Displays a time-based greeting |
| `USER_GUIDE.md` | End-user instructions |
| `README.md` | Repository documentation |

## How to Build
Using g++ (Linux / macOS / WSL / MinGW):

    g++ -std=c++17 *.cpp -o GradeCalculator

## How to Run

    ./GradeCalculator        # macOS / Linux / WSL
    GradeCalculator.exe      # Windows

## Requirements
- C++17 or newer compiler such as g++, clang, or MSVC
- A terminal or console window

## Course Concepts Demonstrated
This project demonstrates Chapters 11-18 of COSC 1437 course material plus four UX enhancement sprints from Labs 19-22.

- Ch 11: `std::vector`, control flow, modular code
- Ch 12: STL algorithms such as `std::min_element`, `std::max_element`, and `std::sort`
- Ch 13: File I/O using `std::ifstream` and `std::ofstream`
- Ch 14: User-defined class with private data and public getters/setters
- Ch 15: Constructors, encapsulation, and calculated properties
- Ch 16: Menu-driven interface, switch statement, and formatted output
- Ch 17: Inheritance and polymorphism
- Ch 18: `std::unique_ptr`, `std::make_unique`, and a `GradingScheme` struct
- Sprint 19: Input validation and robust error handling
- Sprint 20: Save/load functionality
- Sprint 21: Display polish with aligned tables and colored output
- Sprint 22: Sorting, search, statistics, and GPA conversion
