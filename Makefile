# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes	// Check complet de valgrind.
# lsof -i -a -c ircserv  // Check les leaks de fds associes au reseau (sockets).

NAME = IRC

INCS = 	class/server.hpp \
		class/client.hpp \
		class/message.hpp \
		class/channel.hpp \
		utils.hpp \

SRCS = 	main.cpp \
		class/server.cpp \
		class/client.cpp \
		class/message.cpp \
		show_config.cpp \
		ft_split.cpp \
		utils.cpp \
		cmd/addmotd.cpp \
		cmd/addomotd.cpp \
		cmd/chghost.cpp \
		cmd/chgname.cpp \
		cmd/globops.cpp \
		cmd/join.cpp \
		cmd/list.cpp \
		cmd/motd.cpp \
		cmd/opermotd.cpp \
		cmd/names.cpp \
		cmd/nick.cpp \
		cmd/user.cpp \
		cmd/mode.cpp \
		cmd/ping.cpp \
		cmd/wallops.cpp \
		cmd/whois.cpp \
		cmd/pass.cpp \
		cmd/part.cpp \
		cmd/privmsg.cpp \
		cmd/quit.cpp \

OBJS = ${SRCS:.cpp=.o}

OBJS_PATH = obj/
INCS_PATH = inc/
SRCS_PATH = src/

OBJS := ${addprefix ${OBJS_PATH}, ${OBJS}}
INCS := ${addprefix ${INCS_PATH}, ${INCS}}
SRCS := ${addprefix ${SRCS_PATH}, ${SRCS}}

CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98
# CXXFLAGS = -std=c++98

all:		$(NAME)

${OBJS_PATH}%.o: ${SRCS_PATH}%.cpp
		@mkdir -p $(OBJS_PATH)
		@mkdir -p $(OBJS_PATH)/class
		@mkdir -p $(OBJS_PATH)/cmd
		${CXX} ${CXXFLAGS} -c $< -o $@ -I${INCS_PATH}

$(NAME):	$(OBJS)
		${CXX} ${CXXFLAGS} $(OBJS) -o $(NAME)

clean:
		rm -rf $(OBJS_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
