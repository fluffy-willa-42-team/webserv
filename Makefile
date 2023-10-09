# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awillems <awillems@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/09 08:35:24 by awillems          #+#    #+#              #
#    Updated: 2023/09/29 12:07:10 by mahadad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= webserv

# **************************************************************************** #

CC			:= g++
OBJ_EXT		:= .o
CODE_EXT	:= .cpp
HEAD_EXT	:= .hpp
INC			:= -I include
FLAGS		:= -W{all,extra,error} -std=c++98 -D UPLOAD_DIR="\"$(shell pwd)/static/upload/\""
DEV_FLAGS	:= -Wno-error={unused-parameter,unused-variable} -Wfatal-errors
DLEVEL		:= -1
SANI		:= 0
DEBUG		:= 0
DEV_COMPIL	:= 0

ifeq ($(DEBUG), 1)
	FLAGS += -g3
endif

ifeq ($(SANI), 1)
	FLAGS += -g3 -fsanitize=address
endif

ifeq ($(DLEVEL), 0)
	FLAGS += -D WDEBUG=DEBUG
else ifeq ($(DLEVEL), 1)
	FLAGS += -D WDEBUG=INFO
else ifeq ($(DLEVEL), 2)
	FLAGS += -D WDEBUG=WARN
else ifeq ($(DLEVEL), 3)
	FLAGS += -D WDEBUG=ERROR
endif

ifeq ($(OS),Windows_NT)
	$(error Dont compiles on windows)
else
	UNAME_S := $(shell uname -s)

	ifeq ($(UNAME_S),Linux)
		FLAGS += -D KOS_LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		FLAGS += -D KOS_DARWIN
	endif
endif


# **************************************************************************** #

SRC_DIR		:= src
INC_DIR		:= include
OBJ_DIR 	:= obj
LIB_DIR		:= lib

# **************************************************************************** #

SRCS		= $(SRCS_FIND)

# **************************************************************************** #

COLOR_NORMAL	:= \033[32;0m
COLOR_RED		:= \033[31;1m
COLOR_BLUE		:= \033[36;1m
COLOR_GREEN		:= \033[32;1m
COLOR_YELLOW	:= \033[33;1m

# **************************************************************************** #

VPATH		:= $(shell find $(SRC_DIR)/ -type d)

# Finds all sources in the SRC_DIR
SRCS_FIND	:= $(notdir $(shell find $(SRC_DIR) -type f -name "*$(CODE_EXT)"))

# Compiles all SRCS into .o files in the OBJ_DIR
OBJ			:= $(addprefix $(OBJ_DIR)/, $(SRCS:$(CODE_EXT)=$(OBJ_EXT)))

# Finds all folders in the LIB_DIR
ALL_LIB		:= $(shell find $(LIB_DIR)/ -maxdepth 1 -mindepth 1 -type d)

# Finds all the compiled libraries in ALL_LIB
LIB			:= $(shell find $(LIB_DIR)/ -type f -name "*.a")

# Finds all headers in the SRC_DIR and creates links to the original header files
HEADER		:= $(addprefix $(INC_DIR)/, $(notdir $(shell find $(SRC_DIR)/ -type f -name "*$(HEAD_EXT)")))

# All directories
DIR			:= $(SRC_DIR) $(INC_DIR) $(OBJ_DIR) $(LIB_DIR) ./static/upload

# Path to here
THISPATH	:= $(shell pwd)

# Remove Dev flags if dev mode is activated
DEV_FLAGS	:= $(if $(filter 1,$(DEV_COMPIL)),${DEV_FLAGS},)

# **************************************************************************** #

all: print $(DIR) $(ALL_LIB)
	@make -j -s compile
	@printf "\n"

compile: $(NAME)

# Creates every repositories if it does not exist
$(DIR):
	@mkdir $@
	@printf "$(COLOR_YELLOW).$(COLOR_NORMAL)"

# Compiles every lib in the lib repository
$(ALL_LIB): 
	@make -sC $@

# Takes any C/CPP files and transforms into an object into the OBJ_DIR
$(OBJ_DIR)/%$(OBJ_EXT): %$(CODE_EXT) $(HEADER)
	@$(CC) $(FLAGS) ${DEV_FLAGS} $(INC) -o $@ -c $<
	@printf "$(COLOR_RED).$(COLOR_NORMAL)"

# Takes any header files and creates a hard link in INC_DIR
$(INC_DIR)/%$(HEAD_EXT): %$(HEAD_EXT)
	@ln -s $(THISPATH)/$< $(INC_DIR)/
	@printf "$(COLOR_BLUE).$(COLOR_NORMAL)"

# Takes an name of executable and compiles everything into it
$(NAME): $(HEADER) $(OBJ)
	@$(CC) $(FLAGS) ${DEV_FLAGS} $(OBJ) $(INC) $(LIB) -o $(NAME)
	@chmod 777 $(NAME)

print:
ifeq ($(DEV_COMPIL),1)
	@printf "$(COLOR_YELLOW)[WARN] Dev flags are used in compilation\n   /!\\ remove them before submiting your project$(COLOR_NORMAL)\n"
endif
	@printf "$(COLOR_GREEN)$(NAME) : $(COLOR_NORMAL)"

# **************************************************************************** #

clean:
	@rm -rf $(OBJ_DIR)
	@for path in $(ALL_LIB); do \
		make -sC $$path clean;\
	done

# **************************************************************************** #

fclean:
	@rm -rf $(OBJ_DIR)* $(INC_DIR)* $(NAME)
	@for path in $(ALL_LIB); do \
		make -sC $$path fclean;\
	done

# **************************************************************************** #

print_src:
	@for elem in $(SRCS_FIND); do \
		echo $$elem;\
	done

# **************************************************************************** #

re: fclean all

# **************************************************************************** #

exe: all
	@./$(NAME) ./conf/example1.conf

# **************************************************************************** #

.PHONY: all, fclean, clean, re, print_src, $(ALL_LIB)
