
SRCS	=	ft_memset.c \
			ft_bzero.c \
ft_memcpy.c \
ft_memccpy.c \
ft_memmove.c \
ft_memchr.c \
ft_memcmp.c \
ft_strlen.c \
ft_strlcpy.c \
ft_strlcat.c \
ft_strchr.c \
ft_strrchr.c \
ft_strnstr.c \
ft_strncmp.c \
ft_strcmp.c \
ft_atoi.c \
ft_isalpha.c \
ft_isdigit.c \
ft_isalnum.c \
ft_isascii.c \
ft_isprint.c \
ft_isspace.c \
ft_toupper.c \
ft_tolower.c \
ft_calloc.c \
ft_strdup.c \
ft_substr.c \
ft_strjoin.c \
ft_strjoin_gnl.c \
ft_strtrim.c \
ft_split.c \
ft_itoa.c \
ft_strmapi.c \
ft_putchar.c \
ft_putchar_fd.c \
ft_putstr_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c  \
get_next_line.c \
ft_lstnew.c \
ft_lstlast.c \
ft_lstadd_front.c \
ft_lstadd_back.c \
ft_lstsize.c \
ft_lstiter.c \
ft_lstclear.c \
ft_lstdelone.c \
ft_lstmap.c \
ft_lstsort.c \
ft_strlenmax.c \
ft_freee.c \
is_bit_set.c \
reset_bit.c \
set_bit.c

INCLUDES	= -I.
#Al poner includes e incluirlo en la regla c. o., lo que consigo es evitar tener
#que poner en los ficheros que están en carpetas la ruta, como por ejemplo para
#la inclusión del printf en la carpeta print tener que poner:
# include "../../libft.h" para saber dónde tiene que ir a encontrar la librería,
#con incluir esto en la compilación él ya busca en los directorios sin necesidad
#de darle la ruta

OBJS	= $(SRCS:.c=.o)
#- Aquí simplemente estoy cambiando la extensión.
#- En la variable OBJS se van a almacenar todos los
#archivos de SRC que acaban en .c, y sustituyo la c por una o

OBJS_BONUS	= $(SRCS_BONUS:.c=.o)	#Igual que OBJS pero solo para bonus
#Los bonus los he incluido en objs para que no me dé problemas

NAME 	= libft.a
#Nombre de lo que quiero crear

CC 		= gcc

AR 		= ar

CFLAGS 	= -Wall -Werror -Wextra

RM 		= rm -f

#REGLAS

#s%.o : a%.c
#funcionaría asi??
#The .c.o is an example of what's known an old-fashioned suffix rule. It tells GNU make "here's how to build a .o file from a .c file with the same name." The modern equivalent is a pattern rule which would look the same except to use %.o: %.c in place of .c.o.
.c.o:		#No tiene dependecias
		@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)
			
##-c genera el .o (archivo código  máquina)
##$< variable automática que almacena el nombre del primer requisito previo
#Lo que yo entiendo es que coge cada vez el nombre de un .c y lo
#convierte a .o, uno cada vez
##-o da nombre al output
##<:.c=.o El nombre que me haya dado antes me lo pones en .o

#Esta regla se activa cuando ejecute el nombre que pone en NAME
$(NAME):	$(OBJS)
		$(AR) -r -c $(NAME) $(OBJS)
		$(AR) -s $(NAME)
#¿Qué hace esto?
#Parámetros: ar  flags  archive  file
## ar	crea y mantiene grupos de ficheros combinados en un archivo
#Cuando el archivo se crea, se pueden añadir nuevos ficheros,
#extraer existentes, borrarlos o reemplazarlos
## -c	Suprime el mensaje que aparece cd se crea una librería
## -r	Reemplaza el archivo si ya existe. Si no existe lo añade,
# y si no se especifica dónde, lo añade al final
## -s	Crea un índice o actualiza el existente.
#Es equivalente a ejecutar ranlib


all:		$(NAME)

debug:	CFLAGS += -g3 -fsanitize=address
debug:	re


clean:
		$(RM) $(OBJS)

#En fclean quiero que además de borrar los .o tambien borre la biblioteca .a
fclean:		clean
		$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re debug
