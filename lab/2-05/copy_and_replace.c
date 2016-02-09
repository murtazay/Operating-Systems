#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	if(argc != 3){
		printf("Need 2 arguments(source,destination)\n");
		return 1;
	}
	char* source 	  = argv[1];
	char* destination = argv[2];
	int fdSource, fdDestination;
	errno = 0;

	fdSource = open(source, O_RDONLY);
	if(fdSource < 0){
		if(errno == ENOENT){
			printf("%s does not exist\n","source.txt");
		}
		else if(errno == EACCES){
			printf("%s is not accessible\n","source.txt");
		}
		return 1;
	}
	else{
		int accessTest = access(destination, F_OK);
		if(accessTest == 0){
			unlink(destination);
		}
		fdDestination = open(destination, O_CREAT | O_WRONLY, S_IWUSR|S_IRUSR);
		if(fdDestination < 0){
			if(errno == EACCES){
				printf("%s is not accessible\n",destination);
			}
			return 1;
		}
		else{
				char buffer[100];
				int endOfFile;
				while((endOfFile = read(fdSource,buffer,100)) > 0){
					int i = 0;
					while(i < endOfFile){
						if(buffer[i] == '1'){
							buffer[i] = 'A';
						}
						i++;
					}
					write(fdDestination, buffer, endOfFile);
					write(fdDestination, "XYZ" , 3);
				}
			int returnval = close(fdSource);
			if(returnval != 0){
				perror("CLOSE(SOURCE)");
			}
			returnval = close(fdDestination);
			if(returnval != 0){
				perror("CLOSE(DESTINATION)");
			}
		}
	}
	return 0;
}