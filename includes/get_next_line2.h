/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 15:40:31 by rkirszba          #+#    #+#             */
/*   Updated: 2019/07/24 15:41:19 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE2_H
# define GET_NEXT_LINE2_H

# include <sys/types.h>
# include <sys/uio.h>
# include "libft.h"
# define BUFF_SIZE 4096

int	get_next_line2(const int fd, char **line, char **str);

#endif
