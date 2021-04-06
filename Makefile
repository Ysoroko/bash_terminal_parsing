# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/25 11:12:03 by ysoroko           #+#    #+#              #
#    Updated: 2021/04/06 16:27:07 by ysoroko          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC					=	main.c \
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

LIBRARIES			=	libft/libft.a \
						minishell.a

OBJS				=	$(SRC:.c=.o)

BOLD_PURPLE			=	\033[1;35m

BOLD_CYAN			=	\033[1;34m

BOLD_YELLOW			=	\033[1;33m

NO_COLOR			=	\033[0m

# Termcap
# Linking command required to be able to use termcap commands
# Without it, some termcap functions are not recognized despite the #include
TERMCAP		=	-ltermcap

LIBFT		=	cd libft && make bonus

NAME		=	minishell.a

FLAGS		=	-Wall -Wextra -Werror

LINK		=	ar rcs

INCLUDE		=	-I include

EXECUTABLE	=	minishell

MINISHELL_COMPILED = echo "\n$(BOLD_PURPLE)Executable $(BOLD_CYAN)\"$(EXECUTABLE)\" $(BOLD_PURPLE)created and ready for use! ✅\n$(NO_COLOR)"

# Prints "Compiling Minishell..." on the output
compiling_minishell:
						@echo "\n$(BOLD_PURPLE)Compiling Minishell... 🐚\n"

CLEANED		=	echo "\n$(BOLD_YELLOW)Clean: $(NO_COLOR)Removed all the \".o\" files 🧼\n"

FCLEANED	=	echo "\n$(BOLD_YELLOW)Fclean: $(NO_COLOR)Removed all the \".a\" files and the \"minishell\" executable 🧽\n"						

.c.o:	
	@${CC} ${CFLAGS} -I include -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): compiling_minishell $(OBJS)
		@$(LIBFT)
		@$(LINK) $(NAME) $(OBJS)
		@gcc $(FLAGS) $(LIBRARIES) $(TERMCAP) -o $(EXECUTABLE)
		@$(MINISHELL_COMPILED)

# Compiles everything with warning flags and runs the executable
run:	$(NAME)
		./$(EXECUTABLE)

# Compiles everything without warning flags and runs the executable
wrun:	$(NAME)
		@gcc $(LIBRARIES) $(TERMCAP) -o $(EXECUTABLE) && ./$(EXECUTABLE)

# Remove all ".o" files
clean:
		@rm -rf $(OBJS)
		@cd libft && make clean
		@$(CLEANED)

# Remove all ".o / .a / minishell executable" files
fclean:	clean
		@rm -rf $(NAME)
		@rm -rf $(EXECUTABLE)
		@cd libft && make fclean
		@$(FCLEANED)

re:		fclean all

.PHONY: all clean fclean re run wrun compiling_minishell .c.o