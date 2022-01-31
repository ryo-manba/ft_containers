NAME    := a.out
CXX     := clang++
CXXFLAGS:= -Wall -Wextra -Werror -std=c++11 -MMD -MP -pedantic

# Directories
SRCDIR  := ./src
OBJDIR  := ./obj
DEPDIR  := ./dep
INCDIR  := ./include

SRCFILE := main.cpp

SRCS    := $(addprefix $(SRCDIR)/, $(SRCFILE))
OBJS    := $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.cpp=.o)))
DEPS    := $(addprefix $(DEPDIR)/, $(notdir $(SRCS:.cpp=.d)))

RM      := rm -rf

.PHONY  : all
all     : $(OBJDIR) $(DEPDIR) $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

$(DEPDIR):
	mkdir -p dep

$(OBJDIR):
	mkdir -p obj

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -MMD -MP -MF $(DEPDIR)/$(notdir $(<:.cpp=.d)) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJDIR) $(DEPDIR)

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
