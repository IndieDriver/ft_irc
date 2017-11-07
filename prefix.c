/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:54:02 by amathias          #+#    #+#             */
/*   Updated: 2017/11/07 15:14:16 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

t_user	*parse_user_prefix(t_user *user,
			char *prefix, char *username, char *hostname)
{
	size_t nick_len;
	size_t host_len;

	nick_len = (username - prefix);
	host_len = (prefix + ft_strlen(prefix)) - hostname;
	if (!(user->nick = malloc(sizeof(char) * nick_len + 1)))
		return (NULL);
	if (!(user->hostname = malloc(sizeof(char) * host_len + 1)))
		return (NULL);
	ft_strncpy(user->nick, prefix, nick_len);
	user->nick[nick_len] = '\0';
	ft_strncpy(user->hostname, hostname + 1, host_len - 1);
	user->hostname[host_len - 1] = '\0';
	return (user);
}

t_user	*prefix_to_user(char *prefix)
{
	t_user	*user;
	char	*username;
	char	*hostname;

	username = ft_strchr(prefix, '!');
	hostname = ft_strchr(prefix, '@');
	if (username == NULL || hostname == NULL)
	{
		ft_putendl_fd("Invalid prefix <nick>!<user>@<host>", 2);
		return (NULL);
	}
	user = new_user(NULL, NULL, -1);
	user = parse_user_prefix(user, prefix, username, hostname);
	return (user);
}

char	*user_to_prefix(t_user *user)
{
	char *prefix;

	prefix = malloc(sizeof(char) * 510);
	ft_bzero(prefix, 510);
	ft_strncat(prefix, user->nick, 510 - ft_strlen(prefix));
	ft_strncat(prefix, "!", 510 - ft_strlen(prefix));
	ft_strncat(prefix, user->nick, 510 - ft_strlen(prefix));
	ft_strncat(prefix, "@", 510 - ft_strlen(prefix));
	ft_strncat(prefix, user->hostname, 510 - ft_strlen(prefix));
	return (prefix);
}
