/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweeper <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 12:36:28 by lweeper           #+#    #+#             */
/*   Updated: 2020/11/08 12:36:31 by lweeper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>


size_t		gnl_ft_strlen(const char *s);

char		*gnl_ft_strcpy(char *dst, const char *src);

char		*gnl_ft_strdup(const char *s1);

char		*gnl_ft_strjoin(char *s1, char *s2);

char		*gnl_ft_strchr(const char *s, int c);

int			get_next_line(int fd, char **line);

#endif
