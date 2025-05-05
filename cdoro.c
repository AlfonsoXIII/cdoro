#include <stdlib.h>
#include <ncurses.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main(int *argc, char **argv) {
	
	system("notify-send 'Pomodoro' 'Concéntrate!'");

	return (EXIT_SUCCESS);
}
