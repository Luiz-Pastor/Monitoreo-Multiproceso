#################################################
MINER = miner
MONITOR = monitor
#################################################
CC := cc
CFLAGS :=-Wall -Werror -Wextra -g3 -O3
TEMP_FILE = .flag
#################################################
VPATH=src/common_utils:src/miner:src/monitor
OBJ_PATH=obj

COMMON_SRC=	msg_utils.c				\
			shared_memory_utils.c	\
			pow.c
COMMON_OBJ=$(COMMON_SRC:%.c=$(OBJ_PATH)/%.o)

MINER_SRC=	miner.c			\
			miner_error.c	\
			miner_routine.c
MINER_OBJ=$(MINER_SRC:%.c=$(OBJ_PATH)/%.o)

MONITOR_SRC=	monitor.c			\
				monitor_error.c		\
				monitor_routine.c	\
				checker_routine.c
MONITOR_OBJ=$(MONITOR_SRC:%.c=$(OBJ_PATH)/%.o)
#################################################

YELLOW		=		\033[93;1m
DARK_YELLOW	=		\033[0;33m
GREEN		=		\033[92;1m
DARK_GREEN	=		\033[0;32m
BLUE		=		\033[94;1m
CYAN		=		\033[96;1m
CLEAR		=		\033[0m

#################################################

all: $(MINER) $(MONITOR)

$(MINER): $(MINER_OBJ) $(COMMON_OBJ)
	@make -s clean_tmpfile
	@echo "\n$(DARK_YELLOW)[ EXE ] Compiling $(YELLOW)$@$(CLEAR)"
	@$(CC) $^ -o $@ -lpthread -lrt
	@echo "\t$(BLUE)Program compiled!. Usage: $(CYAN)./$@ <ROUNDS> <LAG>$(CLEAR)\n"

$(MONITOR): $(MONITOR_OBJ) $(COMMON_OBJ)
	@make -s clean_tmpfile
	@echo "\n$(DARK_YELLOW)[ EXE ] Compiling $(YELLOW)$@$(CLEAR)"
	@$(CC) $^ -o $@ -lpthread -lrt
	@echo "\t$(BLUE)Program compiled!. Usage: $(CYAN)./$@ <LAG>$(CLEAR)\n"


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
	@rm -rf /dev/mqueue/miner
	@rm -rf /dev/shm/monitor
	@rm -rf /dev/shm/sem_memory

fclean: clean
	@rm -rf $(MINER) $(MONITOR)

re: fclean all

#################################################

MINER_ARGS=1 10
m1: miner_run
miner_run: 
	@./$(MINER) $(MINER_ARGS)

MONITOR_ARGS=10
m2: monitor_run
monitor_run:
	@valgrind --leak-check=full ./$(MONITOR) $(MONITOR_ARGS)

.PHONY: clean fclean re