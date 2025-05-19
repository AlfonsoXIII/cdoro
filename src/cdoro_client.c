#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#include <cdoro_definitions.h>

void invokeHelp(void) {
	printf("\n\t-> cdoro help\n");
	printf("\t\tProvides all detailed help for the available client commands.\n");

	printf("\n\t-> cdoro open\n");
	printf("\t\tSummons a cdoro daemon, as long as it hasn't been prevoiusly opened.\n");

	printf("\n\t-> cdoro close\n");
	printf("\t\tCloses the current cdoro daemon.\n");

	printf("\n\t-> cdoro start\n");
	printf("\t\tStarts a 25min pomodoro counter.\n");

	printf("\n\t-> cdoro break\n");
	printf("\t\tTriggers a break timer.\n");

}

void invokeDaemon(void) {
	struct stat st;

	if (stat(FIFO_PATH, &st) == 0) {
        	if (S_ISFIFO(st.st_mode)) {
            		printf("Existe una FIFO\n");
        	} else {
        		printf("El archivo existe, pero no es una FIFO.\n");
        	}
    	} else {
        	perror("stat");
        	printf("No existe el archivo o no se puede acceder.\n");
	}

	if (daemon(0, 0) == -1) {
		perror("[ERROR] A problem ocurred while trying to summon the daemon:/ Aborting!\n");
		exit(EXIT_FAILURE);
    	}
	printf("[SUCCESS] The daemon was summoned successfully!\n");
	system("./cdoro_daemon &");
} 

int pushCommand(int command, int arg) {
	int fd, response;

    	fd = open(FIFO_PATH, O_WRONLY|O_RDONLY);
    	if (fd == -1) {
        	exit(CDORO_DAEMON_DISCONNECTED);
    	}

    	if (write(fd, &command, sizeof(int)) != sizeof(int)) {
        	close(fd);
        	exit(CDORO_DAEMON_DISCONNECTED);
    	}

	if (read(fd, &response, sizeof(int)) != sizeof(int)) {
		close(fd);
		exit(CDORO_DAEMON_DISCONNECTED);
	}

    	printf("Valor recibido: %d\n", response);
    	close(fd);
    	return (response);
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
			printf("[ERROR] The cdoro daemon isn't running yet!\n");
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
		error_handler = pushCommand(POMODORO_BREAK, CDORO_DAEMON_NULL_ARG);
		if (error_handler == CDORO_DAEMON_DISCONNECTED) {
			printf("[ERROR] The cdoro daemon isn't running yet!\n");
			return (EXIT_FAILURE);
		} else if (error_handler == CDORO_DAEMON_ALREADY_START) {
			printf("[ERROR] A pomodoro timer is alraedy running! Invoke a {stop} command before attempting to start a new one c:\n");
			return (EXIT_FAILURE);
		} else if (error_handler == CDORO_DAEMON_ALREADY_BREAK) {
			printf("[ERROR] A break timer is already running! Invoke a {stop} command before attempting to resume your focusing journey c:\n");
		} else {
			printf("[SUCCESS] Stop! Break time!\n");
			return (EXIT_SUCCESS);
		}


	} else if (strcmp(argv[1], "close") == 0) {
		error_handler = pushCommand(POMODORO_STOP, CDORO_DAEMON_NULL_ARG);
		if (error_handler == CDORO_DAEMON_DISCONNECTED) {
			printf("[ERROR] The cdoro daemon isn't running yet!\n");
			return (EXIT_FAILURE);
		} else {
			printf("[SUCCESS] The daemon was closed successfully!\n");
			return (EXIT_SUCCESS);
		}

	} else if (strcmp(argv[1], "help") == 0) {
		invokeHelp();

	} else {
		printf("[ERROR] Your command was not recognized:/ Check the syntax, or invoke [help] for further insight!\n");
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}
