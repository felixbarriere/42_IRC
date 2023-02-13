NAME = IRC

SRCS = 	main.cpp \
		srcs/server.cpp \

OBJS_PATH = objects/

OBJS = ${addprefix ${OBJS_PATH}, ${SRCS:.cpp=.o}}

CC = c++

CFLAGS = -Wall -Werror -Wextra -std=c++98 -MMD -MP

all:		$(NAME)

$(NAME):	$(OBJS)
		${CC} $(OBJS) -o $(NAME)


-include $(OBJS_PATH)/*.d

${OBJS_PATH}%.o: ${SRCS_PATH}%.cpp
		@mkdir -p $(@D)
		${CC} ${CFLAGS} -c $< -o $@ ${INCLUDES}

clean:
		rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f -r ${OBJS_PATH}

re: fclean all

.PHONY: all clean fclean re