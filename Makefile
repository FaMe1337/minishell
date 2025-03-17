# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toferrei <toferrei@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/14 14:31:18 by toferrei          #+#    #+#              #
#    Updated: 2025/03/17 15:55:46 by toferrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

LIBFT		=	Libft/
LIBFT_A		=	$(LIBFT)libft.a

OBJ_DIR		=	Objects/

SRC			=	Sources/

INI			=	$(SRC)Initialization/
ERR			=	$(SRC)Error_management/
PRS			=	$(SRC)Parsing/
EXP			=	$(SRC)Expanse/
QOT			=	$(SRC)Quotes/
TOK			=	$(SRC)Tokens/
EXC			=	$(SRC)Executor/
RED			=	$(SRC)Red_handler/
BLT			=	$(SRC)Built_ins/
LST			=	$(SRC)List_utils/
SGN			=	$(SRC)Signals/

SOURCES		=	$(SRC)change_directory_set.c \
				$(SRC)change_directory.c \
				$(SRC)child.c \
				$(SRC)cmd_lst_creation_utils.c \
				$(SRC)cmd_lst_creation.c \
				$(SRC)echo.c \
				$(SRC)env_to_list.c \
				$(SRC)env.c \
				$(SRC)error_and_cleaning.c \
				$(SRC)error_and_cleaning_2.c \
				$(SRC)exec_builtins.c \
				$(SRC)executor.c \
				$(SRC)exit.c \
				$(SRC)expanse_utils.c \
				$(SRC)expanse.c \
				$(SRC)export.c \
				$(SRC)first_tokenization.c \
				$(SRC)ft_clean_list.c \
				$(SRC)ft_print_list.c \
				$(SRC)get_prompt.c \
				$(SRC)heredoc.c \
				$(SRC)heredoc_2.c \
				$(SRC)init_data.c \
				$(SRC)list_utils.c \
				$(SRC)list_utils_2.c \
				$(SRC)list_utils_3.c \
				$(SRC)main.c \
				$(SRC)minimal_list_init.c \
				$(SRC)parsing.c \
				$(SRC)pwd.c \
				$(SRC)quotes.c \
				$(SRC)redirections_handler.c \
				$(SRC)remove_quotes.c \
				$(SRC)second_tokenization.c \
				$(SRC)signals.c \
				$(SRC)signals_waitpid.c \
				$(SRC)split.c \
				$(SRC)unset.c

OBJECTS		=	$(patsubst $(SRC)%.c, $(OBJ_DIR)%.o, $(SOURCES))

# OBJECTS		=	$(patsubst $(SRC)%.c, $(OBJ_DIR)%.o, $(SOURCES))

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