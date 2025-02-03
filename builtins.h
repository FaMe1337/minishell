/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toferrei <toferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:27:30 by toferrei          #+#    #+#             */
/*   Updated: 2025/02/03 18:05:17 by toferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H

# define BUILTINS_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include "Libft/libft.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	bool			exported;

}	t_env;

typedef struct s_data
{
	size_t			exit_code;
	t_env			**env;
	char			*pwd;
	char			*home;
}	t_data;



#endif
