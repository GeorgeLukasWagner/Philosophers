# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwagner <gwagner@student.42wolfsburg.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 14:35:45 by gwagner           #+#    #+#              #
#    Updated: 2024/11/11 12:30:42 by gwagner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC_DIR			=	srcs/

SRC				=	$(SRC_DIR)philosophers.c $(SRC_DIR)utils.c $(SRC_DIR)init.c $(SRC_DIR)routine.c $(SRC_DIR)message.c \
					$(SRC_DIR)error.c $(SRC_DIR)routine2.c

OBJS			=	$(SRC:.c=.o)

CC				=	@cc -Wall -Werror -Wextra -pthread #-fsanitize=thread
RM				=	@rm -f

NAME			=	philo

%.o:			%.c
					$(CC) -c $< -o $@

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(OBJS) -o $(NAME)

clean:
					$(RM) $(OBJS)

fclean:			clean
					$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re