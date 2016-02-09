#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{

	if(argc != 2){
		printf("Need 1 argument, file name\n");
		return 1;
	}
	char* filepath = argv[1];
	int fd;

	errno = 0;
	fd = open(filepath,O_RDWR);
	if(fd < 0){
		if(errno == ENOENT){
			printf("%s does not exist\n",argv[1]);
		}
		else if(errno == EACCES){
			printf("%s is not accessible\n",argv[1]);
		}
		return 1;
	}
	else{
		printf("\nOpen() Successful\n\n");
		int endOfFile;
		char buffer[BUFSIZ];
		while((endOfFile = read(fd, buffer, BUFSIZ)) > 0){
			write(1,buffer,endOfFile);
		}
		int error = close(fd);
		if(error != 0){
			perror("CLOSE");
		}
		else{
			printf("\nClose() Successful\n");
		}
	}
	return 0;
}