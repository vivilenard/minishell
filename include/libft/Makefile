# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/15 15:04:49 by vlenard           #+#    #+#              #
#    Updated: 2023/01/30 16:22:49 by vlenard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = 	ft_isdigit.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isprint.c \
		ft_toupper.c ft_tolower.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
		ft_strnstr.c ft_bzero.c ft_memset.c ft_memcpy.c ft_memchr.c ft_memcmp.c \
		ft_memmove.c ft_atoi.c ft_strchr.c ft_strrchr.c ft_calloc.c ft_strdup.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_split.c ft_isXxps.c \
		ft_printf.c ft_takearg.c ft_tohex.c ft_topointer.c ft_utoa.c ft_strcmp.c ft_atodouble.c \
		ft_haystack.c ft_free2d.c ft_strjoinwithoutfree.c ft_iswhitespace.c get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c
SRCBONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
		ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJS = $(SRC:.c=.o)
OBJBONUS = $(SRCBONUS:.c=.o)
NAME = libft.a

all: $(NAME) 
$(NAME) : $(OBJS) 
		ar rcs $(NAME) $(OBJS) 
bonus : $(OBJBONUS) 
		ar rcs $(NAME) $(OBJBONUS)
m: all
		$(CC) libft.a main.c && ./a.out
b: all bonus
		$(CC) libft.a mainbonus.c && ./a.out
n:
		norminette $(SRC) $(SRCBONUS)
clean :
		rm -f $(OBJS) $(OBJBONUS)
fclean : clean
		rm -f $(NAME)
re : fclean
		$(MAKE) all
.PHONY: all, m, b, n, clean, fclean, re