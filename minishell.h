/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:37:05 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 15:09:20 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# define RED "\x1b[31m"
# define GRN "\x1B[32m"
# define NRM  "\x1B[0m"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/types.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>

# include <term.h>

# include <sys/stat.h>

int	g_ff_exit;

typedef struct s_env
{
	int				vision;
	char			*name;
	char			*full;
	struct s_env	*next;
}					t_env;

typedef struct s_commands
{
	int					num;
	char				**full_cmd;
	int					fPipeIn;
	int					fPipeOut;
	char				*fRedir;
	char				fPoint;
	char				*stopWord;
	int					redirFlag;
	int					fdOut;
	int					fdIn;
	int					pipe_heredoc[2];
	int					check_heredoc;
	struct s_commands	*next;
}						t_commands;

typedef struct s_mini
{
	int			quot;
	int			num;
	int			args;
	int			count_cmd;
	int			ff_exit;
	int			fakeHD;
	int			lastCMD;
	int			fdH;
	int			**dd;
	char		*cmd;
	char		*declare;
	char		**env;
	char		**env_exp;
	t_commands	*cmdlist;
	t_commands	*always1st;
	t_commands	*tmplist;
	t_env		*envList;
	t_env		*env1st;
	t_env		*tmpEnv;
	pid_t		pid;
}				t_mini;

int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp_f(const char *s1, const char *s2);
int					ctr(long n);
int					preparser(t_mini *mini);
int					checkslash(t_mini *mini, int i, int check);
int					checkstr(t_mini *mini);
int					skip_beforeQ(t_mini *mini, int i);
int					is_valid_uns(t_commands *list, int i);
int					is_valid_exp(t_commands *list, int i);
int					exec_prog(t_commands *list, t_mini *mini, int num);
int					redir_edit(t_commands *line, t_mini *mini);
int					isItBuildin(t_commands *list, int num, t_mini *mini);
int					isHeredoc(t_commands *list, t_mini *mini);
int					redir_edit(t_commands *line, t_mini *mini);
int					isItBuildin(t_commands *list, int num, t_mini *mini);
int					redir_edit(t_commands *line, t_mini *mini);
int					check_redir(t_commands *tmp, t_mini *mini);
int					isItBuildin(t_commands *list, int num, t_mini *mini);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					cmd_exec(t_commands *tmp, t_mini *mini, int s);
int					check_stop(char check);
int					checkslash(t_mini *mini, int i, int check);
int					check_quots(t_mini *mini, int *i);

size_t				ft_strlen(const char *s);

char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strjoin(char const *s1, char const *s2);
char				*strjoin_free(char *s1, char *s2);
char				*ft_itoa(int nb);
char				*ft_strrev(char *str);
char				*ft_dollar(char *cmd, int *i, t_mini *mini);	
char				*ft_onequot(char *cmd, int *i);
char				*ft_slash(char *cmd, int *i);
char				*ft_doublequot(char *cmd, int *i, t_mini *mini, int num);
char				*cmd_cd2(char *cmd);
char				*ft_space(char *cmd, int *i);
char				*ft_tilda(char *cmd, int *i, t_mini *mini);
char				**ft_split(char const *s, char c);
char				*ft_strchr(const char *s, int c);
char				**cmd_remalloc(char **old_mas, int i);
char				*miniparser(char *cmd, int num, t_mini *mini);
char				*ft_question(t_mini *mini, char *cmd, int *i);
char				*dig_edit(char *cmd, int *i);
char				*before_f(t_mini *mini, int *i);
char				*ft_space(char *cmd, int *i);
char				*ft_tilda(char *cmd, int *i, t_mini *mini);

unsigned long long	ft_atoi(const char *str);

void				ft_putstr_fd(char const *s, int fd);
void				parser(t_commands *list, t_mini *mini);
void				preparser2(t_mini *mini);
void				args_num(t_mini *mini);
void				cut_cmd(t_mini *mini);
void				putEnv(t_mini *mini, char **env);
void				export_wop(t_commands *list, int num, t_mini *mini);
void				export_f(t_mini *mini, t_commands *list, int num);
void				unset_f(t_mini *mini, t_commands *list);
void				putEnvList(t_mini *mini, char **env);
void				env_f(t_commands *list, int num, t_mini *mini);
void				pwd_f(t_commands *list, int num, t_mini *mini);
void				echo_f(t_commands *list, int num, t_mini *mini);
void				cmd_cd(t_commands *list, t_mini *mini);
void				export_wop_declare(t_mini *mini, t_commands *list, int num);
void				ft_lstadd_back(t_commands **lst, t_commands *new_lst);
void				ft_lstadd_back1(t_env **lst, t_env *new_lst);
void				std_error(int fd, char *str_err, char *name);
void				pipex_all(t_mini *piped, t_commands *tmp, int s);
void				free_mass_int_pipe(int **mas, int c);
void				free_mass_int_pipe(int **mas, int count_pipe);
void				cmd_not_build(t_mini *mini, t_commands *tmp);
void				pipe_use(t_mini *mini, t_commands *tmp);
void				redirect_f(t_commands *list, t_mini *mini, char *stop);
void				free_mass(char **mas);
void				history_rd(t_mini *mini);
void				history_wr(char *cmd, int fd);
void				sig_listener(int sig);
void				sig_main(void);
void				ft_signal_cmd(void);
void				ft_signal_hd(void);
void				ft_signal_cltr_c_HD(int sig);
void				ft_sig_quit(int sig);
void				ft_signal_cltr_c_2(int sig);
void				exit_f(t_commands *list, t_mini *mini);
void				history_rd(t_mini *mini);
void				history_wr(char *cmd, int fd);
void				edit_first(t_commands *list, int *flag);
void				shlvl_edit(char **env);
void				del_empty(t_commands *list, int *l);
void				init(t_mini *mini, char **env, char **argv, int argc);

t_commands			*ft_lstnew(int content);
t_commands			*ft_lstlast(t_commands *lst);

t_env				*ft_lstnew1(void);
t_env				*ft_lstlast1(t_env *lst);

#endif