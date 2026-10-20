    **Municipal Financial Manager System**    ****  Group Members:

| Kennedy shikongo  | 226002802 |
| --- | --- |
| Ngoy E Kabamba | 226023715 |
| Umar Sabano | 226034429 |
| Joia Coimbra | 226079678 |
| Josephine | 226082237 |
| Samuel Aishe shaningwa | 226043789 |
| Tjimezeri Tjihozu | 223127418 |
**Description of the MFMS** A menu driven console application written in ANSI C (C99) that manages the core financial records of a municipal: employees and salaries, departmental budgets, suppliers and the asset register, with summary reports.

**Features**

- Main menu with clear navigation and invalid-choice handling

- Employees: add, display, search (ID/ Name / department), Salary calculations (gross, pension, tax, net)

- Budgets: enter budgets and expenditure, remaining balance, status, over budget detection

- Suppliers: add (email/ phone validation), display, search, compare two suppliers

- Assets: add, display, search (ID / name / type / department /condition)

- Reports: employee, budget, supplier, asset

- Input validation on every field (negative values, empty text, non-numeric input, duplicates)

- Option 9 loads sample data quick demonstration 

    

**Compilation** from the project folder: gcc -std=c99 -Wall -Wextra -pedantic -o mfms main.c utils.c employees.c budget.c suppliers.c assets.c reports.c

HOW TO RUN ./mfms Choose a number from the main menu (1 to 5 for a module, 6 to exit). Each module has its own menu and a “Back” option  **Individual responsibilities**  **Member** 

