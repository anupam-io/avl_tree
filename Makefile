CC := g++
CCF := -w -Wall -Werror -pthread -g
PCC := python3

BUILD = menu compare test

init_size = 10000
operations = 10000

targets = test plot clean
all: $(targets)

menu:
	$(CC) $(CCF) menu.c -o menu
	./menu

compare:
	$(CC) $(CCF) compare.cpp -o compare
	./compare $(init_size) $(operations)

test:
	rm -rf result.csv
	$(CC) $(CCF) compare.cpp -o compare
	$(CC) $(CCF) test.cpp -o test
	./test

plot:
	mkdir plots -p
	$(PCC) graph.py

clean:
	rm -rf $(BUILD)
	rm -rf result.csv