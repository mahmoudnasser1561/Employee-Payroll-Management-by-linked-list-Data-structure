#include "dep.h"

struct PayrollNode {
  int emp_Id;
  string name , dept;
  double salary , tax , bonus;
  PayrollNode* next;

  PayrollNode ( int id, string n, string d, double sal, double t, double b) {
    emp_Id = id;
    name = n;
    dept = d;
    salary = sal;
    tax = t;
    bonus = b;
    next = nullptr;
  }
};

class PayrollSystem {
  private:
      PayrollNode* head;
  
      const int idWidth = 8;
      const int nameWidth = 20;
      const int deptWidth = 15;
      const int numWidth = 12;
      const int netWidth = 12;
  
  public:
      PayrollSystem();
  
      void addEmployee(int, string, string, double, double, double);
  
      void displayAll();
  
      PayrollNode* searchEmployee(int);
  
      bool deleteEmployee(int id);
  
      double calculateNetSalary(int id);
  
      void displayByDept(string d);
  
      void updateEmployee();
  
      // Destructor
      ~PayrollSystem();
  };
  