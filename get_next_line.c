#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"





//--------------------------------- [UTILL] ----------------------------------//
char *moveline(char *theline)
{
  int i;
  int j = 0;
  char *temp;
  i = 0;
  while(theline[i])
  {
    if(theline[i] == '\n')
    {
      i++;
      break;
    }
    i++;
  }
  temp = calloc(ft_strlen(&theline[i])+ 1, sizeof(char));
  while(theline[i])
  {
    temp[j] = theline[i];
    i++;
    j++;
  }
  free(theline);
  return (temp);
}

char *finalline(char *theline)
{
  char *result = malloc(100) ; //malloc later
  int i = 0;
  while (theline[i] != '\n')
  {
    result[i] = theline[i];
    i++;
  }
  return(result);
}

int nfind(char *str)
{
  while(*str)
  {
    if(*str == '\n')
      return(0);
    str++;
  }
  return (1);
}

char *get_next_line(int fd)
{
  static char *hermem;
  char *result;
  
  if(fd < 0 || BUFFERSIZE <= 0)
    return(0);
  hermem = SearchForTheLie(fd , hermem); // do the read function until found the \n in the line and return
  // return null if cant malloc or error
  
  if(!hermem)
    return (0);
  
  result = get_next_line(hermem); //get the thing before \n to it malloc also
  hermem = ready_for_next_lie(hermem); //move to after \n free old and malloc after it

  return(result);
}

char *str_GNL_MK2(int fd)
{
  int buffersize = 1;
  char *buff = calloc(buffersize+1 , sizeof(char));
  static char *theline = "//";
  char *result;
  
  while(nfind(theline) && read(fd, buff, buffersize))
  {
    
    theline = ft_strjoin(theline, buff);
    printf("buff is > %s \n the line is > %s \n", buff , theline);
  }

  printf("the lef before final is > %s < \n", theline);
  
  result = finalline(theline);
  theline = moveline(theline);
  
  printf("the lef after move is is > %s < \n", theline);
  
  printf("exit..\n");
  return (result);
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
