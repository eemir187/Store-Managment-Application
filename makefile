build:
	g++ db.cpp location.cpp employee.cpp product.cpp main.cpp -lpq -o store_app

run: build
	./store_app

test:
	g++ db.cpp location.cpp employee.cpp product.cpp test_store.cpp -lpq -o test_runner
	./test_runner

clean:
	rm -f store_app test_runner
