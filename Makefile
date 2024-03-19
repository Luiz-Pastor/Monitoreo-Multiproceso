#################################################
MINER = miner
#################################################
CC := cc
CFLAGS :=-Wall -Werror -Wextra -g3 -O3
#################################################
VPATH=src/miner
OBJ_PATH=obj

MINER_SRC=	miner.c			\
			miner_error.c
MINER_OBJ=$(MINER_SRC:%.c=$(OBJ_PATH)/%.o)

#################################################

all: $(MINER)

$(MINER): $(MINER_OBJ)
	@$(CC) $^ -o $@

$(OBJ_PATH)/%.o: %.c
	@mkdir -p obj/
	@$(CC) $(CFLAGS) -c $< -o $@

#################################################

clean:
	@rm -rf obj/

fclean: clean
	@rm -rf $(MINER)

re: fclean all

.PHONY: clean fclean re