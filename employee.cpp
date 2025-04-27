#include "employee.hpp"
#include <iostream>

void Employee::add(const std::string& name, const std::string& position, double salary, int location_id) {
    std::string sql = "INSERT INTO employees (name, position, salary, location_id) VALUES ('" +
        name + "', '" + position + "', " + std::to_string(salary) + ", " + std::to_string(location_id) + ");";
    execute(sql);
    std::cout << "Employee added.\n";
}

void Employee::list() {
    PGresult* res = query("SELECT id, name, position, salary, location_id FROM employees;");
    int rows = PQntuples(res);
    for (int i = 0; i < rows; ++i) {
        std::cout
            << "ID: "       << PQgetvalue(res, i, 0)
            << ", Name: "   << PQgetvalue(res, i, 1)
            << ", Pos: "    << PQgetvalue(res, i, 2)
            << ", Salary: " << PQgetvalue(res, i, 3)
            << ", LocID: "  << PQgetvalue(res, i, 4)
            << "\n";
    }
    PQclear(res);
}
