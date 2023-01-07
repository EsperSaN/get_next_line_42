#include "get_next_line.h"

//--------------------------------- [UTILL] ----------------------------------//

char *search_for_the_lie(int fd, char *hermem)
{
  char *buffer;
  char *tmp;
  //create the mem if not valid that can use in strjoin function

  if(!hermem)
    hermem = malloc(1 * sizeof(char));
  if(!hermem)
    return(printf("\ni cant malloc----------------------- "));
  buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
  if(buffer)
    buffer[BUFFER_SIZE] = '\0';
  else
    return(0);
  
  while(read(fd, buffer, BUFFER_SIZE)) // just read !!!!! <-------- must be add the \n checker later
  {
    tmp = hermem;
    printf("\nbefore join buffer is %s \nhermem is %s" , buffer,hermem);
    hermem = ft_strjoin(hermem, buffer);
    free(tmp);
  }
  free(buffer);

  return(hermem);
  
}

char *get_next_lie(char *hermem)
{

}

char *ready_for_next_lie(char *hermem)
{

}

char *get_next_line(int fd)
{
  static char *hermem;
  char *result;
  
  printf("start with BUFFERSIZE > %d \n", BUFFER_SIZE);
  if(fd < 0 || BUFFER_SIZE <= 0)
    return(0);
  hermem = search_for_the_lie(fd , hermem); // do the read function until found the \n in the line and return
  // return null if cant malloc or error
  printf("\nhemem is '%s'\n exit...", hermem);
  if(!hermem)
    return (0);
  
  //result = get_next_lie(hermem); //get the thing before \n to it malloc also
  //hermem = ready_for_next_lie(hermem); //move to after \n free old and malloc after it
  return(hermem);
}


//--------------------------------- [MAIN] ----------------------------------//
int main()
{	
  int fd = open("./test", O_RDONLY);
  char *sumstr ;
  int i = 10;
  while(i)
  {
    printf("--------------------[%d]-----------------\n", i);
    sumstr = get_next_line(fd);
    
	  printf("final is \n%s", sumstr);
    printf("--------------------------------------\n");
    i--;
  }

}
