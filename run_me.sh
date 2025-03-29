#!/bin/bash


make re
clear
valgrind --suppressions=readline.supp --show-leak-kinds=all --leak-check=full --track-origins=yes --track-fds=yes ./minishell 