NAME_STL := bm_stl
NAME_FT  := bm_ft
CXX      := clang++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic -g3

# Directories
SRCDIR     := ./
OBJDIR_FT  := ./objs_ft
OBJDIR_STL := ./objs_stl
INCDIR     := ../include

#TESTDIR   := ./test
INC := -I$(INCDIR)

SRCFILE := timer.cpp\
           bm_stack.cpp \
           bm_vector.cpp \
           bm_map.cpp \
           main.cpp

SRCS       := $(addprefix $(SRCDIR)/, $(SRCFILE))
OBJS_FT    := $(addprefix $(OBJDIR_FT)/,  $(notdir $(SRCS:.cpp=.o)))
OBJS_STL   := $(addprefix $(OBJDIR_STL)/, $(notdir $(SRCS:.cpp=.o)))

RM      := rm -rf

LOG_STL  := benchmark_stl.log
LOG_FT   := benchmark_ft.log
LOG_DIFF := benchmark_diff.log

.PHONY  : all
all     : $(NAME_STL) $(NAME_FT)

$(NAME_FT) : $(OBJDIR_FT) $(OBJS_FT)
	$(CXX) $(CXXFLAGS) -o $(NAME_FT) $(OBJS_FT)

$(NAME_STL) : $(OBJDIR_STL) $(OBJS_STL)
	$(CXX) $(CXXFLAGS) -o $(NAME_STL) $(OBJS_STL)

$(OBJDIR_STL):
	mkdir -p $(OBJDIR_STL)

$(OBJDIR_FT):
	mkdir -p $(OBJDIR_FT)

$(OBJDIR_STL)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $<

$(OBJDIR_FT)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -o $@ -D FT=1 -c $<

.PHONY: clean
clean:
	$(RM) $(OBJDIR_FT) $(OBJDIR_STL)
	$(RM) $(LOG_FT) $(LOG_STL) $(LOG_DIFF)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME_FT) $(NAME_STL)

.PHONY: re
re: fclean all

test: all
	./bm_ft  > $(LOG_FT)
	./bm_stl > $(LOG_STL)
	diff -y $(LOG_FT) $(LOG_STL) > $(LOG_DIFF) || ./show_diff.sh

t: test

debug: CXXFLAGS += -g -fsanitize=address -DDEBUG=1
debug: re test

d: debug

.PHONY: test debug
