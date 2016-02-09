#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	if(argc != 2){
		printf("Need 1 argument, file name\n");
		return 1;
	}
	char* filepath = argv[1];
	int returnval;

	// Check file existence
	returnval = access (filepath, F_OK);
	if(returnval == 0){
		printf("%s exists\n", filepath);					// File exists
	}
	else{
		if(errno == ENOENT){
			printf("%s does not exist\n",filepath);			// Does not exist
		}
		else if(errno == EACCES){
			printf("%s is not accessible\n",filepath);		// Permission denied
		}
		return 0;
	}

	// Check read access
	returnval = access (filepath, R_OK);
	if(returnval == 0){
		printf("%s is read accessible\n", filepath);		// Is readable
	}	
	else{
		if(errno == EACCES){
			printf("%s is not readable\n",filepath);		// Is not readable
		}
		return 0;
	}
	// Check write access
	returnval = access (filepath, W_OK);
	if(returnval == 0){
		printf("%s is write accessible\n", filepath);		// Is writable
	}	
	else{
		if(errno == EACCES){
			printf("%s is not writeable\n",filepath);		// Is not writable
		}
		if(errno == EROFS){
			printf("%s is only readable\n",filepath);		// Is read only
		}
		return 0;
	}
	return 0;
}