VALGRINDOUT = valgrind-out.txt

FLAGS = -Wall -Wextra -Wno-unused-result -Wno-unused-parameter -pedantic -ggdb3 -g

all:
	gcc $(FLAGS) -o main main.c binary_tree.c black_magic.c deque.c person.c -I. -lm

clean:
	rm -f main libed.a libsearch.a $(LIBSEARCH_DEPS) $(LIBED_DEPS) jheam_ross_2022100890.zip $(VALGRINDOUT)

zip: clean
	zip -r jheam_ross_2022100890.zip . \
		-x dados/\* \
		   scripts/\* \
		   *.zip \
		   *.txt

valgrind: all
	rm -f $(VALGRINDOUT)

	valgrind --leak-check=full \
			 --show-leak-kinds=all \
			 --track-origins=yes \
			 --verbose \
			 --log-file=$(VALGRINDOUT) \
			 ./main

	@echo "Head to $(VALGRINDOUT)"