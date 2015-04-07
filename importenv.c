#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

const int MAX_ENV_SIZE = 1024*1024;
const int MAX_ENV_VARS = 1024;

int main (int argc, char* argv[]) {
    if (argc < 3) {
	printf("Syntax: %s <environ-file> <cmd> [args...]\n", argv[0]);
	exit(1);
    }
    int fd = open(argv[1], O_RDONLY);
    if (-1 == fd) {
	perror("open");
	exit(1);
    }
    char env[MAX_ENV_SIZE+2];
    int env_size = read(fd, env, MAX_ENV_SIZE);
    if (-1 == env_size) {
	perror("read");
	exit(1);
    }
    if (MAX_ENV_SIZE == env_size) {
	printf("WARNING: environment bigger than %d bytes. It has been truncated.\n", MAX_ENV_SIZE);
    }
    char* envp[MAX_ENV_VARS];
    int i;
    char *c;
    for (i=0, c=env; i<MAX_ENV_VARS && *c; i++, c+=strlen(c)+1) {
	envp[i] = c;
    }
    if (i == MAX_ENV_VARS) {
	printf("WARNING: more than %d vars. Some have been clobbered.\n", MAX_ENV_VARS);
    }
    if (-1 == execvpe(argv[2], argv+2, envp)) {
	perror("exec");
	exit(1);
    }
    // Unreachable
    exit(42);
}
