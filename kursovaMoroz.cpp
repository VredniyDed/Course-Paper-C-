//підключення бібліотек
#include <iostream>
#include <vector>
#include<string>
#include <iomanip>
//попередне оголошення класів OfficeWorker та HiredWorker
class OfficeWorker;
class HiredWorker;
//абстрактний клас BaseWorker
class BaseWorker {
protected:
  // поля класу BaseWorker
  float salary;
  std::string name;
  unsigned int age;
  // чиста віртуальна функція
  virtual void print() = 0;
  // методи, що ініціалізують та повертають значення поля name
  void setName() {
    std::cout << "\tEnter name -> ";
    std::cin.get();
    std::getline (std::cin,name);
  }

  // методи, що ініціалізують та повертають значення поля age
  void setAge() {
    std:: cout << "\tEnter age -> ";
    std::cin >> age;
    while (age<18 || age>75) {
    std::cout << "\tAge must be >=18 and <=75" << "\n\t";
    std::cin >> age;
    }
  }

public:
  //пустий конструктор
  BaseWorker() {}
};
// Manager клас-нащадок класу BaseWorker
class Manager : public BaseWorker {
private:
  // приватні поля класу Manager
  std::vector<OfficeWorker> workers;
  std::vector<HiredWorker> hiredWorkers;
protected:
  //поля та методи для наслідування нащадками
  std::string rangee;
  unsigned int daysPerMonth;
  unsigned int numOfmonth;
  float payForDay;
  // метод на основі значення змінної numOfmonth задає значення для полів rangee та payForDay
  void range(){
    if (numOfmonth <12) {
      rangee = "Junior Manager";
      payForDay = 347.33;
    }
    else if (numOfmonth > 24) {
      rangee = "Senior Manager";
      payForDay = 652.67;
    }
    else  {
    rangee = "Middle Manager";
    payForDay = 869.33;
    }
  }
  // метод на основі значення змінної payForDay,daysPerMonth, workers.size() задає значення для поля salary
  float countSalary() {
    salary = payForDay*daysPerMonth+workers.size()*100;
    return salary;
  }
public:
  //пустий конструктор класу Manager
  Manager(){}
    //конструктор класу Manager  з параметрами
  Manager(std::string n, unsigned int ag, unsigned int num, unsigned int dPM){
    name = n;
    age  = ag;
    numOfmonth = num;
    daysPerMonth = dPM;
    range();
  }
  //прототипи методів класу Manager, реалізація яких винесена за межі класу
  void addOfficeWorker();
  void deleteOfficeWorker();
  void printOfficeWoorkers();
  void addHiredWorker();
  void deleteHiredWorker();
  void printHiredWoorkers();
  void print(); // прототип перевизначеної функці\ батьківського класу
  //метод класу Manager, що виклизає методи, які ініціалізують поля об'єкта класу
  void setFields() {
    std::cout << "****************************************************************" << '\n';
    std::cout << "DATA FOR MANAGER" << '\n';
    this->setName();
    this->setAge();
    this->setNumOfMonth();
    this->setDaysPerMonth();
    std::cout << "****************************************************************" << '\n';
    range();
    countSalary();
  }
  // метод класу Manager, що заповнює поле numOfmonth з перевіркою на коректність введеного числа
  void setNumOfMonth() {
    std::cout << "\tEnter NumOfMonth -> ";
    std::cin >> numOfmonth;
    while (numOfmonth < 1) {
    std::cout << "\tNumOfMonth must be > 1" << "\n\t";
    std::cin >> numOfmonth;
    }
    if (age == 18) {
      while (numOfmonth >= 12) {
        std::cout << "\tNumOfMonth must be < 12" << "\n\t";
        std::cin >> numOfmonth;
      }
    }
    else{
      int workingAge = age - 18;
      int maxMonth = workingAge*12;
      while (maxMonth < numOfmonth) {
      std::cout << "\tNumOfMonth must be < "<< maxMonth << "\n\t";
      std::cin >> numOfmonth;
      }
    }
  }
    // метод класу Manager, що заповнює поле daysPerMonth з перевіркою на коректність введеного числа
  void setDaysPerMonth() {
    std::cout << "\tEnter daysPerMonth ->";
    std::cin >> daysPerMonth;
    while (daysPerMonth > 31 || daysPerMonth < 15) {
    std::cout << "\tDays per month must be >=15 and <= 31" << "\n\t";
    std::cin >> daysPerMonth;
    }
  }
};

