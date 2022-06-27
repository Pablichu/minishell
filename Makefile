NAME 			=	minishell

SRCS			=	main.c											\
					termcaps/init_read.c							\
					termcaps/init_read_aux.c						\
					historial/add_historial.c						\
					historial/updown_hist.c							\
					env_vbles/create_env_vble.c						\
					env_vbles/env_to_list.c							\
					env_vbles/get_set_value.c						\
					env_vbles/list_to_env.c							\
					token/token.c									\
					token/quotes_expand/turbosplit.c				\
					token/quotes_expand/words.c						\
					token/quotes_expand/skip_quotes.c				\
					token/quotes_expand/expand.c					\
					token/quotes_expand/aux_dquote.c				\
					token/quotes_expand/aux_dquote_aux_one.c		\
					token/quotes_expand/aux_dquote_aux_two.c		\
					token/quotes_expand/aux_dollar.c				\
					token/quotes_expand/aux_quote.c					\
					token/pipe/parse_pipe.c							\
					token/redir/parse_redir.c						\
					token/redir/get_file.c							\
					token/redir/exist_file.c						\
					token/redir/delimit.c							\
					token/redir/join_command.c						\
					exec/executor.c									\
					exec/one_command.c								\
					exec/pipes.c									\
					builtins/small_builtins.c						\
					builtins/export_buil.c							\
					builtins/unset_buil.c							\
					builtins/echo_buil.c							\
					builtins/echo_dollar.c							\
					builtins/exit_buil.c							\
					errors/pipe_error.c

OBJS			= 	$(SRCS:.c=.o)

NAME_TERMCAP	=	termcap

NAME_LIBFT		=	libft.a
PATH_LIBFT		=	libft
LIBFT			=	$(PATH_LIBFT)/$(NAME_LIBFT)

INCLUDES		=	-I. -I$(PATH_LIBFT)

PATH_LIBS		=	-L$(PATH_LIBFT)
###-L searchdir
###--library-path=searchdir
# Añade la ruta "searchdir" a la lista de rutas que buscará para bibliotecas y
# scripts de control

LIBS			=	-lft -l$(NAME_TERMCAP)
###-l namespec
###--library=namespec
# Añade el archivo u objeto especificado por "namespec" a la lista de ficheros
# a linkar. Si "namespec" es de la forma ':filename', buscará la ruta de la
# biblioteca para un fichero llamado filename, sino buscará la ruta de la
# biblioteca para un fichero llamado 'libnamespec.a' (poniendo el sufijo lib
# antes del nombre pasado)

CC 				=	gcc

RM 				=	rm -f

SANITIZE		=	-fsanitize=address -g3 -O0

CFLAGS 			=	$(INCLUDES) -Wall -Wextra -Werror

LDFLAGS 		=	$(PATH_LIBS) $(LIBS)

#.c.o:
#		@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

$(NAME):	$(LIBFT) $(OBJS)
				$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

$(LIBFT):
				make -C $(PATH_LIBFT)
#-C -->Cambia al directorio PATH_LIBFT antes de leer la orden,
#y es en ese directorio donde ejecuta lo pedido
#Normalmente se usa con invocaciones recursivas de make


all:		$(NAME)

print:
	echo $(PATH_LIBFT)

clean:
				$(RM) $(OBJS)
				@make -C $(PATH_LIBFT) clean

fclean:		clean
				@$(RM) $(NAME)
				@make -C $(PATH_LIBFT) fclean

re:			fclean all

rebug:		fclean debug

debug:		$(NAME)
debug:		CFLAGS += $(SANITIZE)
debug:		LDFLAGS += $(SANITIZE)


DAY		=	$(shell date +'%d/%m/%Y %H:%M')

git:
			git add .
			git commit -m "$(USER) did a push this day: $(DAY)"
			@echo "\033[1;31m\t!!! GIT PUSHING !!!\033[1;34m"
			@git push
			@echo "\033[1;31m\t\t!!! STATUS !!!\033[1;32m"
			@git status
			@echo "\033[0m"

.PHONY:		all clean fclean re debug git