NAME    := a.out
CXX     := clang++
CXXFLAGS:= -Wall -Wextra -Werror -std=c++98 -MMD -MP -pedantic -g -fsanitize=address

# Directories
#SRCDIR  := ./src
SRCDIR  := ./test
OBJDIR  := ./obj
DEPDIR  := ./dep
INCDIR  := ./include
TESTDIR := ./test

#SRCFILE := main.cpp
SRCFILE := test_vector.cpp \
		   tester.cpp

SRCS    := $(addprefix $(SRCDIR)/, $(SRCFILE))
OBJS    := $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.cpp=.o)))
DEPS    := $(addprefix $(DEPDIR)/, $(notdir $(SRCS:.cpp=.d)))

RM      := rm -rf

.PHONY  : all
all     : $(NAME)

$(NAME) : $(OBJDIR) $(DEPDIR) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

$(DEPDIR):
	mkdir -p dep

$(OBJDIR):
	mkdir -p obj

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -I$(TESTDIR) -MMD -MP -MF $(DEPDIR)/$(notdir $(<:.cpp=.d)) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJDIR) $(DEPDIR)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

test: $(NAME)
	./a.out

debug: CXXFLAGS += -g -fsanitize=address
debug: re test

leak: CXXFLAGS += -DLEAK=1
leak: re test

.PHONY: test debug leak
-include $(DEPS)
