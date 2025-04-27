#include <iostream>
#include "db.hpp"
#include "employee.hpp"
#include "product.hpp"
#include "location.hpp"


int main() {

    const std::string conninfo = "dbname=store_db user=YOUR_USER password=YOUR_PASSWORD host=YOUR_HOST port=YOUR_PORT";

    try {
        Database db(conninfo);
        db.init_schema();

        Location locations(conninfo);
        Employee employees(conninfo);
        Product products(conninfo);

        bool done = false;
        while (!done) {
            
            std::cout << "\nSelect operation:\n"
                         " 1) Add\n"
                         " 2) List\n"
                         " 0) Exit\n\n"
                         "Choice: ";
            int option;
            std::cin >> option;
            std::cin.ignore();

            if (option == 0) {
                done = true;
                continue;
            }

            
            std::cout << "\nSelect entity:\n"
                         " 1) Location\n"
                         " 2) Employee\n"
                         " 3) Product\n"
                         " 0) Back\n"
                         "Choice: ";
            int entity;
            std::cin >> entity;
            std::cin.ignore();

            if (entity == 0) {
                continue;   
            }

            // ADD OPTION
            if (option == 1) {
                switch (entity) {
                    case 1: {
                        std::string name, address;
                        std::cout << "Location Name: ";
                        std::getline(std::cin, name);
                        std::cout << "Address: ";
                        std::getline(std::cin, address);
                        
                        locations.add(name, address);
                        break;
                    }
                    case 2: { 
                        std::string name;
                        std::string position;
                        double salary;
                        int location;
                        std::cout << "Employee Name: ";
                        std::getline(std::cin, name);
                        std::cout << "Position: ";
                        std::getline(std::cin, position);
                        std::cout << "Salary: ";
                        std::cin >> salary;
                        std::cout << "Location ID: ";
                        std::cin >> location;
                        std::cin.ignore();
                        employees.add(name, position, salary, location);
                        break;
                    }
                    case 3: {  // Add Product
                        std::string name;
                        std::string category;
                        double price;
                        std::cout << "Product Name: ";
                        std::getline(std::cin, name);
                        std::cout << "Price: ";
                        std::cin >> price;
                        std::cin.ignore();
                        std::cout << "Category: ";
                        std::getline(std::cin, category);
                        products.add(name, price, category);
                        break;
                    }
                    default:
                        std::cout << "Unknown entity.\n";
                }
            }
            // LIST OPTION
            else if (option == 2) {
                switch (entity) {
                    case 1:
                        locations.list();
                        break;
                    case 2:
                        employees.list();
                        break;
                    case 3:
                        products.list();
                        break;
                    default:
                        std::cout << "Unknown entity.\n";
                }
            }
            else {
                std::cout << "Unknown operation.\n";
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << "\n";
        return 1;
    }

    std::cout << "Goodbye!\n";

    return 0;
}