# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/25 11:12:03 by ysoroko           #+#    #+#              #
#    Updated: 2021/04/02 14:38:02 by ysoroko          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			=	main.c \
				\
				input_parsing/ft_input_parsing.c \
				input_parsing/ft_parsing_utils.c \
				input_parsing/ft_extract_next_command.c \
				\
				execute/ft_execute.c \
				\
				termcaps/ft_termcaps.c \
				\
				utils/signal/ft_signal_handler.c

OBJS		=	$(SRC:.c=.o)

LIBRARIES	=	libft/libft.a

LIBFT		=	cd libft && make bonus

NAME		=	minishell.a

FLAGS		=	-Wall -Wextra -Werror

LINK		=	ar rcs

INCLUDE		=	-I include

EXECUTABLE	=	minishell

all: $(NAME)

$(NAME): $(OBJS)
		@$(LIBFT)
		@$(LINK) $(NAME) $(OBJS)

# Compiles everything with warning flags and runs the executable
run:	$(NAME)
		@gcc $(FLAGS) $(SRC) $(LIBRARIES) -o $(EXECUTABLE) && ./$(EXECUTABLE)

# Compiles everything without warning flags and runs the executable
wrun:	$(NAME)
		@gcc $(SRC) $(LIBRARIES) -o $(EXECUTABLE) && ./$(EXECUTABLE)

# Remove all ".o" files
clean:
		@rm -rf $(OBJS)
		@cd libft && make clean

# Remove all ".o / .a / minishell executable" files
fclean:	clean
		@rm -rf $(NAME)
		@rm -rf $(EXECUTABLE)
		@cd libft && make fclean

re:		fclean all

.PHONY: all clean fclean re run wrun