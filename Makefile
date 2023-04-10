# **************************************************************************** #
#																			  #
#														 :::	  ::::::::	#
#	Makefile										   :+:	  :+:	:+:	#
#													 +:+ +:+		 +:+	  #
#	By: imurugar <imurugar@student.42madrid.com	+#+  +:+	   +#+		 #
#												 +#+#+#+#+#+   +#+			#
#	Created: 2023/03/04 15:47:46 by imurugar		  #+#	#+#			  #
#	Updated: 2023/04/08 01:17:20 by imurugar		 ###   ########.fr		#
#																			  #
# **************************************************************************** #

# /* ~~~~~~~ FOLDERS DIR ~~~~~~~ */
SRCS_DIR =		./src/
OBJ_DIR	 =		./obj/
INC_DIR	 =		./inc/

UTILS_DIR   =	utils/
SIGNAL_DIR  =	signal/
ENV_DIR 	=	env/
LEXER_DIR 	=	lexer/

# /* ~~~~~~~ FILES ~~~~~~~ */
INC =   minishell.h

SRCS	=	main.c \
			executor.c \
			parser.c \
			$(LEXER_DIR)lexer.c \
			$(UTILS_DIR)error.c \
			$(SIGNAL_DIR)handle_signals.c \
			$(ENV_DIR)fill_env.c \

# /* ~~~~~~~ INCLUDING LIBFT ~~~~~~~ */
LIBFT_DIR = libft
LIBFT_MAKE = Makefile
LIBFT_PATH = ${LIBFT_DIR}/libft.a

# /* ~~~~~~~ OTHER CONFIG ~~~~~~~ */
OBJ_FILES   = $(SRCS:.c=.o)

SRC = $(addprefix $(SRCS_DIR), $(SRCS))
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
INCLUDES = $(addprefix $(INC_DIR), $(INC))
OBJ_DIRS := $(sort $(dir $(OBJS)))

# /* ~~~~~~~ TESTING FLAGS ~~~~~~~ */
SANITIZE =
SANITIZE = -g3 -fsanitize=address
# SANITIZE = -g3 -fsanitize=thread

# /* ~~~~~~~ COMPILING INFO ~~~~~~~ */
GCC = gcc
CFLAGS = -lreadline $(SANITIZE) #-Wall -Wextra -Werror -lreadline #-pthread -Ofast -O3 -march=native $(SANITIZE)
LFLAGS:= -L $(LIBFT_DIR) -lft

# /* ~~~~~~~ OTHER ~~~~~~~ */
NAME = minishell
RM = rm -f

# /* ~~~~~~~ Colors ~~~~~~~ */
RED:="\033[1;31m"
GREEN:="\033[1;32m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
EOC:="\033[0;0m"

# /* ~~~~~~~ GENERATE DIRS ~~~~~~~ */
$(OBJ_DIR)%.o:$(SRCS_DIR)%.c $(INCLUDES)
	@mkdir -p $(@D)
	$(GCC) $(CFLAGS) -I $(INC_DIR) -MMD -c $< -o $@

all: obj ${NAME}

obj:
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@echo $(CYAN) "[Compiling libft]" $(RED)
	@cd $(LIBFT_DIR) && $(MAKE)
	@echo $(PURPLE) "[Compiling $@]" $(RED)
	@$(GCC) $(OBJS) $(CFLAGS) $(LFLAGS) -o $(NAME)
	@echo $(GREEN) "[FINISHED OK]" $(EOC)

clean:
	@echo $(PURPLE) "[🧹Cleaning...🧹]" $(EOC)
	@${RM} -Rf $(OBJ_DIR)
	@make -C ${LIBFT_DIR} -f ${LIBFT_MAKE} fclean

fclean: clean
	@echo $(PURPLE) "[🧹FCleaning...🧹]" $(EOC)
	${RM} -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
