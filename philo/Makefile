OBJS_DIR = objs

SRCS	:=	$(shell find srcs/*.c -exec basename \ {} \;)

OBJS = ${patsubst %.c,${OBJS_DIR}/%.o,${SRCS}}

HEADERS = philo.h

NAME = philo

# CC = cc -fsanitize=thread
CC = cc
CFLAGS = -Werror -Wall -Wextra -pthread
# CFLAGS = -fsanitize=address -g3 -pthread
# CFLAGS = -g3 -pthread

# -- RULES -- #

${NAME}: ${OBJS_DIR} ${OBJS} ${HEADERS}
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	@echo "\033[32m$ ${NAME} compiled !"
	@echo "----------------------------\033[0m"

# debug: ${OBJS_DIR} ${OBJS} ${HEADERS}
# 	@${CC} ${CFLAGS} -fsanitize=address -g3 ${OBJS} -o ${NAME}
# 	@echo "\033[32m$ ${NAME} compiled !"
# 	@echo "----------------------------\033[0m"

all: ${NAME}

$(OBJS_DIR):
	@mkdir -p ${OBJS_DIR}
	@echo "\033[33mcompiling ${NAME}..."

${OBJS_DIR}/%.o: srcs/%.c
	@${CC} ${CFLAGS} -I. -c $< -o $@

clean:
	@rm -rf ${OBJS_DIR}
	@echo "\033[32mclean !\033[0m"

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY:	all clean fclean re
