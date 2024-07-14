/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agungor <agungor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:13:02 by agungor           #+#    #+#             */
/*   Updated: 2024/07/13 18:02:44 by agungor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




/* 
* 			OPTIONAL
	? Tilde Expansion (Tilde Genişletmesi):

	? ~ karakteri kullanıcının ev dizinini ifade eder.
	? Örneğin, ~ işareti /home/kullaniciadi gibi kullanıcının ev dizinine genişletilir.
	? ~username ise belirtilen kullanıcının ev dizinine genişletilir
*/

#include "../minishell.h"
#include "../libft/libft.h"

static	void	dolar_array_creating(t_minishell *mini, t_cmd *cmd)
{
	int	i;
	int j;
	int	size;

	i = -1;
	size = 0;
	while (cmd->str[++i])
		if (cmd->str[i] == '$')
			size++;
	mini->dolar_array = s_malloc(mini, size + 1, sizeof(int));
	i = -1;
	j = -1;
	while (cmd->str[++i])
		if (cmd->str[i] == '$')
			mini->dolar_array[++j] = i;
	mini->dolar_array[++j] = i;
}

int	dolar_check(t_cmd *cmd)
{
	int		i;

	i = -1;
	while(cmd->str[++i])
		if (cmd->str[i] == '$')
			return (1);
	return (0);
}

/*
	*	heredoc durumunda bash'in nasıl bir reaksiyon verdiğine dair bir örnektir.
	
	!	bash-3.2$ << $USER echo kullanici adi = $USER
	!	> $USER
	!	kullanici adi = agungor
*/

/*	
	*	YANLIŞ OLABİLİR DOĞRU DA OLABİLİR
	*	Aşağıdaki örneklereden anlaşıldığı üzere $USER ifadesinin D_QUOTE durumuda env içerisinde olması yeterlidir. $USER direkt genişletilmelidir.
	*	Eğer NO_QUOTE ise $işaretinde sonra env içerisinde name bulunamazsa '\n' atmamız gerekmektedir.
	
	!	bash-3.2$ echo $USERasada
	!	bash-3.2$ echo $USERR
	!	bash-3.2$ echo "arif esat gungor$USER"
	!	arif esat gungoragungor
	!	bash-3.2$ echo "arif esat gungoraa****|$USER"
	!	arif esat gungoraa****|agungor
*/

// void	parser(t_minishell *mini)
// {
// 	t_cmd	*cmd;
// 	t_env	*env;
	
// 	write(1, "|**** PARSER START ****|\n", 25);
// 	cmd = mini->first_cmd;
// 	while (cmd)
// 	{
// 		if (cmd->type == D_LESS && cmd->next)				//* << $USER $HOME durumunda birincinin genişletilmemesi ikincinin ise genişletilmesi gerekiyor.
// 		{
// 			//!printf("cmd_str  = %s\n", cmd->str);
// 			if (cmd->next->next)							// * line içerisinde 3 ve 3' ten fazla bir " cmd " var kontrol ederek geçmeliyiz yoksa segmation_fault hatası ile karşılaşabiliriz.
// 				cmd = cmd->next->next;
// 			continue;
// 		}
// 		if (cmd->status == NO_QUOTE && cmd->str[0] == '$')
// 		{
// 			write(1, "ACMAYA GIRDI\n", 14);
// 			env = mini->first_env;
// 			while (env->next)
// 			{
// 				//!write(1, "|cc|\n", 6);
// 				/* printf("env_name = %s\n", env->name);
// 				printf("cmd_str  = %s\n", &cmd->str[1]) */;
// 				if (!ft_strncmp(env->name, &cmd->str[1], ft_strlen(env->name)))
// 				{
// 					null_free((void **)&(cmd->str));
// 					cmd->str = ft_strdup(env->value); //! bellekte aynı adresi gösterirlerse "PROGRAM_FREE" içerisinde double free hatası almaktayız. Harici olarak null_free kullansam bile sorun yaşıyorum çünkü bu valueye char ** üzerinde erişiliyor ft_splitten dönüyor
// 					write(1, "|dd|\n", 6);
// 				}
// 				env = env->next;
// 			}
// 		}
// 		//!write(1, "|**** PARSER END ****|\n", 23);
// 		cmd = cmd->next;
// 	}
// }


//*			echo "$USERaSUUUUG  $HOME"
//*			  /Users/agungor 
/* 
bash-3.2$ echo "$USERaSUUUUG++$HOME"
++/Users/agungor
 */
//*		yukarıdaki girdi için oluşan çıktı mantığında bir parser işlemi kurgulamaktayım.
//! plan geleni genişlettikten sonra | stringin kalan bölümünün genişletmeye ihtiyacı var mı yok mu ona bakmalıyız tekrar böyle bir durum olursa strjoin ile cmd->str yi güncellemeliyiz ___ free sistemine dikkat etmemiz gerekmektedir.
static int	expand_env_variables(t_minishell *mini, t_env *env)
{
	char	*temp_str;

	temp_str = mini->result;
	mini->result = ft_strjoin(mini->result, env->value);
	null_free((void *)&temp_str);
	return (mini->length);
}

char *start_end_cpy(t_minishell *mini, char *cmd_str, int start, int end)
{
	int		i;
	char	*result;
	
	i = 0;
	result = s_malloc(mini, 1, end - start + 2);
	while (start <= end)
		result[i++] = cmd_str[start++];
	result[i] = '\0';
	return(result);
}

