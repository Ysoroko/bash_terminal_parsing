# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/25 11:12:03 by ysoroko           #+#    #+#              #
#    Updated: 2021/03/25 14:06:37 by ysoroko          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			=	main.c 

OBJS		=	$(SRC:.c=.o)

NAME		=	minishell.a

FLAGS		=	-Wall -Wextra -Werror

LINK		=	ar rcs

EXECUTABLE	=	minishell

all: $(NAME)

$(NAME): $(OBJS)
		@$(LINK) $(NAME) $(OBJS)

run: $(NAME)
		@gcc $(FLAGS) $(NAME) -c $(EXECUTABLE) && ./$(EXECUTABLE)

test:
		@gcc $(FLAGS) main.c -o $(EXECUTABLE) && ./$(EXECUTABLE)

wtest:	
		@gcc main.c -o $(EXECUTABLE) && ./$(EXECUTABLE)

clean:
		@rm -rf $(OBJS)

fclean:	clean
		@rm -rf $(NAME) \
		@rm -rf $(EXECUTABLE) \

re:		aclean all

.PHONY: all clean fclean re run