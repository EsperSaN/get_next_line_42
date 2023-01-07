#include "get_next_line.h"

//--------------------------------- [UTILL] ----------------------------------//

char *search_for_the_lie(int fd, char *hermem)
{
  
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
  
  if(fd < 0 || BUFFERSIZE <= 0)
    return(0);
  hermem = search_for_the_lie(fd , hermem); // do the read function until found the \n in the line and return
  // return null if cant malloc or error
  
  if(!hermem)
    return (0);
  
  result = get_next_lie(hermem); //get the thing before \n to it malloc also
  hermem = ready_for_next_lie(hermem); //move to after \n free old and malloc after it

  return(result);
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
    sumstr = str_GNL_MK2(fd);
    
	  printf("final is \n%s", sumstr);
    printf("--------------------------------------\n");
    i--;
  }

}
