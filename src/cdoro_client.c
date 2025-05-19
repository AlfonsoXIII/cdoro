#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#include <cdoro_definitions.h>

void invokeHelp(void) {

}

void invokeDaemon(void) {

} 

int pushCommand(int command, int arg) {

}

int main(int argc, char **argv) {
	int error_handler;

	if (argc < 2) {
		printf("[ERROR] The syntax corresponds to,\n\n\t-> cdoro {command} [args]\n");
		return (EXIT_FAILURE);
	}

	if (strcmp(argv[1], "open") == 0) {
		invokeDaemon();

	} else if (strcmp(argv[1], "start") == 0) {
		error_handler = pushCommand(POMODORO_START, CDORO_DAEMON_NULL_ARG);
		if (error_handler == CDORO_DAEMON_DISCONNECTED) {
			printf("[ERROR] The Daemon isn't running yet!\n");
			return (EXIT_FAILURE);
		} else if (error_handler == CDORO_DAEMON_ALREADY_START) {
			printf("[ERROR] A pomodoro timer is alraedy running! Invoke a {stop} command before attempting to start a new one c:\n");
			return (EXIT_FAILURE);
		} else if (error_handler == CDORO_DAEMON_ALREADY_BREAK) {
			printf("[ERROR] A break timer is already running! Invoke a {stop} command before attempting to resume your focusing journey c:\n");
		} else {
			printf("[SUCCESS] A new timer has started! Good luck!\n");
			return (EXIT_SUCCESS);
		}

	} else if (strcmp(argv[1], "break") == 0) {

	} else if (strcmp(argv[1], "close") == 0) {

	} else {
		printf("[ERROR] Your command was not recognized:/ Check the syntax, or invoke [help] for further insight!\n");
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}
