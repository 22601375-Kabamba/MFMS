#ifndef EMPLOYEEES_H
#define EMPLOYEES_H
#define MAX_EMPLOYEES 100

typedef struct Employee {
    int id;
    char firstName[60];
    char lastName[60];
    char housePhone[10];
    char department[60];
    char houseAddress[70];
    char emailAddress[60];
    int age;
    char dob[15];
    float basicSalary;
    float housingAllowance;
    float transportAllowance;
    float grossSalary;
    
};

void addEmployee(struct Employee emp[], int *count);
void displayEmployee(struct Employee emp[], int count);
void searchEmployee(struct Employee emp[], int count);
void calculateSalary(struct Employee *emp);
void printEmployeeDetails(struct Employee emp);

#endif