| Josephine Lifumbela | Employee management (employee.c employee.h |
| --- | --- |
| Joia Coimbra | Budget Management (budget.c, budget.h) |
| Umar Sabano | Supplier Management (supplier.c, supplier.h) |
| Ngoy E Kabamba | Assest Management (assets.c, assets.h) |
| Samuel Aishe | Reports (reports.c, reports.h) |
| Kennedy K shikongo | Integration and validation (main.c, utils.c, utils.h) |
| Tjimezeri Muhupua | Testing (testing and test record, TEST.md |
   **Limitations**

- Data is kept in memory only. Everything entered is lost when the program closes. Saving files is left for project B.

- Maximum sizes are fixed (for example, 100 assets, 100 budgets, 100 suppliers). 

Testing

TEST.md

### Name: Kennedy Shikongo
### Student number: 226002802 Github username: https://github.com/226002802-kennedy-shikongo
Responsibility designated: Integration & validation (make all modules compile together and run together and make sure that bad input will not break it).

The five modules were combined into one (program.c). Replaced the 'coming soon' notices in main.c with the actual assets and reports menus. The project was copied to an un-nested folder structure and files that must not be compiled (the unprocessed supplier file and the asset test file, each with its own main() function) were removed. Repaired the file name case problems (Assests.c to assets.c) and the duplicate definitions between the modules. Rewrote the budget input functions (readInt, readDouble and readNonEmpty in utils.c) to prevent the budget menu from running in an endless loop with alphabetic input and to impose minimium and maximum values. Fixed the employee name validation (getText) so that a name of only spaces is rejected. Rewrote reports.c so it makes use of the functions offered already by the other modules. Incorporated the new supplier module into suppliers.c. 

GitHub contribution: Commits on my branch kennedy-reports-suppliers for the integration fixes, the flat layout move and the supplier integration, merged into main via a pull request. I created README.md and.gitignore.

During integration, I verified input validation for each module, in the following order: alphabetic, negative, zero, empty line, spaces only, duplicate ID's, invalid menu selection. These verifications identified the menu loop in the budget module, the space-only employee name problem, and the invalid phone number problem, which were all corrected and re-verified. I compiled the program from a fresh clone to verify it has no warnings or errors.

  Name: Josephine Lifumbela Muzuki
### Student number: 226082237
Role & responsibility: Main Menu Module & Core Interface Routing (Designing the main terminal controller for the Municipal Financial Management System and designing the user options flow and making it cross-platform compatible for any terminal).

Created functions and modules: I developed the main menu (main.c) of the MFMS: it is the main access to and routing center for all individual modules. I developed the displayMenu() function (in a continuous control loop) for selecting options 1-6, input validation, and error-free routing to the modules' submenus (employeeMenu(), budgetMenu(), supplierMenu(), assetMenu(), reportsMenu()).

I also had to address numerous development issues in text based environment and terminal needs along the way, e.g. the custom color aesthetics when developing the terminal have broken rendering (i.e. Raw ANSI text escape strings), causing the text to appear in broken characters, and breaking compilation syntax. I solved these by thoroughly studying terminal character mappings in order to discover the specific number-ANSI color number sequences to provide the specific colors with, i.e., 0m will reset colors, &color number&m, (where the number represents a color). Additionally in order to fix the environment specific header and Intelli Sense compiler errors caused from the file interface tags and #pragma errors in the #include implementations, I researched and added conditional preprocessor directives of #ifdef _WIN32 and #endif with on Windows, allowing the terminal of Windows to understand the character/numeral sequence allowing it to interpret the color numbers without breaking cross-compilation or creating duplicate definitions across members files for other members. (Ai assists also used for system-level environment fixes and structural text writing).

GitHub contribution: Development branch commits for main menu initialization, ANSI color mapping variables, Cross platform Pre-processor blocks, Terminal validation changes made to the main branch through pull request. Github account is https://github.com/226082237-josehine

Tests done: I tested the menu loop to ensure it would continue to iterate from choice to choice, and that a bad choice would just be handled with out crashing the console app. I also explicitly tested the validation layout with non-numeric character breaks, and spaces to avoid infinite loops while I make iterations on the interface, and tested the text variables across different terminal environments to ensure they print correctly.
### Name: Kabamba Ngoy
### GitHub Account: https://github.com/22601375-Kabamba/MFMS
### Student number: 226013715
Responsible for: Asset management module: Manage, view, search, report on all municipal assets with validation for each field.

Created functions and modules: assets.h and assets.c created for assets module Asset.h: a header file that contains the Asset structure with data and methods (asset id, name, type, purchase value, Dept and Condition), sizeof() data, constants, prototypes for public functions and an include guard. Assets are stored in a private array with an associated 'assetCount' variable (assets[MAX_ASSETS] and assetCount). Assets are static so data can only be accessed by other modules through the public functions: getAssetCount() and getTotalAssetValue().

Validation I created the validation as little helpers you can re-use. Read Line uses fgets, so it works with names that contain spaces and always discards any leftovers from a long input. IsBlank and readNonEmpty discard empty input or all-blank input. Read Positive Double discards everything else, and discards partially-numeric input like "12bc" and discards all-zero and negative doubles. Read Menu Choice asks again if the choice is outside of a specified range. FindAssetById and containsIgnoreCase are helpers for duplicate-checking and search.

All main operations are called above helpers. Add Asset performs input validation to make sure our asset is unique, non-empty and we only add set types and conditions (using the numbered menu below, so types/conditions are always the same) all against a local variable. It is then copied into the array.displayAsset performs a nicely formatted table.searchAssets performs a search by full id or a case insensitive search by partial name or department.displayAssetReport is a summary report which displays total assets, total value, average value and total assets in poor condition (runs the total assets in poor condition check first to avoid division by 0).asset Menu is the sub-menu that main.c calls.I also wrote a small driver, test_assets.c so this module can be compiled/tested independently of group's main.c.

In developing I managed to address several build issues were can not find header file (replace with file location which was not correctly capitalized assets.h the file name in project folder and in the #include declaration). I also got an undefined reference to main linker error (installed module in drive). This was because I had run the module independently using the run button (try, compile it separately so that if it is run outside the environment it will also combine it with the test driver I also obtained a single file version of the program so that I can run the code in an online compiler). I use AI as a tool to generate and debug this module [VERIFY, if allowed]. I have checked and tested the code myself and I can explain how each of the functions work.

Github contribution: I created my local repository; committed the Assets module (assets.h, assets.c and the test driver) and pushed to the group repository 22601375-Kabamba/MFMS. I fixed 403 permission denied by switching my account to retrieve the account name, then logged into the account on Github with my personal token. I fixed rejection of the push by pulling and merging remote history before being able to push again.

Code used and tested: compiled with gcc -std=c99 -Wall -Wextra -pedantic and found no warnings or errors. I used the driver and compiled separately, tested with the following input: normal asset entry, duplicate asset id rejected with error message, negative purchase value, 0, letters instead of numbers as input, empty department input, invalid menu choice, search by id, name, department, no match in search, print full register, report with poor condition assets. All invalid inputs rejected and then asked for again without crashing. Totals were calculated properly (2 assets at 350000 and 18000 summed to 368000 with a mean of 184000).

Name: Umar Sabano

 

Student number: 226034429

 

Assigned responsibility: Supplier Management

 

Github username: Umar-nust (https://github.com/Umar-nust)

 

What I did: I created the supplier module (suppliers.c) including add, view, edit and delete. We then realized that something was missing: the email address, town and search menu (by ID, by name, by town). I put in validation as well: phone number checking only digits and length check for Namibian numbers, email format and not empty names or towns. I tested with valid, invalid and borderline input and then corrected any errors.

Built-in functions: addSupplier(), viewSuppliers(), searchSuppliers(), editSupplier(), deleteSupplier(), supplierMenu(), findSupplier(), isValidPhone(), isValidEmail(), containsIgnoreCase(), printHeader(), printSupplier(), readLine(), readInt(), isBlank().

String functions used: strlen, strcpy, strchr, strrchr, strstr.

 

Testing done:

 

Added fake suppliers. Verified table output.

Tested invalid emails and phone numbers (alphabets, symbols, too short, too long etc) and verified that they did not pass validation.

Left name and town blank, and verified the prompts it repeated.

Searching by ID, name and town – also partial, mixed-case text and mismatches.

Edited and deleted suppliers and cross checked.

Made invalid menu choices and input too long and did not crash.

Tested compiling with https://onecompiler.com/c with some errors but managed. 

### Name: Coimbra Joia Jumina
### Student number: 226079678
Budget Management Module creation and deployment (designing and programming the core engine for budget management features such as track budgets, allocation, and their data).

Features and modules you built: Implemented the budget module (budget.c and budget.h). Built the static budget storage array (MAX_BUDGETS), a function to look up the index of a department (findBudgetIndex), sample budget initialization values (loadSampleBudgets), and functions to calculate a department's remaining funds, the added funds to a budget, and spending out of a budget. Integrated these features smoothly with the rest of the project structure and shared functions. [AI assistance was used to sketch and debug code structure as allowed by course rules]

GitHub contribution: Contribution of the commits to the repository of the files of the module budget, organization of the directory structure of the project and selection of the correct files for the compilation process. 

Results of test: Both gcc terminal builds (gcc -c for module compiling, full system with all modules) tested successfully. Confirmed correct loading of sample budget data in other modules, conformed correctness of lookup functions in departments and the successful load of the module to main program menu with no compilation warnings or errors. 

Github username: https://github.com/226079678coimbra

### Name: Tjimezeri Tjihozu
Github username: Name: Tjimezeri Tjihozu
### Student number: 223127418
Responsibility assigned: Testing lead (Manual testing, integration checks and quality assessment of all modules of the system).

As the testing lead I performed manual testing of the assembled program with valid and bad inputs (letters, negative numbers, zeros, empty lines, spaces-only, and invalid menu choices) for all modules. I validated that a clone of the repository assembles cleanly with (gcc -std=c99 -Wall -Wextra -pedantic) with zero errors and warnings. Tested the main menu navigation and exit routines; Employee Management validation of daily rates, allowances, IDs; Budget Management validation of expenses, gross/net over budgets; Supplier Management validation of phone/email; Employee Management (again) validation of case-insensitive search; Asset Management validation of case-insensitive search and condition validation; and integrated generation of cross-referenced reports, documenting edge cases not yet performed due to time constraints.

Responsibility assigned: Testing lead (Manual testing, integration checks and quality assessment of all modules of the system).

As the testing lead I performed manual testing of the assembled program with valid and bad inputs (letters, negative numbers, zeros, empty lines, spaces-only, and invalid menu choices) for all modules. I validated that a clone of the repository assembles cleanly with (gcc -std=c99 -Wall -Wextra -pedantic) with zero errors and warnings. Tested the main menu navigation and exit routines; Employee Management validation of daily rates, allowances, IDs; Budget Management validation of expenses, gross/net over budgets; Supplier Management validation of phone/email; Employee Management (again) validation of case-insensitive search; Asset Management validation of case-insensitive search and condition validation; and integrated generation of cross-referenced reports, documenting edge cases not yet performed due to time constraints.

### Name: Samuel Aishe Shaningwa
### Student number: 226043789
Assigned responsibility: Reports module.

Functions/modules written: I had written the Reports module and its utility functions as a first draft. This draft included the reports menu and the employee, budget, supplier and asset reports, along with a function to print all four at once.

GitHub contribution: "Add reports module and utility functions - Contribution by Shaningwa" was my commit which brought the Reports module into the repo. GitHub username: https://github.com/226043789-Shaningwa

Tests carried out: I did not make separate tests. The project test record was written by Tjimezeri Muhupua.

Github repository: https://github.com/22601375-Kabamba/MFMS