// класс HiredWorker є нащадком класу Manager
class HiredWorker : public Manager {
private:
  // приватні поля класу HiredWorker
  float payPerHour;
  unsigned int hours;
  std::string service;
public:
  //пустий констуктор класу HiredWorker
  HiredWorker(){}
  //метод класу HiredWorker, що заповнює поле service
  void setService() {
    std::cout << "\tEnter service -> ";
    std::cin.get();
    std::getline (std::cin,service);
  }
  //метод класу HiredWorker, що заповнює поле hours з перевіркою на коректність введеного числа
  void setHours() {
    std::cout << "\tEnter hourse of work -> ";
    std::cin >> hours;
    while (hours<1 || hours>12) {
    std::cout << "\tHours of work must be beetwen 1 and 12" << "\n\t";
    std::cin >>  hours;
    }
  }
  //метод класу HiredWorker, що заповнює поле payPerHour
  void setPayPerHour() {
    std::cout << "\tEnter pay per hour $ -> ";
    std::cin >> payPerHour;
  }
  //метод класу HiredWorker, що виводить в консольне вікно дані про об'єкт класу HiredWorker
  void print(int i) {
    std::cout<<"|" <<std::left<<std:: setw(6)<< i <<"|"<<std:: setw(16)<<  name<<"|"<<
    std::setw(7)<< age<<"|"<< std::setw(24)<< service <<"|"<< std::setw(10)<<
     salary<<"|"<< std::setw(13)<< hours<<"|" <<
    std::setw(12)<< payPerHour<<"|\n";
    }
    // перевизначений метод, що на основі значення змінної payPerHour,hours задає значення для поля salary
  float countSalary(){
        salary = payPerHour*hours;
        return salary;
      }

};

//класс OfficeWorker є нащадком класу Manager
class OfficeWorker : public Manager {
private:
  // приватні поля класу
  std::string position;
  unsigned int projects;
public:
  //пустий конструктор
  OfficeWorker (){}
  //метод класу OfficeWorker, що заповнює поле position
  void setPosition() {
    std::cout << "\tEnter position -> ";
    std::cin.get();
    std::getline (std::cin,position);
  }

  //метод класу OfficeWorker, що заповнює поле projects з перевіркою на коректність введеного числа
  void setProjects() {
    std::cout << "\tNumber of projects -> "; std::cin >> projects;
    while (projects<0 || projects>10) {
      std::cout << "\tMax number of projects = 10. Min = 0" << "\n\t";
      std::cin >> projects;
    }
  }

