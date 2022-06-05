NAME_FT		= a_ft_container.out
NAME_STD	= b_std_container.out
SRCS		= main.cpp
HEADERS		= vector.hpp
OBJS_A		= $(SRCS:.cpp=.ft_o)
OBJS_B		= $(SRCS:.cpp=.std_o)
OBJS		= $(OBJS_A) $(OBJS_B)

CXX			= c++
CXXFLAGS	= -Wall -Wextra
#FIXME: add Werror before submission
#CXXFLAGS	= -Wall -Wextra -Werror -std=c++98
RM			= rm -rf

CCBLUE		= \033[34m
CCBLUE_BOLD	= \033[1;34m
CCEND		= \033[0m

.PHONY: all clean fclean re ft std

all: $(NAME_FT) $(NAME_STD)

ft: $(NAME_FT)

std: $(NAME_STD)

$(NAME_FT): $(OBJS_A)
	$(CXX) $(OBJS_A) $(CXXFLAGS) -o $(NAME_FT)
	@echo "$(CCBLUE_BOLD) >>> make $(NAME_FT) done!  <<< $(CCEND)"

$(NAME_STD): $(OBJS_B)
	$(CXX) $(OBJS_B) $(CXXFLAGS) -o $(NAME_STD)
	@echo "$(CCBLUE_BOLD) >>> make $(NAME_STD) done!  <<< $(CCEND)"

%.ft_o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -D FT -c $< -o $@

%.std_o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -D STD -c $< -o $@

clean:
	@echo "$(CCBLUE) >>> clean object files. <<< $(CCEND)"
	$(RM) $(OBJS)

fclean: clean
	@echo "$(CCBLUE) >>> clean executables. <<< $(CCEND)"
	$(RM) $(NAME_FT) $(NAME_STD)

re: fclean all
