/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 00:03:13 by fdidelot          #+#    #+#             */
/*   Updated: 2017/05/27 04:30:27 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		num_width(char *format, t_print *elem)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (ft_isdigit(format[i]))
		i++;
	if (i)
	{
		str = ft_strsub(format, 0, (size_t)i);
		if (format[i] == '$')
		{
			DOLL = ft_atoi(str);
			free(str);
			return (i + 1);
		}
		NUM = ft_atoi(str);
		free(str);
	}
	return (i);
}

int		num_acc(char *format, t_print *elem)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	ACC = 1;
	while (ft_isdigit(format[i]))
		i++;
	if (i)
	{
		str = ft_strsub(format, 0, (size_t)i);
		NACC = ft_atoi(str);
		free(str);
	}
	return (i);
}

int		create_elem(t_print *elem, char *format)
{
	int	i;
	int	j;

	i = 1;
	j = (int)ft_strlen(format);
	while (format[i] && SPEC == '1')
	{
		while (flags(format[i], elem))
			if (++i < j)
				;
		if ((i += num_width(format + i, elem)) > j)
			return (0);
		if (format[i] == '.')
		{
			i++;
			if (format[i] == '*')
				STARAC = 1;
			else if ((i += num_acc(format + i, elem)) > j)
				return (0);
		}
		if ((i += length(format + i, elem)) > j)
			return (0);
		specifier(elem, format[i]);
		i++;
	}
	return (i);
}

t_print		*analyse(char *format, t_print *elem)
{
	t_print *new;
	t_print *start;

	while (*format)
	{
		if (*format == '%')
		{
			if (!elem)
			{
				elem = init();
				start = elem;
				SIZEF = create_elem(elem, format);
			}
			else
			{
				new = init();
				new->size_flags = create_elem(new, format);
				join(elem, new);
			}
			format += SIZEF;
		}
		else
			format++;
	}
	return (start);
}
