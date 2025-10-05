# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madamou <madamou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 12:57:50 by madamou           #+#    #+#              #
#    Updated: 2025/10/05 21:21:38 by madamou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLACK=	$(shell tput -Txterm setaf 0)
RED= 	$(shell tput -Txterm setaf 1)
GREEN= 	$(shell tput -Txterm setaf 2)
WHITE= 	$(shell tput -Txterm setaf 7)
YELLOW=	$(shell tput -Txterm setaf 3)
BLUE=	$(shell tput -Txterm setaf 6)
PURPLE=	$(shell tput -Txterm setaf 5)
END= 	$(shell tput -Txterm sgr0)

CC = cc

C_FLAGS = -Wall -Werror -Wextra -g3 #-MMD -O2 -MP -O3 -Ofast -ffast-math 

SRCS_DIR = srcs/

UTILS = $(addprefix utils/, utils.c)

EVENT = $(addprefix event/, trigger_functions.c  trigger_functions_utils.c)

CHECK_ENEMY = $(addprefix check_enemy/, check_enemy.c)

RENDER = $(addprefix render/, crosshair.c gun.c render.c)

DRAW = $(addprefix draw/, draw.c)

SPRITE = $(addprefix sprites/, sprites_functions.c sprites_functions_utils.c sprites_functions_utils2.c)

CHECKING = $(addprefix checking/, checking_map.c check_map_playable.c)

RAYCAST_SPRITE =  $(addprefix raycast_sprite/, raycast_sprite.c raycast_sprites_utils.c)

DDA = $(addprefix dda/, raycast.c raycast_utils.c dda.c dda_utils.c draw_stripe.c $(RAYCAST_SPRITE) $(CHECK_ENEMY))

MINI_MAP = $(addprefix minimap/, render_map.c render_map_utils.c)

MOVE = $(addprefix move/, fov_move.c player_move.c)


RAYCASTING = $(addprefix raycasting/, $(DDA) $(MINI_MAP))

PARSING = $(addprefix parsing/, parser.c map_parsing.c utils.c $(CHECKING))

MLX = $(addprefix mlx/, init_mlx.c init_mlx_utils.c $(MOVE) $(SPRITE) $(EVENT) $(RENDER) $(DRAW))

OBJS_DIR = .objets/

SRCS = main.c $(PARSING) $(RAYCASTING) $(MLX) $(UTILS)

SRCS := $(SRCS:%=$(SRCS_DIR)/%)

OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

DIR_DUP = mkdir -p $(@D)

G				= $(BLUE)
X 				= $(END)
BAR_SIZE		= 50

TOTAL_FILES		:= $(words $(SRCS))
COMPILED_FILES	:= 0

LIBFT = libft.a

MINI_LIBX_DIR = ./minilibx-linux
MINI_LIBX = libmlx.a

NAME = ./cub3D

all : $(MINI_LIBX) $(LIBFT) $(NAME)

$(LIBFT) :
	@echo
	@echo "👷$(GREEN)compiling libft$(END)👷"
	@make -sC ./libft
	@echo
	@echo "👷$(GREEN)libft compilation done$(END)👷"

$(MINI_LIBX) :
	@make -sC $(MINI_LIBX_DIR)

$(NAME) : message $(OBJS)
	@$(CC) $(C_FLAGS) $(OBJS) -o $@ -L./libft -lft -lm -L$(MINI_LIBX_DIR) -lmlx -lX11 -lXext 
	@echo
	@echo "🧊$(BLUE)executable created >_$(END)✅"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@$(DIR_DUP)
	@$(CC) $(C_FLAGS) -c -I includes $< -o $@
	@$(eval COMPILED_FILES := $(shell echo $$(($(COMPILED_FILES)+1))))
	@echo -n ""
	@for i in `seq 1 $(shell echo "$$(($(COMPILED_FILES)*$(BAR_SIZE)/$(TOTAL_FILES)))")`; do \
		echo -n "$(G)▰$(X)" ; \
	done
	@for i in `seq 1 $(shell echo "$$(($(BAR_SIZE)-$(COMPILED_FILES)*$(BAR_SIZE)/$(TOTAL_FILES)))")`; do \
		echo -n "▱" ; \
	done
	@echo -n " ($(shell echo "scale=2; $(COMPILED_FILES)/$(TOTAL_FILES) * 100" | bc)%) "
	@echo -n ""
	@printf "%d/%d" $(COMPILED_FILES) $(TOTAL_FILES)
	@echo -n " "
	@printf "%s" $(notdir $<)
	@printf "\e[0K\r"

form :
	@python3 -m c_formatter_42 $(SRCS)

message :
	@echo
	@echo "$(BLUE)🔩compiling cube3D🔩$(END)"
	
leak : all
	@valgrind --leak-check=full --show-leak-kinds=all  ./minishell

push:
	@python3 -m c_formatter_42 $(addprefix $(SRCS_DIR), main.c $(PARSING) $(PROMPT) $(SIGNALS) \
	 $(BINARY_TREE) $(ERROR) $(EXEC) $(ENV) $(UTILS) $(BUILTINS)) | norminette | grep Error
	@git add .
	@echo -n "$(BLUE)Enter your commit message: $(END)"
	@read commit_message; \
	git commit -m "$$commit_message"; \
	git push; \
	echo "$(YELLOW)All has been pushed with '$$commit_message' in commit$(END)"

debug : all
	@lldb $(NAME) ./maps/test.cub

docker:
	@if [ -z $$(docker images -q cube3d-app_x11) ]; then \
		echo "🐳$(BLUE)Image cube3d-app_x11 not found, work in progress...$(END)🐳"; \
		docker-compose build; \
		echo "🐳$(BLUE)Docker container is built $(END)✅"; \
	fi
	@echo "🐳$(BLUE)Docker container is built $(END)✅"
	xhost +local:
	@docker-compose run app
	xhost -local:

clean : 
	@rm -rf $(OBJS_DIR)
	@make clean -sC ./libft
	@make clean -C $(MINI_LIBX_DIR)
	@echo "🧼🧼$(PURPLE)objects cleaned$(END)🧼🧼"

fclean : clean
	@rm -rf $(NAME)
	@make fclean -sC ./libft
	@echo "🧼🧼$(PURPLE)executable cleaned$(END)🧼🧼"

re_mlx :
	@make re -C $(MINI_LIBX_DIR)
	
re : re_mlx fclean all

.PHONY : all clean fclean re debug push leak docker 
