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