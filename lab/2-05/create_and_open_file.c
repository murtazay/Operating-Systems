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
	fd = open(filepath, O_CREAT | O_RDWR, S_IRWXU);

	if(fd < 0){
		printf("\nopen() failed with error [%s]\n", strerror(errno));
		perror("OPEN");
		return 0;
	}
	else{
		printf("\nopen() Successful\n%s created and is open for reading and writing\n", filepath);
		int returnval;
		returnval = close(fd);
		if(returnval == 0){
			printf("\nclose() Successful\n%s closed\n", filepath);
		}
		else{
			printf("\nclose() failed with error[%s]\n", strerror(errno));
			perror("CLOSE");
			return 1;
		}
	}
	return 0;
}