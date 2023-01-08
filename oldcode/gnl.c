#include "get_next_line.h"

//--------------------------------- [UTILL] ----------------------------------//

int wait_i_have_a_reason(char *hermem)
{
  printf("\n -----------CHECK------------\n > %s <\n", hermem);
  
  while(*hermem)
  {
    if(*hermem == '\n')
    {
  
      printf("\n ------------------- WAIT WAIT LISTEN TO ME I HAVE REASON ----------------");
  
      return(0);
    }
    hermem++;
  }
  
  printf("-----------------PASS!!!!-----------\n");
  
  return(1);
}

int	did_n_word(char *hermem)
{
  int i;

  i = 0;
  if(!hermem)
    return(0);
  while(*hermem)
  {
    if(*hermem == '\n')
      break;
    i++;
    hermem++;
  }
  return(i);
}

char *search_for_the_lie(int fd, char *hermem)
{
  char *buffer;
  char *tmp;
  int	i_remember_that;
  
  if(!hermem) //create the mem if not valid that can use in strjoin function
    hermem = malloc(1 * sizeof(char));
  
  if(!hermem)
    return(printf("\ni cant malloc----------------------- "));
  
  buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
  
  if(!buffer)
    return(0);
  
  buffer[BUFFER_SIZE] = '\0';
  
  i_remember_that = 1; // 1 for start in read

  // || have to move condition bolow there due the nominent
  // the old is 'while(wait_i_have_a_reason(hermem) && read(fd, buffer, BUFFER_SIZE))'
  while(i_remember_that) // have to write the case that if read -1 at the first or neither the read 0 mean end
  {
    i_remember_that = read(fd ,buffer, BUFFER_SIZE); // if this value > 0 mean it can read
    
    if(i_remember_that <= 0)
    {
      printf("\n ////////////////////////// finish or error /////////////////////// \n");
      free(hermem); // is it ness??
      free(buffer);
      return(0);
    }

    tmp = hermem;
    
    printf("\nbefore join the 'buffer' is > %s < \nhermem is > %s <" , buffer,hermem);
    
    hermem = ft_strjoin(hermem, buffer);
    free(tmp);

    if(!wait_i_have_a_reason(hermem))
      break;
  }
  
  free(buffer);

  return(hermem);
  
}


char *get_next_lie(char *hermem) // use for get the line to the result to output 
{
  char *to_return;
  int	how_long;
  int	i;

  i = 0;

 if(!hermem)
    return(0);

  how_long = did_n_word(hermem);

  printf("\n -------- I malloc {%d} + 1 PAPA ---------- \n" , how_long);

  to_return = malloc(how_long + 1); // this thing have to free by user

  to_return[how_long] = '\0';

  while(how_long && hermem[i]) // to prevent the 1 size str that only contain \0 
  {
    to_return[i] = hermem[i];
    i++;
    how_long--;
  }

  return (to_return);
}

char *ready_for_next_lie(char *hermem)
{
  int i;
  int	j;
  char	*tmp;

  i = 0;
  j = 0;
  if(!hermem)
    return(0);

  while(hermem[i])
  {
    if(hermem[i] == '\n')
    {
      i++;
      break;
    }
    i++;
  }
  tmp = malloc(ft_strlen(&hermem[i]) + 1);
  tmp[ft_strlen(&hermem[i])] = '\0';

  while(hermem[i])
  {
    tmp[j] = hermem[i];
    i++;
    j++;
  }
  free(hermem);
  return (tmp);
}

char *get_next_line(int fd) //------for the malloc there is still leak when read is not -1 or 0 so that mean when call the function that read donst end it will leake at static // the return is user free

{
  static char *hermem;
  char *result;
  
  printf("start with BUFFERSIZE > %d \n", BUFFER_SIZE);
  
  if(fd < 0 || BUFFER_SIZE <= 0)
    return(0);
  hermem = search_for_the_lie(fd , hermem); // do the read function until found the \n in the line and return
  
  
  printf("\nhermem is '%s'\n exit...", hermem);
  
  if(!hermem) // return null if cant malloc or error
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
    printf("\n--------------------------------------------------------------------------[%d]---------------------------------------------------------\n", i);
    sumstr = get_next_line(fd);
    
	  printf("final is \n { %s }", sumstr);
    printf("\n-----------------------------------------------------------------------------------------------------------------------------------------\n");
    i--;
    free(sumstr);
  }

}
