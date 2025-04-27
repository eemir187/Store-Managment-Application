#define CATCH_CONFIG_MAIN
#include "test_framework/catch.hpp"

#include "db.hpp"
#include "location.hpp"
#include "employee.hpp"
#include "product.hpp"
#include <postgresql/libpq-fe.h>
#include <string>

static const std::string TEST_CONN = "dbname=store_db user=YOUR_USER password=YOUR_PASSWORD host=YOUR_HOST port=YOUR_PORT";

// Helper to flush tables
void clear_tables(Database& db) {
    db.execute("DELETE FROM product_locations;");
    db.execute("DELETE FROM products;");
    db.execute("DELETE FROM employees;");
    db.execute("DELETE FROM locations;");
}

TEST_CASE("Database connection succeeds", "[Database]") {
    REQUIRE_NOTHROW(Database(TEST_CONN));
}

TEST_CASE("Location add & list", "[Location]") {
    Database db(TEST_CONN);
    clear_tables(db);
    Location loc(TEST_CONN);
    loc.add("TestStore", "123 Test St");

    PGresult* r = db.query("SELECT name, address FROM locations;");
    REQUIRE(PQntuples(r) == 1);
    REQUIRE(std::string(PQgetvalue(r,0,0)) == "TestStore");
    REQUIRE(std::string(PQgetvalue(r,0,1)) == "123 Test St");
    PQclear(r);
}

TEST_CASE("Employee add & list", "[Employee]") {
    Database db(TEST_CONN);
    clear_tables(db);

    // First insert a location for FK
    db.execute("INSERT INTO locations (name,address) VALUES ('L','A');");
    PGresult* lr = db.query("SELECT id FROM locations;");
    int loc_id = std::stoi(PQgetvalue(lr,0,0));
    PQclear(lr);

    Employee emp(TEST_CONN);
    emp.add("Alice","Cashier",1500.0, loc_id);

    PGresult* r = db.query("SELECT name, position, salary, location_id FROM employees;");
    REQUIRE(PQntuples(r) == 1);
    REQUIRE(std::string(PQgetvalue(r,0,0)) == "Alice");
    REQUIRE(std::string(PQgetvalue(r,0,1)) == "Cashier");
    REQUIRE(std::stod(PQgetvalue(r,0,2)) == Approx(1500.0));
    REQUIRE(std::stoi(PQgetvalue(r,0,3)) == loc_id);
    PQclear(r);
}

TEST_CASE("Product add & list", "[Product]") {
    Database db(TEST_CONN);
    clear_tables(db);

    Product prod(TEST_CONN);
    prod.add("Widget", 9.99, "Gadgets");

    PGresult* r = db.query("SELECT name, price, category FROM products;");
    REQUIRE(PQntuples(r) == 1);
    REQUIRE(std::string(PQgetvalue(r,0,0)) == "Widget");
    REQUIRE(std::stod(PQgetvalue(r,0,1)) == Approx(9.99));
    REQUIRE(std::string(PQgetvalue(r,0,2)) == "Gadgets");
    PQclear(r);
}
