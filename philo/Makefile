SRCS	= main.c philo_actions.c utils.c threads.c philos.c init.c checks.c

OBJS	= $(addprefix .obj/, ${SRCS:.c=.o})

CC	= cc

RM	= rm -f

HEADER	= philo.h

FLAGS	= -Wall -Werror -Wextra

NAME	= philo

all:	${NAME}

.obj/%.o:	srcs/%.c ${HEADER}
		mkdir .obj -p
		${CC} ${FLAGS} -c $< -o $@ -I .

${NAME}: ${OBJS} ${LIBFT} ${HEADER}
	${CC} ${FLAGS} ${OBJS} -lpthread -o ${NAME}

clean:
	${RM} ${OBJS}
	${RM} -r .obj
	
fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY: clean fclean all re

