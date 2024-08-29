
SRCS = ./project/pipex.c ./utils/utils.c

BONUS_SRCS = ./project/pipex_bonus.c ./utils/utils_bonus.c ./get_next_line/get_next_line.c \
				./get_next_line/get_next_line_utils.c ./utils/here_doc.c

OBJ = ${SRCS:.c=.o}
BONUS_OBJ = ${BONUS_SRCS:.c=.o}

NAME = pipex
BONUS_NAME = pipex_bonus

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

%.o: %.c ./Includes/pipex.h ./get_next_line/get_next_line.h ./libft/libft.h
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJ}
	${CC} ${OBJ} ./libft/libft.a -o ${NAME}

${BONUS_NAME}: ${BONUS_OBJ}
	${CC} ${BONUS_OBJ} ./libft/libft.a -o ${BONUS_NAME}

all: ${NAME}

bonus: ${BONUS_NAME}

clean:
	${RM} ${OBJ} ${BONUS_OBJ}

fclean: clean
	${RM} ${NAME} ${BONUS_NAME}

re: fclean all

.PHONY: clean
