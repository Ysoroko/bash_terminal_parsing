# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/25 11:12:03 by ysoroko           #+#    #+#              #
#    Updated: 2021/03/25 14:54:50 by ysoroko          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			=	main.c 

OBJS		=	$(SRC:.c=.o)

LIBRARIES	=	libft/libft.a

LIBFT		=	cd libft && make

NAME		=	minishell.a

FLAGS		=	-Wall -Wextra -Werror

LINK		=	ar rcs

INCLUDE		=	-I include

EXECUTABLE	=	minishell

all: $(NAME)

$(NAME): $(OBJS)
		@$(LIBFT)
		@$(LINK) $(NAME) $(OBJS)

run: $(NAME)
		@gcc $(FLAGS) $(NAME) -c $(EXECUTABLE) && ./$(EXECUTABLE)

test:	$(NAME)
		@gcc $(FLAGS) $(SRC) $(LIBRARIES) -o $(EXECUTABLE) && ./$(EXECUTABLE)

wtest:	
		@gcc main.c -o $(EXECUTABLE) && ./$(EXECUTABLE)

clean:
		@rm -rf $(OBJS)
		@cd libft && make clean

fclean:	clean
		@rm -rf $(NAME)
		@rm -rf $(EXECUTABLE)
		@cd libft && make fclean
		

re:		aclean all

.PHONY: all clean fclean re run