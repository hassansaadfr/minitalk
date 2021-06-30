NAME			=	minitalk
SERVER			=	server
CLIENT			=	client

CC				=	clang

CFLAGS			=	-Wall -Werror -Wextra -g

HEADERS			=	-I includes

SRCS_CLIENT		=	client.c
SRCS_SERVER		=	server.c

CLIENT_OBJS		=	${addprefix srcs/client_scrs/,${SRCS_CLIENT:.c=.o}}
SERVER_OBJS		=	${addprefix srcs/server_srcs/,${SRCS_SERVER:.c=.o}}

$(NAME)			:	$(CLIENT) $(SERVER)

$(CLIENT)		:	${CLIENT_OBJS}
					${CC} ${CFLAGS} ${CLIENT_OBJS} -Iincludes -o $(CLIENT)

$(SERVER)		:	${SERVER_OBJS}
					${CC} ${CFLAGS} ${SERVER_OBJS} -Iincludes -o $(SERVER)

.c.o			:
					${CC} ${CFLAGS} ${HEADERS} -c $< -o ${<:.c=.o}

all				:	${NAME}

clean			:
					@rm -rf ${CLIENT_OBJS} ${SERVER_OBJS}

fclean			:	clean
					@rm -rf server client

re				:	fclean all

.PHONY			:	all clean fclean re
