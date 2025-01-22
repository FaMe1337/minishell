/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:26:16 by toferrei          #+#    #+#             */
/*   Updated: 2025/01/21 11:15:47 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

/*
int change_directory(char **args, int fd, lista *data)
{
	check for directory
		if no directory
			check for HOME variable
				if no HOME
					return error message ---> bash: cd: HOME not set ===> error code 1
				if HOME
					go to HOME and return
		if directory
			check for flag
				if flag == '-'
					check if OLDPWD exists
						yes
							change to OLDPWD and print and return 0 and change PWD to OLDPWD and OLPWD to PWD
						no
							return error message -----> need to find error code
			check for first character
				if  ( not / ) or .
					concatenate current path to beginning of "directory"
					if .

}

*/

int main(int ac, char **av, char **env)
{
	int n = 0;
	while (env[n])
	{
		printf("\n%s\n", env[n]);
		n++;
	}
	return 0;
}