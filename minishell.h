/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agungor <agungor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 23:36:06 by osarikay          #+#    #+#             */
/*   Updated: 2024/07/13 18:32:19 by agungor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

#define HISTORY_FILE ".custom_history"

typedef enum e_mode
{
	LINE_FREE,
	PROGRAM_FREE,
}					t_mode;


typedef	enum e_status
{
	NO_QUOTE,
	O_QUOTE,
	D_QUOTE,
}				t_status;

typedef enum e_token
{
	PIPE,
	CMD,
	O_GREATER,
	D_GREATER,
	O_LESS,
	D_LESS,
	SPACE_CMD,
	MY_SPACE,
}					t_token;

typedef struct s_line
{
	char			*line;
	struct s_line	*next;
}				t_line;


typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	//*	stryi temp içinde tutmamız gerekebilir.
	char			*str;
	t_token			type; 				//! | > >> < cmd
	t_status		status; 		//! quote durumunu belirteceğiz. "" '' tırnaksız durumları 

	struct s_cmd	*next;

}					t_cmd;
// ls -la src/
// execve(PATH, ARG, ENV);
// PATH /bin/ls
// char **ARG "ls" "-la" "src/" NULL 
typedef struct s_minishell
{
	t_env			*first_env;
	t_env			*last_env;
	t_cmd			*first_cmd;
	t_cmd			*last_cmd;
	t_line			*first_line;
	t_line			*last_line;
	// char			*cmd; //! kaldırılması muhtemel görünüyor.
	int				*dolar_array;
	char			*line;

	int				start;
	int				end;
	int				length;
	char			*result;

}					t_minishell;

//* Title Section
# define MY_MINI_NAME "🚀🚀🚀 MINISHELL 🚀🚀🚀"

void				*s_malloc(t_minishell *mini, long count, size_t size);
int					ft_error(int error_num);

//* free section
void				null_free(void **alloced_name);
void				loop_free(char **str);
int					general_free(t_minishell *mini, t_mode free_type, int error_num);

//!void				general_exit(t_minishell *mini, int error_num);

//* check section
int					general_check(t_minishell *mini);
int					dolar_check(t_cmd *cmd);
t_token				set_token(int c, int d);


//*	list section
void				env_add(t_minishell *mini, char *name, char *value);
void				line_add(t_minishell *mini);
void				cmd_add(t_minishell *mini, t_status status, t_token type);

//* str section

char 				*start_end_cpy(t_minishell *mini, char *cmd_str, int start, int end);

//* MAIN SECTION
void				env_list(char **env, t_minishell *mini);
void				lexer(t_minishell *mini);
void				expander(t_minishell *mini);
void				edit_list(t_minishell *mini);
void				parser(t_minishell *mini);


void				normalize_quotes(t_minishell *mini);



#endif