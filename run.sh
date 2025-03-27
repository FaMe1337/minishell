#!/bin/bash


make re
clear
valgrind --suppressions=readline.supp --track-origins=yes --track-fds=yes ./minishell 