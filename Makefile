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

# /* ~~~~~~~ MAIN DIRS ~~~~~~~ */
BUILTIN_DIR 	=	builtin/
ERR_FREE 		=	errors_frees/
PARSER_DIR 		=	parsing/
PIPE_DIR 		=	pipe_lst/
SIGNAL_DIR	  	=	signals/
VAR_LST_DIR	  	=	var_lst/

# /* ~~~~~~~ SUB DIRS ~~~~~~~ */
BUILDS_DIR 		=	$(PARSER_DIR)builds/
EXPANSION_DIR 	=	$(PARSER_DIR)expansion/
REDIRECTS_DIR 	=	$(PARSER_DIR)redirects_in_out/

# /* ~~~~~~~ HEADER FILES ~~~~~~~ */
INC 			=   minishell.h

# /* ~~~~~~~ SOURCE FILES ~~~~~~~ */
SRCS	=	main.c \
			init.c \
			exec_cmd.c \
			$(BUILTIN_DIR)cd.c \
			$(BUILTIN_DIR)echo.c \
			$(BUILTIN_DIR)env.c \
			$(BUILTIN_DIR)exit.c \
			$(BUILTIN_DIR)export.c \
			$(BUILTIN_DIR)export_shorter.c \
			$(BUILTIN_DIR)pwd.c \
			$(BUILTIN_DIR)unset.c \
			$(ERR_FREE)error.c \
			$(ERR_FREE)frees_and_closes.c \
			$(PARSER_DIR)commands.c \
			$(PARSER_DIR)heredoc.c \
			$(PARSER_DIR)parsing_pipe.c \
			$(PARSER_DIR)parsing_utils.c \
			$(PARSER_DIR)parsing.c \
			$(BUILDS_DIR)build_ins.c \
			$(BUILDS_DIR)hash_builds.c \
			$(EXPANSION_DIR)expansion_utils.c \
			$(EXPANSION_DIR)expansion.c \
			$(REDIRECTS_DIR)recognize_redirects.c \
			$(REDIRECTS_DIR)redirect_utils.c \
			$(PIPE_DIR)pipe_lst_add.c \
			$(PIPE_DIR)pipe_lst_del.c \
			$(SIGNAL_DIR)signal_handler.c \
			$(SIGNAL_DIR)signal_setup.c \
			$(VAR_LST_DIR)var_lst_add.c \
			$(VAR_LST_DIR)var_lst_del.c \
			$(VAR_LST_DIR)var_lst_get.c

# /* ~~~~~~~ INCLUDING LIBFT ~~~~~~~ */
LIBFT_DIR	= libft/
LIBFT_MAKE	= Makefile
LIBFT_PATH	= ${LIBFT_DIR}/libft.a
LIBFT_H_INC	:=	-I $(LIBFT_DIR)/inc/

# /* ~~~~~~~ INCLUDE CONFIG ~~~~~~~ */
OBJ_FILES   = $(SRCS:.c=.o)
SRC			= $(addprefix $(SRCS_DIR), $(SRCS))
OBJS		= $(addprefix $(OBJ_DIR), $(OBJ_FILES))
INCLUDES	= $(addprefix $(INC_DIR), $(INC))
OBJ_DIRS	:= $(sort $(dir $(OBJS)))
#INCLUDES	= $(H_INCLUDES)# $(LIBFT_H_INC)

# /* ~~~~~~~ TESTING FLAGS ~~~~~~~ */
 SANITIZE =
 SANITIZE = -g3 -fsanitize=address
# SANITIZE = -g3 -fsanitize=thread

# /* ~~~~~~~ COMPILING INFO ~~~~~~~ */
GCC = gcc
CFLAGS = -Wall -Wextra -Werror -lreadline -g $(SANITIZE)
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
$(OBJ_DIR)%.o: $(SRCS_DIR)%.c $(INCLUDES)
	@mkdir -p $(@D)
	$(GCC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR) -MMD -c $< -o $@

all: obj ${NAME}

obj:
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@echo $(CYAN) "[Compiling libft]" $(RED)
	@cd $(LIBFT_DIR) && $(MAKE)
	@echo $(PURPLE) "[Compiling $@]" $(RED)
	@$(GCC) $(OBJS) $(CFLAGS) $(LFLAGS) -o $(NAME) $(INCLUDES)
	@echo $(GREEN) "[FINISHED OK]" $(EOC)
	@echo "$$CUP"
	@echo $(CYAN) "[MINISHELL BY ARI AND KING]" $(EOC)

clean:
	@echo $(PURPLE) "[🧹Cleaning...🧹]" $(EOC)
	@${RM} -Rf $(OBJ_DIR)
	@make -C ${LIBFT_DIR} -f ${LIBFT_MAKE} fclean

fclean: clean
	@echo $(PURPLE) "[🧹FCleaning...🧹]" $(EOC)
	${RM} -f $(NAME)

re: fclean all

cup:
	@echo "$$CUP"

define CUP

_________________¶¶¶1___¶¶¶____¶¶¶1_______________
__________________¶¶¶____¶¶¶____1¶¶1______________
___________________¶¶¶____¶¶¶____¶¶¶______________
___________________¶¶¶____¶¶¶____¶¶¶______________
__________________¶¶¶____1¶¶1___1¶¶1______________
________________1¶¶¶____¶¶¶____¶¶¶1_______________
______________1¶¶¶____¶¶¶1___¶¶¶1_________________
_____________¶¶¶1___1¶¶1___1¶¶1___________________
____________1¶¶1___1¶¶1___1¶¶1____________________
____________1¶¶1___1¶¶1___1¶¶¶____________________
_____________¶¶¶____¶¶¶1___¶¶¶1___________________
______________¶¶¶¶___1¶¶¶___1¶¶¶__________________
_______________1¶¶¶1___¶¶¶1___¶¶¶¶________________
_________________1¶¶1____¶¶¶____¶¶¶_______________
___________________¶¶1____¶¶1____¶¶1______________
___________________¶¶¶____¶¶¶____¶¶¶______________
__________________1¶¶1___1¶¶1____¶¶1______________
_________________¶¶¶____¶¶¶1___1¶¶1_______________
________________11_____111_____11_________________
__________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶________
1¶¶¶¶¶¶¶¶¶¶¶__¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶________
1¶¶¶¶¶¶¶¶¶¶¶__1¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶________
1¶¶_______¶¶__1¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶________
1¶¶_______¶¶__1¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶________
1¶¶_______¶¶__¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶________
1¶¶_______¶¶__1¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶________
_¶¶¶¶¶¶¶¶¶¶¶__¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶________
_¶¶¶¶¶¶¶¶¶¶¶__¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶________
__________¶¶___1¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶1________
__________1¶¶___¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶_________
____________¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶11__________
11_____________________________________________111
1¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶1
__¶¶111111111¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶111111111¶__


endef
export CUP

.PHONY: all clean fclean re
