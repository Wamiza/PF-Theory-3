#include <stdio.h>
#include <string.h>

// Define the Employee structure
struct Employee {
    int employeeCode;
    char employeeName[50];
    int dateOfJoining;
};

void assignEmployee(struct Employee *emp, int code, char name[], int doj) {
    emp->employeeCode = code;
    strcpy(emp->employeeName, name);
    emp->dateOfJoining = doj;
}

int calculateTenure(int dateOfJoining, int currentDate) {
    int joiningYear = dateOfJoining / 10000;
    int currentYear = currentDate / 10000;
    return currentYear - joiningYear;
}

void displayEligibleEmployees(struct Employee employees[], int size) {
    int currentDate;
    printf("Enter the current date (YYYYMMDD): ");
    scanf("%d", &currentDate);

    int eligibleCount = 0;
    printf("\nEmployees with more than 3 years tenure:\n");
    printf("------------------------------------------\n");
    for (int i = 0; i < size; i++) {
        int tenure = calculateTenure(employees[i].dateOfJoining, currentDate);
        if (tenure > 3) {
            eligibleCount++;
            printf("Employee Code: %d\n", employees[i].employeeCode);
            printf("Employee Name: %s\n", employees[i].employeeName);
            printf("Date of Joining: %d\n", employees[i].dateOfJoining);
            printf("Tenure: %d years\n", tenure);
            printf("------------------------------------------\n");
        }
    }
    printf("Total employees with more than 3 years tenure: %d\n", eligibleCount);
}

int main() {
    struct Employee employees[4];

    assignEmployee(&employees[0], 101, "Alice", 20180115);
    assignEmployee(&employees[1], 102, "Bob", 20190520);
    assignEmployee(&employees[2], 103, "Charlie", 20170110);
    assignEmployee(&employees[3], 104, "Diana", 20200215);
    
    displayEligibleEmployees(employees, 4);

    return 0;
}
