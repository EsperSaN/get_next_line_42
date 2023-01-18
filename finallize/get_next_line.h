/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 19:59:26 by pruenrua          #+#    #+#             */
/*   Updated: 2023/01/18 15:31:59 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

size_t	newline_checker(char	*str);
size_t	count_untill_newline(char	*str);
char	*read_until_newline(int	fd, char	*st_mem);
char	*copy_line_to_output(char	*st_mem);
char	*del_oldline_and_move_to_next_line(char *st_mem);
char	*get_next_line(int	fd);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);

# endif
