sqlitetap: sql_tap.o
	ld -shared -o sql_tap.ext sql_tap.o

sql_tap.o: sql_tap.c
	gcc -c -fPIC sql_tap.c

test: sqlitetap
	sqlite3 < test.sql



