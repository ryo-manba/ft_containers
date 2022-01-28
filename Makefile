NAME    := a.out
CXX     := clang++
CXXFLAGS:= -Wall -Wextra -Werror -std=c++98 -MMD -MP -pedantic

SRCS    := main.cpp
OBJS    := $(SRCS:.cpp=.o)
DEPS    := $(SRCS:.cpp=.d)

.PHONY  : all
all     : $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

.PHONY: clean
clean:
	$(RM) $(OBJS) $(DEPS)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

.PHONY: test
test: $(NAME)
	./a.out

.PHONY: debug list
debug: CXXFLAGS += -g -fsanitize=address
debug: re

-include $(DEPS)
