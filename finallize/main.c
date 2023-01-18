#include "get_next_line.h"
#include <stdio.h>
int main()
{
	int fd = open("./test",O_RDONLY);
	printf("enter with %d and fd == %d \n",BUFFER_SIZE,fd);
	while(1)
	{
		char *line = get_next_line(fd);
		if(line == NULL)
			break;
		printf("%s",line);
		free(line);
	}
	printf("end");
}