  //метод класу OfficeWorker, що виводить в консольне вікно дані про об'єкт класу OfficeWorker
  void print(int index) {
    std::cout<<"|" <<std::left<<std:: setw(6)<<index<<"|"<<std:: setw(16)<< name<<"|"<<
      std::setw(7)<<age<<"|"<< std::setw(11)<<rangee <<"|"<< std::setw(16)<<position <<"|"<< std::setw(10)<<
      countSalary() <<"|"<< std::setw(13)<<numOfmonth<<"|" <<
      std::setw(12)<<payForDay<<"|"<< std::setw(15)<<daysPerMonth<<"|"<<std:: setw(8)<< projects <<"|\n";
    }
    // перевизначений метод на основі значення змінної numOfmonth задає значення для полів rangee та payForDay
  void range(){
      if (numOfmonth <24) {
        rangee = "Junior ";
        payForDay = 434.78;
      }
      else if (numOfmonth > 48) {
        rangee = "Senior ";
        payForDay = 1739.13;
      }
      else  {
      rangee = "Middle";
      payForDay = 869.56;
    }
  }
  // перевизначений метод, що на основі значення змінної payForDay,daysPerMonth,projects задає значення для поля salary
  float countSalary(){
      salary = payForDay*daysPerMonth+projects*500;
      return salary;
    }
};
// метод класу Manager, що додає в контейнер workers об'єкт класу OfficeWorker
void Manager :: addOfficeWorker() {
  OfficeWorker w;
  std::cout << "****************************************************************" << '\n';
  std::cout << "ADD OFFICE WORKER" << '\n';
  w.setName();
  w.setAge();
  w.setPosition();
  w.setNumOfMonth();
  w.setDaysPerMonth();
  w.setProjects();
  w.range();
  w.countSalary();
  workers.push_back(w);
  std::cout << "****************************************************************" << '\n';
}
// метод класу Manager, що видаляє з контейнеру workers за індексом об'єкт класу OfficeWorker
void Manager :: deleteOfficeWorker() {
  printOfficeWoorkers();
  if (!workers.empty()){
  int index;
  bool check= false;
std::cout << "\n\nENTER INDEX OF WORKER YOU WANT TO DELETE: "; std::cin >> index;
for (size_t i = 0; i < workers.size(); i++) {
      if (index == i) {
        check = true;
        workers.erase(workers.begin() + i);

        std::cout << "\n\tDELETED" << '\n';
        std::cout << "--------------------------------" << '\n';
        break;
      }
}
  if (!check) {
    std::cout << "\n0 OFFICE WORKERS WITH INDEX " << index << '\n';
      std::cout << "--------------------------------" << '\n';
  }
}
}
// метод класу Manager(реалізація перевизначеної функції), що виводить у консольне вікно інформацію про об'єкт класу Manager
void Manager :: print() {
  std::cout << "****************************************************************" << '\n';
  std::cout << "MANAGER DATA:" << '\n';
  std::cout << "\tName -> " << name << '\n';
  std::cout << "\tAge -> " << age << '\n';
  std::cout << "\tRange -> " << rangee << '\n';
  std::cout << "\tSalary -> " << countSalary() << '\n';
  std::cout << "\tNum Of month -> " << numOfmonth << '\n';
  std::cout << "\tDays per month -> " << daysPerMonth << '\n';
  std::cout << "\tPay for day -> " << payForDay << '\n';
  std::cout << "\tNum of office workers -> " << workers.size() << '\n';
  std::cout << "****************************************************************" << '\n';
}
//метод класу Manager, що в табличному вигляді виводить в консольне вікно послідовність об'єктів класу OfficeWorker контейнеру workers з інформацією про їхні поля
void  Manager:: printOfficeWoorkers() {
  if (!workers.empty()) {
    std::cout << "-----------------------------------------------------------------------------------------------------------------------------\n";
    std::cout << "|Index |"<< "Name\t\t|"<< "Age\t|"<<"Range\t    |"<<"Position\t     |"<<"Salary   $|"<<"Num Of month |"<<"Pay For Day |"<<"Days per month |"<<"Projects|"<< "\n";
    std::cout << "-----------------------------------------------------------------------------------------------------------------------------\n";
    for (size_t i = 0; i < workers.size(); i++) {
     workers[i].print(i);
    }
    std::cout << "-----------------------------------------------------------------------------------------------------------------------------\n";
  }
  else {
    std::cout << "\tLIST IS EMPTY" << '\n';
    std::cout << "--------------------------------" << '\n';
 }
}
// метод класу Manager, що додає в контейнер workers об'єкт класу HiredWorker
void Manager :: addHiredWorker() {
  HiredWorker w;
  std::cout << "****************************************************************" << '\n';
  std::cout << "ADD HIRED WORKER" << '\n';
  w.setName();
  w.setAge();
  w.setService();
  w.setHours();
  w.setPayPerHour();
  w.countSalary();
  hiredWorkers.push_back(w);
  std::cout << "****************************************************************" << '\n';
}
// метод класу Manager, що видаляє з контейнеру workers за індексом об'єкт класу HiredWorker
void Manager :: deleteHiredWorker() {
  printHiredWoorkers();
  if (!hiredWorkers.empty()){
  size_t index;
  bool check= false;
std::cout << "\n\nENTER INDEX OF HIRED WORKER YOU WANT TO DELETE: "; std::cin >> index;
  for (size_t i = 0; i < hiredWorkers.size(); i++) {
        if (index == i) {
          check = true;
          hiredWorkers.erase(hiredWorkers.begin() + i);

          std::cout << "\n\tDELETED" << '\n';
          std::cout << "--------------------------------" << '\n';
          break;
        }
  }
  if (!check) {
    std::cout << "\n0 HIRED WORKERS WITH INDEX " << index << '\n';
      std::cout << "--------------------------------" << '\n';
    }
  }
}
//метод класу Manager, що в табличному вигляді виводить в консольне вікно послідовність об'єктів класу HiredWorker контейнеру workers з інформацією про їхні поля
void  Manager:: printHiredWoorkers() {
  if (!hiredWorkers.empty()) {
    std::cout << "------------------------------------------------------------------------------------------------\n";
    std::cout << "|Index |"<< "Name\t\t|"<< "Age\t|"<<"Service\t\t |"<<"Salary   $|"<<"Num Of hours |"<<"Pay for hour|"<< "\n";
    std::cout << "------------------------------------------------------------------------------------------------\n";
    for (size_t i = 0; i < hiredWorkers.size(); i++) {
     hiredWorkers[i].print(i);
    }
    std::cout << "------------------------------------------------------------------------------------------------\n";
  }
  else {
    std::cout << "\tLIST IS EMPTY" << '\n';
    std::cout << "--------------------------------" << '\n';
 }
}


