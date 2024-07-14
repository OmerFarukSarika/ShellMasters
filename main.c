/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agungor <agungor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 23:21:42 by osarikay          #+#    #+#             */
/*   Updated: 2024/07/13 14:44:34 by agungor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <signal.h>

void load_history() {
    char* home = getenv("HOME");
    if (!home) return;
    char history_path[1024];
    snprintf(history_path, sizeof(history_path), "%s/%s", home, HISTORY_FILE);
    read_history(history_path);
}

void save_history() {
    char* home = getenv("HOME");
    if (!home) return;
    char history_path[1024];
    snprintf(history_path, sizeof(history_path), "%s/%s", home, HISTORY_FILE);
    write_history(history_path);
}

/* int get_history(t_minishell *mini, int fd)
{
	fd = open(".commands.txt", O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (write(1, "dosya acılamadı\n", 18)); //! free ye gidecek
	write(fd, mini->line, ft_strlen(mini->line));
	write(fd, "\n", 1);
	close(fd);
	return (0);
} */

//!UNUTMA sileceğiz harici olarak sonradan ekleyebiliriz
void	ponzi_function(t_minishell *mini)
{
	t_env *temp;
	
	temp = NULL;
	if (mini->line[0] == 'e' && mini->line[1] == 'n' && mini->line[2] == 'v')
	{	
		temp = mini->first_env;
		while (temp->next)
		{
			printf("%s=%s\n", temp->name, temp->value);
			temp = temp->next;
		}
		printf("%s=%s\n", temp->name, temp->name);
	}
}

int	main(int ac, char **av, char **env)
{
	t_minishell	*mini;
	t_cmd		*temp;

	(void)av;
	if (ac != 1)
		ft_error(-1);
	mini = s_malloc(NULL, 1, sizeof(t_minishell));								//* program kapanırsa freelenmeli | line için freelenmemeli
	env_list(env, mini);														//* program kapanırsa freelenmeli | line için freelenmemeli
	load_history();
	while (1)
	{
		mini->line = readline(MY_MINI_NAME);									//* bir sonraki line'a geçerken veya program kapatılırken freelenmeli
		line_add(mini);
//!		printf("-->%p\n", mini->line);
//!		ponzi_function(mini);
		if (mini->line && *(mini->line))					//? iki if koşulu birleştirilebilir ? freeleme sisteminde sonra yazılacaktır.
		{
        	add_history(mini->line);
        	save_history();  // Her giriş sonrası geçmişi kaydet
			//!printf("esat");
    	}
		if ((!mini->line || !mini->line[0])/*  && (mini->line[0] != ' ' && mini->line[1] == '\0') */)
		{
			general_free(mini, PROGRAM_FREE, 0);
			printf("arif");
			exit(0); //! line boş gelirse leaks check yapıyorum. ---> exit atmaktaki amacım henüz sinyal yakalama ile çıkışları yapmamış oluşumuzdan dolayı.
		}
		else
		{
			if (general_check(mini))			//! hatalı bir token girişlerinde basit seviyede bir check işlemi yapıyoruz. böyle bir şeyin yaşanması durumunda "line seviyesinde" free yapıp yeni bir line bekliyoruz.
				continue;
			lexer(mini);
			expander(mini);													// ! dolar check diye bir fonksyion yazılıp eğerki dolar işareti bizim linemizde var ise ona göre expander fonksiyonuna gidebilecek ayrıetten bir fonskyion yazılabilme ihtimalini göz önünde bulundurmayı öneriyoruz.
			//parser(mini);
			temp = mini->first_cmd;
			write(1, "\n\n\n*******BEFORE*******\n\n\n", 26);
			while (temp)
			{
				printf("str 	= %s\n", temp->str);
				printf("type	= %u\n", temp->type);
				printf("status	= %u\n", temp->status);
				printf("\n");
				temp = temp->next;
			}
			edit_list(mini);
			temp = mini->first_cmd;
			write(1, "\n\n\n*******AFTER*******\n\n\n", 26);
			while (temp)
			{
				printf("str 	= %s\n", temp->str);
				printf("type	= %u\n", temp->type);
				printf("status	= %u\n", temp->status);
				printf("\n");
				temp = temp->next;
			}
		}
		general_free(mini, LINE_FREE, 0);
		add_history(mini->line);
	}
/* 
	! ONERI
	char	**arg;
	// cat -e src
	arg = mmalloc (sizeof(char *) * 4);
	arg[0] = "cat";
	arg[1] = NULL;
	PATH = "/bin/ls" 
	execve(PATH, arg, NULL); */
}
