#include "./src/dep.h"
#include "./src/payroll_system.h"

int main() {
  PayrollSystem payroll;
  int choice;
  do {
      cout << "\nEMPLOYEE PAYROLL MANAGEMENT SYSTEM\n"
           << "1) FOR-> Add New Employee.\n"
           << "2) FOR-> Display All Employees.\n"
           << "3) FOR-> Search Employee.\n"
           << "4) FOR-> Delete Employee.\n"
           << "5) FOR-> Calculate Net Salary.\n"
           << "6) FOR-> Display ll Employees By Department.\n"
           << "7) FOR-> Update Selected Employee Records.\n"
           << "0) FOR-> Exit.\n"
           << "Enter your choice 0 : 7 -> ";
      cin >> choice;

      switch(choice) {
          case 1: {
              int id;
              string name, d;
              double salary, tax, bonus;
              cout << "\nEnter Employee ID: "; cin >> id;
              cout << "Enter Employee Name: "; cin.ignore(); getline(cin, name);
              cout << "Enter Department: ";    getline(cin, d);
              cout << "Enter Base Salary: ";   cin >> salary;
              cout << "Enter Tax Amount: ";    cin >> tax;
              cout << "Enter Bonus Amount: ";  cin >> bonus;
              payroll.addEmployee(id, name, d, salary, tax, bonus);
              break;
          }

          case 2: {
              payroll.displayAll();
              break;
          }

          case 3: {
              int id;
              cout << "\nEnter Employee ID to search: ";
              cin >> id;
              PayrollNode* emp = payroll.searchEmployee(id);
              if (emp) {
                  cout << "\nOK FOUNDED:";
                  cout << "\n--------------------------------\n";
                  cout << left << setw(15) << "EMP_ID:" << emp->emp_Id << endl
                       << setw(15) << "Name:" << emp->name << endl
                       << setw(15) << "Dept:" << emp->dept << endl
                       << setw(15) << "Salary:" << fixed << setprecision(2) << emp->salary << endl
                       << setw(15) << "Tax:" << emp->tax << endl
                       << setw(15) << "Bonus:" << emp->bonus << endl
                       << setw(15) << "Net Salary:" << (emp->salary + emp->bonus - emp->tax) << endl;
              }
              else cout << "\nNot found\n";
              break;
          }

          case 4: {
              int id;
              cout << "\nEnter Employee ID to delete: ";
              cin >> id;
              if (payroll.deleteEmployee(id)) cout << "\nEmployee deleted successfully\n";
              else cout << "\nEmployee not found\n";
              break;
          }

          case 5: {
              int id;
              cout << "\nEnter Employee ID to calculate net salary: ";
              cin >> id;
              double net = payroll.calculateNetSalary(id);
              if (net >= 0) cout << "\nNet Salary: " << fixed << setprecision(2) << net << endl;
              else cout << "\nEmployee not found\n";
              break;
          }

          case 6: {
              string d;
              cout << "\nEnter Department to display: ";
              cin.ignore(); getline(cin, d);
              payroll.displayByDept(d);
              break;
          }

          case 7: {
              payroll.updateEmployee();
              break;
          }

          case 0: {
              cout << "\nExiting system...\nBye Bye :(";
              break;
          }

          default: {
              cout << "\nInvalid choice. Please try again.\n";
          }
      }
  } while (choice != 0);

  return 0;
}