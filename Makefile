SRCS	= 	main.c line_edit/ft_doublequot.c env_funcs/export_w_o_params.c  \
			line_edit/ft_dollar.c line_edit/ft_slash.c  					\
			line_edit/ft_onequot.c line_edit/parser.c   					\
			line_edit/args_count.c line_edit/parser3.c utils/init.c 		\
			line_edit/check_str.c line_edit/check_quots.c					\
			env_funcs/export.c env_funcs/unset.c line_edit/ft_dollar2.c 	\
			env_funcs/putEnvList.c pipesRedirs/pipex_12.c utils/error.c  	\
			env_funcs/env.c	env_funcs/isValid.c	functions/cmd_cd.c			\
			functions/pwd_f.c functions/echo_f.c pipesRedirs/pipe.c 		\
			pipesRedirs/remalloc_cmd.c pipesRedirs/redirect.c 				\
			utils/exec_prog.c functions/exit.c utils/signal.c				\
			env_funcs/add_declare.c functions/pwdForCD.c line_edit/parser2.c\
			libft_functions/ft_lib1.c libft_functions/ft_lib2.c 			\
			libft_functions/ft_lib3.c libft_functions/ft_lib4.c				\
			libft_functions/ft_lst.c libft_functions/ft_lst1.c 				\
			libft_functions/ft_split.c pipesRedirs/checkRedir.c 			\
			pipesRedirs/isHeredoc.c utils/isItBuildin.c line_edit/cmd_cut.c	\
			pipesRedirs/redirect_edit.c pipesRedirs/mini_parser.c 			\
			utils/history.c utils/signal2.c utils/exec_prog2.c				\
			
OBJS	= $(SRCS:.c=.o)

HEADER	= minishell.h

NAME	= minishell

FLAGS	= -Wall -Wextra -Werror

RM	= rm -f

all:		$(NAME)

$(NAME):	$(OBJS) $(HEADER)
			gcc $(OBJS) $(FLAGS) -o $(NAME) -lreadline -L/Users/${USER}/.brew/opt/readline/lib -I/Users/${USER}/.brew/opt/readline/include

%.o	:	%.c $(HEADER)
			gcc $(FLAGS) -c -I/Users/${USER}/.brew/opt/readline/include $< -o $@

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}
			${RM} .history

re:			fclean all

.PHONY:		all clean fclean re
