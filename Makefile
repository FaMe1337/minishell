# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fabio <fabio@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/14 14:31:18 by toferrei          #+#    #+#              #
#    Updated: 2025/03/20 19:32:44 by fabio            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

LIBFT		=	Libft/
LIBFT_A		=	$(LIBFT)libft.a

OBJ_DIR		=	Objects/

SRC			=	Sources/

BLT			=	Built_ins/
ERR			=	Error_management/
EXC			=	Executor/
EXP			=	Expanse/
INI			=	Initialization/
LST			=	List_utils/
PRS			=	Parsing/
QOT			=	Quotes/
RED			=	Redirections_handler/
SGN			=	Signals/
TOK			=	Tokens/

SOURCES		=	$(SRC)$(BLT)change_directory_set.c \
				$(SRC)$(BLT)change_directory.c \
				$(SRC)$(BLT)echo.c \
				$(SRC)$(BLT)exit.c \
				$(SRC)$(BLT)export.c \
				$(SRC)$(BLT)env.c \
				$(SRC)$(BLT)pwd.c \
				$(SRC)$(BLT)unset.c \
				$(SRC)$(ERR)error_and_cleaning.c \
				$(SRC)$(ERR)error_and_cleaning_2.c \
				$(SRC)$(EXC)child.c \
				$(SRC)$(EXC)exec_builtins.c \
				$(SRC)$(EXC)executor.c \
				$(SRC)$(EXP)expanse_utils.c \
				$(SRC)$(EXP)expanse.c \
				$(SRC)$(INI)env_to_list.c \
				$(SRC)$(INI)get_prompt.c \
				$(SRC)$(INI)init_data.c \
				$(SRC)$(INI)minimal_list_init.c \
				$(SRC)$(LST)ft_clean_list.c \
				$(SRC)$(LST)ft_print_list.c \
				$(SRC)$(LST)list_utils.c \
				$(SRC)$(LST)list_utils_2.c \
				$(SRC)$(LST)list_utils_3.c \
				$(SRC)$(PRS)cmd_lst_creation_utils.c \
				$(SRC)$(PRS)cmd_lst_creation.c \
				$(SRC)$(PRS)parsing.c \
				$(SRC)$(QOT)quotes.c \
				$(SRC)$(QOT)remove_quotes.c \
				$(SRC)$(TOK)first_tokenization.c \
				$(SRC)$(TOK)second_tokenization.c \
				$(SRC)$(TOK)split.c \
				$(SRC)$(RED)heredoc.c \
				$(SRC)$(RED)heredoc_2.c \
				$(SRC)$(RED)redirections_handler.c \
				$(SRC)$(SGN)signals.c \
				$(SRC)$(SGN)signals_waitpid.c \
				$(SRC)main.c

OBJECTS		=	$(patsubst $(SRC)%.c, $(OBJ_DIR)%.o, $(SOURCES))

# Compiler and Flags
CC			=	cc
LDFLAGS		=	-L$(LIBFT) -lft
CFLAGS		=	-g -Wall -Wextra -Werror
RFLAGS		=	-lreadline

# Default Target
all: $(NAME)

# Build the executable
$(NAME): $(OBJECTS)
	@$(MAKE) -s -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(LDFLAGS) $(RFLAGS)
	@echo "All files were created"

# Rule for building object files
$(OBJ_DIR)%.o: $(SRC)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	@rm -f $(OBJECTS)
	@rm -rf $(OBJ_DIR)
	@echo "Object files were cleaned"

# Full clean
fclean: clean
	@$(MAKE) -s -C $(LIBFT) clean
	@rm -f $(NAME)
	@echo "All files were cleaned"

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
