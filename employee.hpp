#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include "db.hpp"
#include <string>

class Employee : public Database {
public:
    Employee(const std::string& conninfo) : Database(conninfo) {}

    void add(const std::string& name, const std::string& position, double salary, int location_id);

    void list();

};

#endif // EMPLOYEE_HPP
