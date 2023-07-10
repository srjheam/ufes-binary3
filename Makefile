all:
	gcc -o main main.c binary_tree.c -I. -Wall -Wall -Wextra -Werror -pedantic -ggdb3 -lm

clean