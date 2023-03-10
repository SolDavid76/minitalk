SRCS_DIR	= src/

SRC_SRV		= server.c utils.c

SRC_CLT		= client.c utils.c

SRCS		= $(addprefix $(SRCS_DIR), $(SRC))

OBJS_DIR	= obj/

OBJ_SRV		= ${SRC_SRV:.c=.o}

OBJ_CLT		= ${SRC_CLT:.c=.o}

OBJS_SRV	= $(addprefix $(OBJS_DIR), $(OBJ_SRV))

OBJS_CLT	= $(addprefix $(OBJS_DIR), $(OBJ_CLT))

NAME		= minitalk

NAME_SRV	= server

NAME_CLT	= client

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

INCS		= -I ./include/

TIMEOUT		= -D TIMEOUT=1

all:		${OBJS_DIR} ${NAME}

${NAME}:	${NAME_SRV} ${NAME_CLT}

${NAME_SRV}	: ${OBJS_SRV}
			${CC} ${CFLAGS} ${OBJS_SRV} -o ${NAME_SRV}

${NAME_CLT}	: ${OBJS_CLT}
			${CC} ${CFLAGS} ${OBJS_CLT} ${TIMEOUT} -o ${NAME_CLT}

${OBJS_DIR}	:
			mkdir ${OBJS_DIR}

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
			${CC} ${CFLAGS} -c $< -o $@ ${INCS}

clean:
			rm -rf ${OBJS_DIR}

fclean:		clean
			rm -f ${NAME_SRV}
			rm -f ${NAME_CLT}

re:			fclean all

.PHONY:		all clean fclean re
