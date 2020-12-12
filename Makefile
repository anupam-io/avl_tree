CC := g++
CCF := -w -Wall -Werror -pthread -g

BUILD = menu compare test result.csv

init_size = 1000
operations = 1000

menu:
	$(CC) $(CCF) menu.c -o menu
	./menu

compare:
	$(CC) $(CCF) compare.cpp -o compare
	./compare $(init_size) $(operations)

test:
	$(CC) $(CCF) compare.cpp -o compare
	$(CC) $(CCF) test.cpp -o test
	./test


clean:
	rm -rf $(BUILD)
