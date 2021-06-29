NAME			=	minitalk

CC				=	clang

CFLAGS			=	-Wall -Werror -Wextra -g

SRCS			=	server.c client.c

$(NAME)			:
					@${CC} ${CFLAGS} ${LD_FLAGS} client.c -o client
					@${CC} ${CFLAGS} ${LD_FLAGS} server.c -o server

all				:	${NAME}

clean			:
					@rm -rf ${OBJS}

fclean			:	clean
					@rm -rf server client

re				:	fclean all

.PHONY			:	all clean fclean re
