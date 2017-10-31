/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:54:02 by amathias          #+#    #+#             */
/*   Updated: 2017/10/31 17:17:25 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

t_user	*parse_user_prefix(t_user *user,
			char *prefix, char *username, char *hostname)
{
	if (!(user->nick = malloc(sizeof(char) * (username - prefix) + 1)))
		return (NULL);
	if (!(user->user = malloc(sizeof(char) * (hostname - username) + 1)))
		return (NULL);
	if (!(user->hostname = malloc(sizeof(char) *
			((prefix + ft_strlen(prefix)) - hostname) + 1)))
		return (NULL);
	ft_strncpy(user->nick, prefix, (username - prefix));
	ft_strncpy(user->user, username + 1,
			((hostname - 1) - username));
	ft_strncpy(user->hostname, hostname + 1,
			(((prefix + ft_strlen(prefix) - 1)) - hostname));
	return (user);
}


t_user	*prefix_to_user(char *prefix)
{
	t_user	*user;
	char	*username;
	char	*hostname;

	username = ft_strstr(prefix, "!");
	hostname = ft_strstr(prefix, "@");
	if (username == NULL || hostname == NULL)
	{
		// <nick>!<user>@<host>
		ft_putendl_fd("Invalid prefix <nick>!<user>@<host>", 2);
		return (NULL);
	}
	user = new_user(NULL, NULL, NULL, -1);
	user = parse_user_prefix(user, prefix, username, hostname);
	return (user);
}

char	*user_to_prefix(t_user *user)
{
	char *prefix;

	prefix = malloc(sizeof(char) * 510);
	ft_bzero(prefix, 510);
	ft_strncat(prefix, user->nick, 510);
	ft_strncat(prefix, "!", 510);
	ft_strncat(prefix, user->user, 510);
	ft_strncat(prefix, "@", 510);
	ft_strncat(prefix, user->hostname, 510);
	return (prefix);
}
