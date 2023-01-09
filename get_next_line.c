/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 19:58:37 by pruenrua          #+#    #+#             */
/*   Updated: 2023/01/08 23:46:16 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	newline_checker(char	*str)
{
	while (*str)
	{
		if (*str == '\n')
			return(0);
		str++; 
	}
	return (1);
}

size_t	count_untill_newline(char	*str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		i++;
		printf("\n %c count %d", str[i],i);
		if (str[i] == '\n')
			break;
		
	}
	i++; //>> return COUNT not INDEX
	return (i);
}

char	*read_until_newline(int	fd, char	*st_mem)
{
	char	*buffer;
	char	*tmp;
	int	read_counter;

	if (!st_mem)
	{
		st_mem = (char *)malloc(1 * sizeof(char));
		st_mem[0] = '\0';
		printf("[ MALLOC 1st]\n");
	}
	if (!st_mem)
		return (0);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	printf("[ MALLOC BUFFER]\n");
	if (!buffer)
		return (0);
	buffer[BUFFER_SIZE] = '\0';
	read_counter = 1;
	while (read_counter > 0)
	{
		read_counter = read(fd, buffer, BUFFER_SIZE);
		printf("[ READED with read_count = %d ]\n", read_counter);
		if(read_counter == 0) // if fin reading just stop -> free (buff) -> return
			break;
		if (read_counter == -1) //adjust it 
		{
			printf("[ READ IS == %d]\n" , read_counter);
			free(st_mem);
			free(buffer);
			return (0);
		}
		buffer[read_counter] = '\0'; // add this to prevent the read that read can read 1 and replace just 1 position and lefe te rest from recent loop 
		/*  BEFORE FIX
		[ READED with read_count = 1 ] <-- this mean read can read just 1 char and put it in first index [0] ;																																									| strjoin should cut here											
		[ join [0123456789012345678901234567890123456789] with [0789] ] <-- but the join will read until \0 and join so we must protech the buffer just what it can read now so we want just [0] so we protech that by add \0 to the next index after read byte so that would be 0'\0'789
		[ JoinNED with result > [01234567890123456789012345678901234567890789] ]
		AFTER FIX 
		[ READED with read_count = 1 ]
		[ join [0123456789012345678901234567890123456789] with [0] ] these change
		[ JoinNED with result > [01234567890123456789012345678901234567890] ]	
		*/
		tmp = st_mem;
		printf("[ join [%s] with [%s] ]\n", st_mem , buffer);
		st_mem = ft_strjoin(st_mem, buffer);
		printf("[ JoinNED with result > [%s] ]\n", st_mem);
		free(tmp);
		printf("[ free BUFF]\n");
		printf("[ TO CHECKER]\n");
		if (!newline_checker(st_mem))
		{
			printf("[ found 'n']\n");
			break;
		}
	}
	free(buffer);
	return (st_mem);
}

char	*copy_line_to_output(char	*st_mem)
{
	char	*result;
	size_t	lenght_of_result;
	size_t	i;

	i = 0;
	if (!st_mem)
		return (0);
	printf("\n[copy-line-to-output]\n");
	lenght_of_result = count_untill_newline(st_mem); // <-- fix to output with \n
	printf("lenght is [%d] stlen is %d\n", lenght_of_result,ft_strlen(st_mem));
	result = (char *)malloc((lenght_of_result + 1) * sizeof(char));
	result[lenght_of_result] = '\0';
	while (lenght_of_result && st_mem[i])
	{
		result[i] = st_mem[i];
		i++;
		lenght_of_result--;
	}
	return (result);
}

char	*del_oldline_and_move_to_next_line(char *st_mem)
{
	size_t	i;
	size_t	j;
	char	*result;

	i = 0;
	j = 0;
	if (!st_mem)
		return (0);
	while (st_mem[i] && st_mem[i] != '\n')
	{
		// if (st_mem[i] == '\n')
		// {
		// 	i++;
		// 	break;
		// }
		i++;
	}
	if (!st_mem[i++])
	{
		free(st_mem);
		return (0);	
	}
	result = (char *)malloc(ft_strlen(&st_mem[i++]) + 1);
	result[ft_strlen(&st_mem[i])] = '\0';
	while(st_mem[i])
	{
		result[j] = st_mem[i];
		i++;
		j++;
	}
	free(st_mem);
	return (result);
}

char	*get_next_line(int	fd)
{
	static char	*st_mem;
	char	*output;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	st_mem = read_until_newline(fd, st_mem);
	printf("---------- READ FIN WITH ---------\n [%s] \n ----------^ in the st_mem ------------\n", st_mem);
	if (!st_mem)
		return (0);
	output = copy_line_to_output(st_mem);
	printf("---------- COPY OUTPUT IS [%s] ---------\n", output);
	st_mem = del_oldline_and_move_to_next_line(st_mem);
	printf("---------- MOVE ---------\n");
	return (output);
}

//--------------------------------- [MAIN] ----------------------------------//
int main()
{	
  int fd = open("./test", O_RDONLY);
  char *sumstr ;
  int i = 1;
  while(i)
  {

    printf("\n--------------------------------------------------------------------------[%d]---------------------------------------------------------\n", i);
    sumstr = get_next_line(fd);
	printf("///////// final is { %s } ////////////", sumstr);
    // printf("\n-----------------------------------------------------------------------------------------------------------------------------------------\n");
    i--;
    free(sumstr);
  }

}