NAME	:= philo
CFLAGS	:= -g -Wextra -Wall -Werror

INCS	:= -I./incs
SRCS	:= $(shell find ./srcs -name "*.c")
OBJS	:= ${SRCS:.c=.o}

CC      := gcc
AR      := ar
ARFLAGS := rcs

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) && printf "Linking: $(NAME)\n"

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
