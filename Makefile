#################################################
MINER = miner
#################################################
CC := cc
CFLAGS :=-Wall -Werror -Wextra -g3 -O3
TEMP_FILE = .flag
#################################################
VPATH=src/miner
OBJ_PATH=obj

MINER_SRC=	miner.c			\
			miner_error.c	\
			miner_routine.c	\
			pow.c
MINER_OBJ=$(MINER_SRC:%.c=$(OBJ_PATH)/%.o)
#################################################

YELLOW		=		\033[93;1m
DARK_YELLOW	=		\033[0;33m
GREEN		=		\033[92;1m
DARK_GREEN	=		\033[0;32m
BLUE		=		\033[94;1m
CYAN		=		\033[96;1m
CLEAR		=		\033[0m

#################################################

all: $(MINER)

$(MINER): $(MINER_OBJ)
	@make -s clean_tmpfile
	@echo "\n$(DARK_YELLOW)[ EXE ] Compiling $(YELLOW)$@$(CLEAR)"
	@$(CC) $^ -o $@ -lpthread -lrt
	@echo "\t$(BLUE)Program compiled!. Usage: $(CYAN)./$@$(CLEAR)\n"


$(OBJ_PATH)/%.o: %.c

	@if [ ! -e $(TEMP_FILE) ]; then \
		touch $(TEMP_FILE); \
		echo "$(DARK_GREEN)[ OBJ ] Compiling the objects (\"$(CFLAGS)\")$(CLEAR)"; \
	fi

	@mkdir -p obj/
	@echo "\t$(GREEN)=> Compiling $^$(CLEAR)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean_tmpfile:
	@rm -rf $(TEMP_FILE)

#################################################

clean:
	@rm -rf obj/

fclean: clean
	@rm -rf $(MINER)

re: fclean all

#################################################

ARGS=10 10

r: run
run: all
	@./$(MINER) $(ARGS)

v: valgrind
valgrind: all
	@valgrind --leak-check=full ./$(MINER) $(ARGS)

.PHONY: clean fclean re