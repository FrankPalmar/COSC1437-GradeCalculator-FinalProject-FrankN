# User Guide - Grade Calculator (OOP Edition)

## Introduction
The Grade Calculator helps you track homework, quiz, and exam grades. You can add graded items, view everything in a table, calculate your grade two different ways, and save your work so you can load it again later.

## Getting Started
Build the program using the command shown in the README file. After it builds, run the program from your terminal using `./GradeCalculator` on macOS/Linux/WSL or `GradeCalculator.exe` on Windows.

## Menu Walkthrough
When the program starts, it shows a menu. Enter the number for the option you want.

### 1. Set grading scheme
Use this option to change the grading weights and letter-grade cutoffs.

The program asks for:
- Homework weight percent: number from 0 to 100
- Quiz weight percent: number from 0 to 100
- Exam weight percent: number from 0 to 100
- Minimum percent for A: number from 0 to 100
- Minimum percent for B: number from 0 to 100
- Minimum percent for C: number from 0 to 100
- Minimum percent for D: number from 0 to 100

Rules:
- The three category weights must add up to 100%.
- The cutoffs must be in order: A > B > C > D.
- Example default style: Homework 20%, Quiz 30%, Exam 50%; A 90, B 80, C 70, D 60.

### 2. Add graded item
Use this option to add a homework, quiz, or exam grade.

The program asks for:
- Category: choose 1 for Homework, 2 for Quiz, or 3 for Exam
- Item name: text with no spaces, like `HW1`, `Quiz1`, or `Midterm`
- Points possible: positive number greater than 0
- Points earned: number from 0 up to the points possible

The program will not accept points earned greater than points possible.

### 3. View all items
This shows every graded item in a clean table.

The table shows:
- Item number
- Category
- Name
- Points earned
- Points possible
- Percentage

If there are no items, the program tells you that no graded items have been added yet.

### 4. Remove item
Use this option to delete a graded item.

The program shows the current list, then asks:
- Item number to remove
- Confirmation: `y` or `n`

If you type `y`, the item is removed. If you type `n`, nothing is deleted.

### 5. Calculate points-based grade
This calculates your grade using all points together.

Formula:

    total points earned / total points possible * 100

The result shows:
- Total points earned
- Total points possible
- Percentage
- Letter grade
- GPA points

### 6. Calculate weighted grade
This calculates your grade by category weight.

The program calculates:
- Homework average times homework weight
- Quiz average times quiz weight
- Exam average times exam weight

Then it adds the category contributions together. If a category has no items, that category average is treated as 0%.

### 7. Save grades to file
This saves your grading scheme and all graded items to a file called `grades.txt`.

Use this before exiting if you want to keep your data.

### 8. Load grades from file
This loads your saved grading scheme and graded items from `grades.txt`.

If the file is missing or broken, the program shows an error instead of crashing.

### 9. Sort items by percentage
This sorts the graded items from lowest percentage to highest percentage.

After sorting, the program displays the updated table.

### 10. Search item by name
Use this option to look for an item by name.

The program asks for all or part of the item name. For example, searching `Quiz` can find `Quiz1` and `Quiz2`.

### 11. Show statistics
This shows a small dashboard with:
- Number of items
- Total points earned
- Total points possible
- Overall points-based percent
- Highest item
- Lowest item

### 0. Exit
This closes the program.

Save your grades first with option 7 if you want to keep them.

## Sample Session
This is an example of a full run. Your greeting may be different depending on the time of day.