static void	find_env_variables(t_minishell *mini, t_cmd *cmd)
{
	bool	flag;
	int		i;
	int		end;
	int		start;
	t_env	*env;
	char	*temp_str;
	char	*selected_str;
	
	i = 0;
	start = 0;
	end = -1;
	if (cmd->str[0] == '$')
		start = 1;
	while(cmd->str[++end])
	{
		printf("start = %d | end = %d\n", start, end);
		if (cmd->str[end] != '$' && cmd->str[end + 1] == '$') //! $$ durumunda patlamaması için düşündük.
		{
			printf("MERKEZ IF'E GIRDI\n");
			temp_str = mini->result;
			selected_str = start_end_cpy(mini, cmd->str, start, end);
			printf("selected_str = %s\n", selected_str);
			mini->result = ft_strjoin(mini->result, selected_str);
			null_free((void *)&selected_str);
			null_free((void *)&temp_str);
			start = end + 2;											//*	normal şartlarda start = end + 1 olması gerekirdi fakat burada $ ibaresinide atlamamız gerektiğini fark ettik. Bundan dolayı +2 fazlası yaptık.
		}
		else if (cmd->str[end] == '$')
		{
			flag = true;
			printf("MERKEZ ELSE IF'E GIRDI\n");
			env = mini->first_env;	//! str içerisindeki while içinde eşitlenmeli
			while(env->next)
			{
				mini->length = ft_strlen(env->name);										
				if (!ft_strncmp(env->name, &cmd->str[start], mini->length))
				{
					printf("START = %d\n", start);
					if (!ft_isalnum(cmd->str[start + mini->length]) /* || cmd->str[start + mini->length] == '$' || !cmd->str[start + mini->length] */)
					{
						printf("girmedi\n");
						end += expand_env_variables(mini, env);  //! $USERa$HOME
						flag = false;
						start = end + 1;
						if (cmd->str[end + 1] != '\0' && cmd->str[end + 2] != '\0' && cmd->str[end + 1] == '$')
							start = end + 2;
					}
					break;
				}
				env = env->next;
			}
			if (flag)
			{
				printf("flag start = %d | flag end = %d\n", start, end);
				printf("atlama yerine girdi\n");
				end = mini->dolar_array[++i];
				start = end + 1;
/* 					while (cmd->str[end] && cmd->str[end] != '$')
						end++; */
				end--;
				printf("flag start = %d | flag end = %d\n", start, end);
			}
		}
		else if (cmd->str[end + 1] == '\0' && cmd->str[end + 1] != '$')
		{
			temp_str = mini->result;
			selected_str = start_end_cpy(mini, cmd->str, start, end);
			printf("else if = %s\n", selected_str);
			mini->result = ft_strjoin(mini->result, selected_str);
			null_free((void *)&selected_str);
			null_free((void *)&temp_str);
			start = end + 1;
		}
	}
	null_free((void **)&(cmd->str));	//* tüm işlemlerimiz bittikten sonra cmd yi freelemeliyiz
}


/* void	expander(t_minishell *mini)
{
	t_cmd	*cmd;
		
	write(1, "|**** EXPANDER START ****|\n", 28);
	cmd = mini->first_cmd;
	while (cmd)
	{
		if (cmd->type == D_LESS && cmd->next)				// << $USER $HOME durumunda birincinin genişletilmemesi ikincinin ise genişletilmesi gerekiyor. //scmd->next silinebilir
		{
			//!printf("cmd_str  = %s\n", cmd->str);
			if (cmd->next->next)							//  line içerisinde 3 ve 3' ten fazla bir " cmd " var kontrol ederek geçmeliyiz yoksa segmation_fault hatası ile karşılaşabiliriz.
				cmd = cmd->next->next;
			continue;
		}
		if (cmd->status != O_QUOTE && dolar_check(mini))
		{
			dolar_array_creating(mini, cmd);
			mini->result = ft_strdup("");
			find_env_variables(mini, cmd);
			cmd->str = ft_strdup(mini->result);
			null_free((void *)&mini->result);
			null_free((void *)&mini->dolar_array);
		}
		else; //! O_QUOTE durumunda burada işlem yapacağız
			
		//!write(1, "|**** PARSER END ****|\n", 23);
		cmd = cmd->next;
	}
} */


void	expander(t_minishell *mini)
{
	t_cmd	*cmd;
		
	write(1, "|**** EXPANDER START ****|\n", 28);
	cmd = mini->first_cmd;
	while (cmd)
	{
		mini->length = 0;
		/* if (cmd->type == D_LESS && cmd->next)				// << $USER $HOME durumunda birincinin genişletilmemesi ikincinin ise genişletilmesi gerekiyor. //scmd->next silinebilir
		{
			//!printf("cmd_str  = %s\n", cmd->str);
			if (cmd->next->next)							//  line içerisinde 3 ve 3' ten fazla bir " cmd " var kontrol ederek geçmeliyiz yoksa segmation_fault hatası ile karşılaşabiliriz.
				cmd = cmd->next->next;
			continue;
		} */
		if (cmd->status != O_QUOTE && dolar_check(cmd))
		{
			dolar_array_creating(mini, cmd);
			//!printf("find_env\n");
			mini->result = ft_strdup("");
			find_env_variables(mini, cmd);
			cmd->str = ft_strdup(mini->result);
			null_free((void *)&mini->result);
			null_free((void *)&mini->dolar_array);
		}
		else; //! O_QUOTE durumunda burada işlem yapacağız
			
		//!write(1, "|**** PARSER END ****|\n", 23);
		cmd = cmd->next;
	}
}
