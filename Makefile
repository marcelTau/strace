##
## EPITECH PROJECT, 2019
## d
## File description:
## d
##

END        		= \033[0m
BOLD        	= \033[1m
GREY        	= \033[30m
RED        		= \033[31m
GREEN        	= \033[32m
YELLOW        	= \033[33m
BLUE        	= \033[34m
PURPLE        	= \033[35m
CYAN        	= \033[36m
WHITE        	= \033[37m

EXTENSION 		= .c
CC 				= @gcc
CXX 			= @g++
# LIBS 			= -l sfml-window -l sfml-audio -l sfml-system -l sfml-network -l sfml-graphics
# CFLAGS 			+= -Wall -Werror -Wextra



NAME 			= strace

SRC 			= src/main.c 		\
				  src/arg_parse.c 	\
				  src/strace.c 	\
				  src/print_funcs.c 	\
				  src/print_syscall.c 	\



ifeq ($(EXTENSION), .c)
OBJ  			= $(SRC:.c=.o)
else
OBJ  			= $(SRC:.cpp=.o)
endif

all: 			strace

strace: 			$(OBJ)
ifeq ($(EXTENSION), .c)
	@$(CC) -o $(NAME) $(LIBS) $(OBJ)
else
	@$(CXX) -o $(NAME) $(LIBS) $(OBJ)
endif
	@echo -e "$(GREEN)* * * * * COMPLETED * * * * *$(END)"

test: 	all
	@./blender.py

clean:
	@rm -f $(OBJ)
	@echo -e "$(RED)$(BOLD)* * * * *  CLEANED  * * * * *$(END)"

fclean: clean
	@rm -f $(NAME)
	@echo -e "$(RED)$(BOLD)* * * * *  CLEANED ALL  * * * * *$(END)"

re: 	fclean all

ifeq ($(EXTENSION), .c)
src/%.o:	src/%$(EXTENSION)
	@$(CC) $(CFLAGS) $(LIBS) -c -o $@ $<							\
	&& echo -e "$(GREEN)[- - OK - - - -]$(BOLD)" $< "$(END)"			\
	|| echo -e "$(RED)[- - - - KO - -]$(BOLD)" $< "$(END)"
else
src/%.o:	src/%$(EXTENSION)
	@$(CXX) $(CFLAGS) $(LIBS) -c -o $@ $<							\
	&& echo -e "$(GREEN)[- - OK - - - -]$(BOLD)" $< "$(END)"			\
	|| echo -e "$(RED)[- - - - KO - -]$(BOLD)" $< "$(END)"
endif

.PHONY: all clean fclean re
