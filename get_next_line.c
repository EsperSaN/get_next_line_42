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
		if (str[i] == '\n')
			break;
		i++;
	}
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
	while (read_counter)
	{
		read_counter = read(fd, buffer, BUFFER_SIZE);
		printf("[ READED ]\n");
		if (read_counter == -1) //adjust it 
		{
			printf("[ READ IS < 0]\n");
			free(st_mem);
			free(buffer);
			return (0);
		}
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
	lenght_of_result = count_untill_newline(st_mem);
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
	printf("---------- COPY ---------\n");
	st_mem = del_oldline_and_move_to_next_line(st_mem);
	printf("---------- MOVE ---------");
	return (output);
}

//--------------------------------- [MAIN] ----------------------------------//
int main()
{	
  int fd = open("./test", O_RDONLY);
  char *sumstr ;
  int i = 10;
  while(i)
  {
    // printf("\n--------------------------------------------------------------------------[%d]---------------------------------------------------------\n", i);
    sumstr = get_next_line(fd);
	printf("///////// final is { %s } ////////////", sumstr);
    // printf("\n-----------------------------------------------------------------------------------------------------------------------------------------\n");
    i--;
    free(sumstr);
  }

}