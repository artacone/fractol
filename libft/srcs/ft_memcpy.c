/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvertie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 23:44:56 by rvertie           #+#    #+#             */
/*   Updated: 2021/04/17 14:28:04 by rvertie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned long long			*wd;
	const unsigned long long	*ws;
	unsigned char				*cd;
	const unsigned char			*cs;

	wd = dest;
	ws = src;
	while (n >= sizeof(*wd))
	{
		*wd++ = *ws++;
		n -= sizeof(*wd);
	}
	cs = (const unsigned char *)ws;
	cd = (unsigned char *)wd;
	while (n > 0)
	{
		*cd++ = *cs++;
		n--;
	}
	return (dest);
}