```text
Good afternoon!

Welcome to the COSC 1437 Grade Calculator

Grade Calculator Menu
=====================
1. Set grading scheme
2. Add graded item
3. View all items
4. Remove item
5. Calculate points-based grade
6. Calculate weighted grade
7. Save grades to file
8. Load grades from file
9. Sort items by percentage
10. Search item by name
11. Show statistics
0. Exit
Enter your choice: 1

Grading Scheme Setup
====================
Category weights must add up to 100%.

Homework weight percent: 20
Quiz weight percent: 30
Exam weight percent: 50

Letter grade cutoffs must be in order: A > B > C > D.
Minimum percent for A: 90
Minimum percent for B: 80
Minimum percent for C: 70
Minimum percent for D: 60
Grading scheme updated successfully!

Enter your choice: 2

Add Graded Item
===============
1. Homework
2. Quiz
3. Exam
Choose a category: 1
Enter item name (no spaces): HW1
Enter points possible: 100
Enter points earned: 95
Item added successfully!

Enter your choice: 2

Add Graded Item
===============
1. Homework
2. Quiz
3. Exam
Choose a category: 2
Enter item name (no spaces): Quiz1
Enter points possible: 50
Enter points earned: 45
Item added successfully!

Enter your choice: 2

Add Graded Item
===============
1. Homework
2. Quiz
3. Exam
Choose a category: 3
Enter item name (no spaces): Exam1
Enter points possible: 200
Enter points earned: 180
Item added successfully!

Enter your choice: 3

Current Graded Items
====================
#     Category      Name                      Earned    Possible     Percent
----------------------------------------------------------------------------
1     Homework      HW1                         95.00      100.00      95.00%
2     Quiz          Quiz1                       45.00       50.00      90.00%
3     Exam          Exam1                      180.00      200.00      90.00%

Enter your choice: 5

Points-Based Grade
==================
Total Points Earned: 320.00
Total Points Possible: 350.00
Percentage: 91.43%
Letter Grade: A
GPA Points: 4.00

Enter your choice: 6

Weighted Grade
==============
Category           Average      Weight    Contribution
------------------------------------------------------
Homework            95.00%      20.00%          19.00%
Quiz                90.00%      30.00%          27.00%
Exam                90.00%      50.00%          45.00%

Final Weighted Percentage: 91.00%
Letter Grade: A
GPA Points: 4.00

Enter your choice: 7
Grades saved successfully to grades.txt!

Enter your choice: 0
Thank you for using Grade Calculator!
```

## Sprint Features

### Sprint 19 - Input validation
The program checks menu choices and number inputs. If you type letters when a number is expected, or choose a number outside the allowed range, the program asks again instead of crashing.

How to use it: just use the program normally. The validation happens automatically.

### Sprint 20 - Save and load
Use option 7 to save your grades to `grades.txt`. Use option 8 to load the saved grades later.

How to use it:
1. Add your graded items.
2. Choose option 7 to save.
3. Restart the program.
4. Choose option 8 to load.

### Sprint 21 - Display polish
The program uses aligned tables so the grade list is easier to read. It also uses color codes for letter grades.

How to use it: choose option 3 to view the table, or options 5 and 6 to see colored letter grades.

### Sprint 22 - Sorting, search, statistics, and GPA conversion
The program includes extra final-polish tools:
- Option 9 sorts grades by percentage.
- Option 10 searches for an item by name.
- Option 11 shows statistics.
- Options 5 and 6 also show GPA points.

## Understanding Your Results

### Points-based grade
The points-based grade ignores categories. It adds all points earned and divides by all points possible.

Use this if your class grade is based only on total points.

### Weighted grade
The weighted grade calculates each category average first, then applies the category weights.

Use this if your class syllabus says homework, quizzes, and exams are worth different percentages.

Example:
- Homework average: 95%, weight 20%, contribution 19%
- Quiz average: 90%, weight 30%, contribution 27%
- Exam average: 90%, weight 50%, contribution 45%
- Final weighted grade: 91%

## Known Limitations
- Item names should not contain spaces. Use names like `HW1`, `Quiz_1`, or `FinalExam`.
- The save file is a simple text file named `grades.txt`. Editing it by hand can break the load feature.
- If a weighted category has no items, that category counts as 0% in the weighted calculation.
- ANSI color codes may not display correctly in older Windows terminals.

## Troubleshooting

### Problem: I typed letters when the program asked for a number.
The program will show an invalid input message and ask again. Type a valid number to continue.

### Problem: The program says no saved file was found.
You probably have not saved yet, or `grades.txt` is not in the same folder as the program. Add grades and use option 7 to save.

### Problem: My item name got cut off after the first word.
Names cannot contain spaces. Use an underscore instead, like `Chapter_1_Quiz`.

### Problem: My weighted grade seems low.
Check if one category has no items. Empty weighted categories count as 0%, so add at least one homework, quiz, and exam for a complete weighted grade.
