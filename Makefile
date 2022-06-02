NAME_STL = container_stl
SRCS_STL = main_stl.cpp
OBJS_STL = $(SRCS_STL:.cpp=.o)

CXX			= g++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98
RM			= rm -rf

CCBLUE		= \033[34m
CCBLUE_BOLD	= \033[1;34m
CCEND		= \033[0m

.PHONY: all clean fclean re

all: $(NAME_STL)

$(NAME_STL): $(OBJS_STL)
	$(CXX) $(OBJS_STL) $(CXXFLAGS) -o $(NAME_STL)
	@echo "$(CCBLUE_BOLD) >>> make $(NAME_STL) done!  <<< $(CCEND)"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "$(CCBLUE) >>> clean main projects object files. <<< $(CCEND)"
	$(RM) $(OBJS_STL)

fclean: clean
	@echo "$(CCBLUE) >>> clean main project's executable. <<< $(CCEND)"
	$(RM) $(NAME_STL)

re: fclean all
