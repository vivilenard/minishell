NAME = shell
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRCPATH = src/
SRC = $(addprefix $(SRCPATH),  practice.c)
OBJ = $(SRC:.c=.o)
DOWNLOADFOLDER = dwnlds
INCFLAG = -I$(DOWNLOADFOLDER)/readline_out/include
INCLUDE = -L$(DOWNLOADFOLDER)/readline_out/lib -lreadline

all: $(NAME)
$(NAME): $(OBJ) $(DOWNLOADFOLDER)
	$(CC) $(OBJ) $(INCFLAG) $(INCLUDE) -o shell
run: $(NAME)
	./$(NAME)
$(DOWNLOADFOLDER):
	mkdir -p $(DOWNLOADFOLDER)
	curl -s https://ftp.gnu.org/gnu/readline/readline-8.1.2.tar.gz --output $(DOWNLOADFOLDER)/readline-8.1.2.tar.gz
	tar xfz $(DOWNLOADFOLDER)/readline-8.1.2.tar.gz -C $(DOWNLOADFOLDER)
	cd $(DOWNLOADFOLDER)/readline-8.1.2; ./configure --prefix=$(PWD)/dwnlds/readline_out; cd ../../
	make -C $(DOWNLOADFOLDER)/readline-8.1.2
	make install -C $(DOWNLOADFOLDER)/readline-8.1.2

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f ./$(NAME)
re: fclean
	$(MAKE) all

.PHONY: all, run, clean, fclean, re