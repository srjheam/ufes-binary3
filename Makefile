all:
	gcc -o main main.c binary_tree.c black_magic.c deque.c person.c -I. -Wall -Wall -Wextra -Werror -pedantic -ggdb3 -lm

clean:
	rm main
