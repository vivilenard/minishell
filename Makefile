NAME = shell
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRCPATH = src/
LIBFTPATH = libft/
SRC = 	$(addprefix $(SRCPATH),  main.c prep.c utils.c lexer.c)
OBJ = $(SRC:.c=.o) 
DOWNLOADFOLDER = dwnlds
LIBFT = libft/libft.a
INCFLAG = -I$(DOWNLOADFOLDER)/readline_out/include
INCLUDE = -L$(DOWNLOADFOLDER)/readline_out/lib -lreadline

all: $(NAME)
$(NAME): $(OBJ) $(DOWNLOADFOLDER) $(LIBFT)
	$(CC) $(OBJ) $(INCFLAG) $(INCLUDE) -o $(NAME)
run: $(NAME)
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