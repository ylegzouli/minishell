/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 18:21:52 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/06/01 16:05:47 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

# define BUFFER_SIZE	1

int				get_next_line(int fd, char **line);
int				ft_check_error(int fd, char **str, char **line);
int				ft_newline(char *str);
char			*ft_readline(int fd, char *str);
void			ft_buffer_cpy(char **str, int size_line);

size_t			ft_strlen(char const *str);
char			*ft_subnull(void);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);

#endif
