#include "db.hpp"
#include <iostream>

Database::Database(const std::string& conninfo) {
    conn_ = PQconnectdb(conninfo.c_str());

    if (PQstatus(conn_) != CONNECTION_OK) {
        std::string err = PQerrorMessage(conn_);
        PQfinish(conn_);
        throw std::runtime_error("Connection failed: " + err);
    }
}

Database::~Database() {
    if (conn_) {
        PQfinish(conn_);
    }
}

void Database::execute(const std::string& sql) {
    PGresult* res = PQexec(conn_, sql.c_str());
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::string err = PQerrorMessage(conn_);
        PQclear(res);
        throw std::runtime_error("SQL error: " + err);
    }
    PQclear(res); 
}

PGresult* Database::query(const std::string& sql) {
    PGresult* res = PQexec(conn_, sql.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::string err = PQerrorMessage(conn_);
        PQclear(res);
        throw std::runtime_error("SQL error: " + err);
    }
    return res;
}

void Database::init_schema() {
    execute("DROP TABLE IF EXISTS product_locations;");
    execute("DROP TABLE IF EXISTS products;");
    execute("DROP TABLE IF EXISTS employees;");
    execute("DROP TABLE IF EXISTS locations;");

    execute(R"(
      CREATE TABLE locations (
        id SERIAL PRIMARY KEY,
        name TEXT NOT NULL,
        address TEXT NOT NULL
      );
    )");

    execute(R"(
      CREATE TABLE employees (
        id SERIAL PRIMARY KEY,
        name TEXT NOT NULL,
        position TEXT NOT NULL,
        salary NUMERIC NOT NULL,
        location_id INTEGER REFERENCES locations(id)
      );
    )");

    execute(R"(
      CREATE TABLE products (
        id SERIAL PRIMARY KEY,
        name TEXT NOT NULL,
        price NUMERIC NOT NULL,
        category TEXT NOT NULL
      );
    )");

    execute(R"(
      CREATE TABLE product_locations (
        product_id INTEGER REFERENCES products(id),
        location_id INTEGER REFERENCES locations(id),
        PRIMARY KEY (product_id, location_id)
      );
    )");
}