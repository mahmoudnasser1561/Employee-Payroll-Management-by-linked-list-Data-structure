#include "dep.h"
#include "payroll_system.h"

PayrollSystem::PayrollSystem() {
    head = NULL;
}

void PayrollSystem::addEmployee(int id, string name, string d, double salary, double tax, double bonus) {
    PayrollNode* newNode = new PayrollNode(id, name, d, salary, tax, bonus);

    if (head==NULL) {
        head = newNode;
    }
    else {
        PayrollNode* temp = head;
        while (temp->next!=NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    cout << "\nNew employee added successfully!\n";
}

void PayrollSystem::displayAll() {
    if (head==NULL) {
        cout <<endl<< "No employees founded."<<endl;
        return;
    }

    cout <<endl<< "ALL EMPLOYEE PAYROLL INFORMATION"<<endl;
    cout << "====================================================================================================="<<endl;
    cout << left << setw(idWidth) << "ID"
         << setw(nameWidth) << "NAME"
         << setw(deptWidth) << "DEPARTMENT"
         << right << setw(numWidth) << "SALARY"
         << setw(numWidth) << "TAXES"
         << setw(numWidth) << "BONUS"
         << setw(netWidth) << "NET PAY" << endl;
    cout << "====================================================================================================="<<endl;

    PayrollNode* temp = head;
    while (temp) {
        double netSalary = temp->salary + temp->bonus - temp->tax;
        cout << left
             << setw(idWidth)<< temp->emp_Id
             << setw(nameWidth) << temp->name
             << setw(deptWidth) << temp->dept
             << right << fixed << setprecision(2)
             << setw(numWidth) << temp->salary
             << setw(numWidth) << temp->tax
             << setw(numWidth) << temp->bonus
             << setw(netWidth) << netSalary << endl;
        temp = temp->next;
    }
}

PayrollNode* PayrollSystem::searchEmployee(int id) {
    PayrollNode* temp = head;
        while (temp!= NULL) {
            if (temp->emp_Id == id) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
}

bool PayrollSystem::deleteEmployee(int id) {
    if (head==NULL) return false;

    if (head->emp_Id == id) {
        PayrollNode* toDelete = head;
        head = head->next;
        delete toDelete;
        return true;
    }

    PayrollNode* temp = head;
    while (temp->next) {
        if (temp->next->emp_Id == id) {
            PayrollNode* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

double PayrollSystem::calculateNetSalary(int id) {
    PayrollNode* emp = searchEmployee(id);
    return emp ? (emp->salary + emp->bonus - emp->tax) : -1;
}

void PayrollSystem::displayByDept(string d) {
    if (!head) {
        cout << "\nNo employees found.\n";
        return;
    }

    cout << "\nEMPLOYEES IN " << uppercase << d << " DEPARTMENT\n"
    << "===================================================================\n"
         << left << setw(idWidth) << "EMP_ID"
         << setw(nameWidth) << "NAME"
         << right << setw(numWidth) << "SALARY"
         << setw(netWidth) << "NET PAY" << endl
    << "===================================================================\n";

    PayrollNode* temp = head;
    bool found = false;
    while (temp) {
        if (temp->dept == d) {
            double net = temp->salary + temp->bonus - temp->tax;
            cout << left
                 << setw(idWidth) << temp->emp_Id
                 << setw(nameWidth) << temp->name
                 << right << fixed << setprecision(2)
                 << setw(numWidth) << temp->salary
                 << setw(netWidth) << net << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "No employees found in " << d << " department"<<endl;
    }
}

void PayrollSystem::updateEmployee() {
    if (!head) {
        cout << "\nNo employees founded!\n";
        return;
    }

    int id;
    cout << "\nEnter Employee ID : "; cin >> id;

    PayrollNode* emp = searchEmployee(id);
    if (!emp) {
        cout << "Employee not found!\n";
        return;
    }

    cout << "\nCurrent Record:\n";
    cout << "----------------------------------------\n";
    cout << "1. Salary: " << emp->salary << endl;
    cout << "2. Tax: " << emp->tax << endl;
    cout << "3. Bonus: " << emp->bonus << endl;
    cout << "----------------------------------------\n";

    int f;
    cout << "Select field (1 or 2 or 3) ?: "; cin >> f;

    if (f < 1 || f > 3) {
        cout << "Invalid choice!\n";
        return;
    }

    int operation;
    cout << "Select operation:\n1. Increase\n2. Decrease\nChoice: "; cin >> operation;

    if (operation != 1 && operation != 2) {
        cout << "Invalid operation!\n";
        return;
    }

    double amount;
    cout << "Enter amount: "; cin >> amount;

    switch (f) {
        case 1: // Salary
            if (operation == 1) { // +
                emp->salary += amount;
                cout << "Salary increased by " << amount << endl;
            } else { //-
                emp->salary = (emp->salary - amount < 0) ? 0 : emp->salary - amount;
                cout << "Salary decreased by " << amount << endl;
            }
            break;
        case 2: // Tax
            if (operation == 1) { // +
                emp->tax += amount;
                cout << "Tax increased by " << amount << endl;
            }
            else { //-
                emp->tax = (emp->tax - amount < 0) ? 0 : emp->tax - amount;
                cout << "Tax decreased by " << amount << endl;
            }
            break;
        case 3: // Bonus
            if (operation == 1) { // +
                emp->bonus += amount;
                cout << "Bonus increased by " << amount << endl;
            }
            else { //-
                emp->bonus = (emp->bonus - amount < 0) ? 0 : emp->bonus - amount;
                cout << "Bonus decreased by " << amount << endl;
            }
            break;
    }

    cout << "\nUpdated Record:\n";
    cout << "----------------------------------------\n";
    cout << "Salary: " << emp->salary << endl;
    cout << "Tax: " << emp->tax << endl;
    cout << "Bonus: " << emp->bonus << endl;
    cout << "Net Salary: " << (emp->salary + emp->bonus - emp->tax) << endl;
    cout << "----------------------------------------\n";
}

PayrollSystem::~PayrollSystem() {
    PayrollNode* current = head;
    while (current) {
        PayrollNode* next = current->next;
        delete current;
        current = next;
    }
}