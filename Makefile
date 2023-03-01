NAME = shell
CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCPATH = src/
LIBFTPATH = ./libft
#SRC = 	$(addprefix $(SRCPATH),  main.c utils_prep.c utils.c load_tokens.c content_analyse.c\
		lexer/split_token.c lexer/split_utils1.c lexer/split_utils2.c parser.c utils_parser.c \
		executer/executer.c executer/executer_redirections.c executer/built-in.c expander/expander.c \
		executer/get_path.c)
SRC = $(addprefix $(SRCPATH), executer/executer_dummy2.c executer/executer.c executer/executer_redirections.c executer/built-in.c expander/expander.c utils.c)
OBJ = $(addprefix _bin/,$(notdir $(SRC:.c=.o)))
#OBJ = $(SRC:.c=.o)
DOWNLOADFOLDER = dwnlds
INCFLAG = -Iinclude -Ilibft -I$(DOWNLOADFOLDER)/readline_out/include
LINK = -L$(DOWNLOADFOLDER)/readline_out/lib -lreadline -Llibft -lft
LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(SRC) $(LIBFT) $(DOWNLOADFOLDER)
	$(CC) $(CFLAGS) $(SRC) $(INCFLAG) $(LINK) -o $(NAME)
s: $(NAME)
	./$(NAME)
clean:
	rm -f $(OBJ)
	make clean -C $(LIBFTPATH)
fclean: clean
	rm -f ./$(NAME)
	make fclean -C $(LIBFTPATH)
re: fclean
	$(MAKE) all

$(LIBFT):
	@git submodule init libft
	@git submodule update libft
	@cd libft && make && make clean

$(DOWNLOADFOLDER):
	mkdir -p $(DOWNLOADFOLDER)
	curl -s https://ftp.gnu.org/gnu/readline/readline-8.1.2.tar.gz --output $(DOWNLOADFOLDER)/readline-8.1.2.tar.gz
	tar xfz $(DOWNLOADFOLDER)/readline-8.1.2.tar.gz -C $(DOWNLOADFOLDER)
	cd $(DOWNLOADFOLDER)/readline-8.1.2; ./configure --prefix=$(PWD)/dwnlds/readline_out; cd ../../
	make -C $(DOWNLOADFOLDER)/readline-8.1.2
	make install -C $(DOWNLOADFOLDER)/readline-8.1.2


.PHONY: all, run, clean, fclean, re