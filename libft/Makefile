NAME	=	libft.a

CC	=	cc
flag	=	-Wall -Wextra -Werror
del	=	rm -f

SRC	= ft_strnstr.c ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
ft_isdigit.c ft_isprint.c ft_memcpy.c ft_memset.c ft_strchr.c\
ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strrchr.c ft_tolower.c\
ft_toupper.c ft_memchr.c ft_memmove.c ft_memcmp.c ft_calloc.c ft_strdup.c ft_substr.c\
ft_strjoin.c ft_putchar_fd.c ft_putnbr_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_strtrim.c\
ft_itoa.c ft_split.c ft_strmapi.c ft_striteri.c

B_SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
ft_lstadd_back.c ft_lstdelone.c ft_lstiter.c

OBJ	=	$(SRC:.c=.o)

B_OBJ = $(B_SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
			ar -rcs $(NAME) $(OBJ)

bonus : $(OBJ) $(B_OBJ)
			ar -rcs $(NAME) $(OBJ) $(B_OBJ)

clean:
			$(del) $(OBJ) $(B_OBJ)

fclean:	clean
			$(del) $(NAME)

re:	fclean $(NAME)

.PHONY: all clean fclean re