int main(int argc, char const *argv[]) {
    //змінна, що приймає опцію в функціональному меню
    std::string ch;
    //змінна, що контролює виклик перед початком роботи першої опції меню
    bool ptr = false;
    //об'єкт класу Manager з яким будуть відбуватися подальші зміни
    Manager case1;
  	std :: cout <<"\n\n\n\n\n\n\n\t\t\t\t*****************************************";
  	std :: cout <<"\n\t\t\t\t*\t\t \t\t\t*";
  	std :: cout <<"\n\t\t\t\t*       EMPLOYEES OF THE ORGANIZATION   *";
    	std :: cout <<"\n\t\t\t\t*\t\t \t\t\t*";
  	std :: cout <<"\n\t\t\t\t*****************************************";
    std::cout << "\n\n\n\t\t\t\t Choose 1, to start work!";
    //цикл, що виводить доступні опції програми, поки не буде завернено роботу
    while (1) {
    std::cout << "\n\n\t\t\t\t1. Set Manager Fiels\n";
    std::cout << "\n\t\t\t\t2. Watch manager's data\n";
    std::cout << "\n\t\t\t\t3. Watch office workers data\n";
    std::cout <<"\n\t\t\t\t4. Delete office worker\n";
    std::cout << "\n\t\t\t\t5. Add office worker\n";
    std::cout << "\n\t\t\t\t6. Watch hired workers data\n";
    std::cout <<"\n\t\t\t\t7. Delete hired worker\n";
    std::cout << "\n\t\t\t\t8. Add hired worker\n";
    std::cout << "\n\t\t\t\t9. Exit\n";
    std::cout << "\n\n\t\t\t\tChoose from 1 to 9:";
    //ввід користувацького вибору опції
    std::cin >> ch;
    //перевірка, щоб опція 1 була викликана перед початком роботи
    if ((!ptr && ch != "1") && ch != "9") {
      std::cout << "\n\t\t\t\tNo, choose 1 option to start" << '\n';
    }
    else{
      if (ch == "1") {
        ptr = true;
        //ініціалізація полей даних об'єкту класу Manager case1
        case1.setFields();
      }
      else if (ch == "2") {
        //друк полей даних об'єкту класу Manager case1
        case1.print();
      }
      else if (ch == "3") {
        //друк в табличному вигляді інформації про поля об'єктів класу OfficeWorker контейнеру workers
        case1.printOfficeWoorkers();
      }
      else if (ch == "4") {
        //видалення б'єкту класу OfficeWorker контейнеру workers
        case1.deleteOfficeWorker();
      }
      else if (ch == "5") {
        //додання б'єкту класу OfficeWorker до контейнеру workers
        case1.addOfficeWorker();
      }
      else if (ch == "6") {
        //друк в табличному вигляді інформації про поля об'єктів класу HiredWorker контейнеру hiredWorkers
        case1.printHiredWoorkers();
      }
      else if (ch == "7") {
        //видалення б'єкту класу HiredWorker контейнеру hiredWorkers
        case1.deleteHiredWorker();
      }
      else if (ch == "8") {
        //додання б'єкту класу HiredWorker до контейнеру hiredWorkers
        case1.addHiredWorker();
      }
      else if (ch == "9") {
        //закінчення виконання програми
        return 0;
      }
      else{
        //повідомлення про некоректний ввід опції
        std::cout << "\n\t\t\t\tInvalid entry. Please enter right option" << '\n';
      }
  }
}
//закінчення виконання програми
  return 0;
}
