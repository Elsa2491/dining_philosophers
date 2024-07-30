NAME = philo

CC = cc -Wall -Wextra -Werror -g3 #-Weverything
MAKEFLAGS += --no-print-directory

GREEN := \e[32m
RESET :=\e[0m

SRCS_PATH = $(shell find srcs -type d)

SRCS = check_params.c print_functions.c free_functions.c init_functions.c \
	thread_functions.c actions.c monitoring.c time_functions.c mutexes_fail.c \
	main.c 

vpath %.c $(foreach dir, $(SRCS_PATH), $(dir):)

OBJS_PATH = objs/

OBJS = $(addprefix $(OBJS_PATH), $(SRCS:%.c=%.o))

all: $(NAME)

$(OBJS_PATH)%.o: %.c
	@mkdir -p $(OBJS_PATH)
	$(CC) -c $< -o $@

$(NAME): $(OBJS)
	@echo "\nCompilation dining philosophers: $(GREEN)success$(RESET)\n"
	$(CC) $(OBJS) -o $(NAME)

clean:
	/bin/rm -rf $(OBJS)
	@echo "\nDining philosophers removed: $(GREEN)success$(RESET)\n"

fclean:	clean
	/bin/rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
