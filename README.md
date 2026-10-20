Municipal Financial ManagerGroup 
Members:
Kennedy shikongo 226002802
Ngoy E Kabamba 226023715
Umar Sabano 226034429
Joia Coimbra 226079678
Josephine 226082237
Samuel Aishe shaningwa 226043789
Tjimezeri Tjihozu 223127418

System
Description of the MFMS
A menu driven console application written in ANSI C (C99) that
manages the core financial records of a municipal: employees and
salaries, departmental budgets, suppliers and the asset register,
with summary reports.
Features
- Main menu with clear navigation and invalid-choice handling
- Employees: add, display, search (ID/ Name / department),
Salary calculations (gross, pension, tax, net)
- Budgets: enter budgets and expenditure, remaining balance,
status, over budget detection
- Suppliers: add (email/ phone validation), display, search,
compare two suppliers
- Assets: add, display, search (ID / name / type / department
/condition)
- Reports: employee, budget, supplier, asset
- Input validation on every field (negative values, empty text,
non-numeric input, duplicates)
- Option 9 loads sample data quick demonstration
- 
Compilation
from the project folder:
gcc –std=c99 –Wall –Wextra –pedantic –o mfms main.c utils.c
employees.c budget.c suppliers.c assets.c reports.c

HOW TO RUN
./mfms
Choose a number from the main menu (1 to 5 for a module, 6 to exit).
Each module has its own menu and a “Back” option

Individual responsibilities

Members
Josephine Lifumbela: Employee management (employee.c employee.h)
Joia Coimbra: Budget Management (budget.c,budget.h)
Umar Sabano: Supplier Management (supplier.c,supplier.h)
Ngoy Kabamba: Assest Management (assets.c, assets.h)
Samuel Aishe: Reports (reports.c, reports.h)
Kennedy K shikongo: Integration and validation (main.c,utils.c, utils.h)
Tjimezeri Muhupua: Testing (testing and test record,TEST.md

Limitations
Data is kept in memory only. Everything entered is lost
when the program closes. Saving files is left for project B.
Maximum sizes are fixed (for example, 100 assets, 100
budgets, 100 suppliers).

Testing
TESTINGMFMS.pdf
