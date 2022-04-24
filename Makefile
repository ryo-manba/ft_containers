NAME    := a.out
CXX     := clang++
CXXFLAGS:= -Wall -Wextra -Werror -std=c++98 -MMD -MP -g3 -pedantic

# Directories
SRCDIR  := ./test
OBJDIR  := ./obj
DEPDIR  := ./dep
INCDIR  := ./include
TESTDIR := ./test

SRCFILE := test_map.cpp \
		   test_vector.cpp \
		   test_stack.cpp \
		   test_pair.cpp \
		   tester.cpp \
		   main.cpp

SUBJ_SRC := test/subject_main.cpp
SUBJ_OBJ := $(SUBJ_SRC:.cpp=.o)
SUBJ_DEP := $(SUBJ_SRC:.cpp=.d)
SUBJ_NAME := subject

SRCS    := $(addprefix $(SRCDIR)/, $(SRCFILE))
OBJS    := $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.cpp=.o)))
DEPS    := $(addprefix $(DEPDIR)/, $(notdir $(SRCS:.cpp=.d)))

RM      := rm -rf

all     : $(NAME) ## Compile

$(NAME): $(OBJDIR) $(DEPDIR) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

subject: $(SUBJ_OBJ) ## Compile in Subject
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $(SUBJ_OBJ) -o $(SUBJ_NAME)

$(DEPDIR):
	mkdir -p dep

$(OBJDIR):
	mkdir -p obj

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -I$(TESTDIR) -MMD -MP -MF $(DEPDIR)/$(notdir $(<:.cpp=.d)) -c $< -o $@

clean:
	$(RM) $(OBJDIR) $(DEPDIR) $(SUBJ_OBJ) $(SUBJ_DEP)

fclean: clean
	$(RM) $(NAME) $(SUBJ_NAME)
	make fclean -C benchmark

re: fclean all

.PHONY: all clean fclean re

debug: CXXFLAGS += -fsanitize=address -DDEBUG=1 ## Compile in Debug mode
debug: re test

leak: CXXFLAGS += -DLEAK=1 ## Compile in Leak mode
leak: re test

test: $(NAME) ## Run UnitTest
	./a.out

bench: ## Run BenchmarkTest
	make test -C benchmark

b: bench
d: debug
s: subject
t: test
l: leak

.PHONY: test debug leak subj bench help
.PHONY: t d l s b

-include $(DEPS)

.PHONY: help
help:
	@grep -E '^[a-zA-Z_-]+\t*:.*?## .*$$' Makefile | awk 'BEGIN {FS = "\t*:.*?## "}; {printf "\033[36m%-10s\033[0m %s\n", $$1, $$2}'
