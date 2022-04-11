NAME    := a.out
CXX     := clang++
CXXFLAGS:= -Wall -Wextra -Werror -std=c++98 -MMD -MP -pedantic -g3

# Directories
SRCDIR  := ./test
#SRCDIR  := ./
OBJDIR  := ./obj
DEPDIR  := ./dep
INCDIR  := ./include
TESTDIR := ./test

#SRCFILE := main.cpp
SRCFILE := test_map.cpp \
		   test_vector.cpp \
		   test_stack.cpp \
		   test_pair.cpp \
		   tester.cpp \
		   main.cpp

SUBJECT_SRC := test/subject_main.cpp
SUBJECT_OBJ := $(SUBJECT_SRC:.cpp=.o)
SUBJECT_NAME := subj

SRCS    := $(addprefix $(SRCDIR)/, $(SRCFILE))
OBJS    := $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.cpp=.o)))
DEPS    := $(addprefix $(DEPDIR)/, $(notdir $(SRCS:.cpp=.d)))

RM      := rm -rf

.PHONY  : all
all     : $(NAME)

$(NAME) : $(OBJDIR) $(DEPDIR) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(SUBJECT_NAME) : $(SUBJECT_OBJ)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $(SUBJECT_OBJ) -o $(SUBJECT_NAME)

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
	$(RM) $(NAME) $(SUBJECT_NAME)

.PHONY: re
re: fclean all

test: $(NAME)
	./a.out

t: $(NAME)
	./a.out

d: CXXFLAGS += -g -fsanitize=address -DDEBUG=1
d: re test

l: CXXFLAGS += -DLEAK=1
l: re test

.PHONY: test debug leak
-include $(DEPS)
