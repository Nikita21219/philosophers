NAME = philo_bonus
CC = cc
OBJDIR = ./objs
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

HEADER = philo.h
SRC = $(wildcard *.c)
OBJ = $(addprefix $(OBJDIR)/,$(notdir $(SRC:.c=.o)))

all:    $(NAME)

$(OBJDIR)/%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):    $(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) -I $(HEADER) $(OBJ)

$(OBJDIR):
	@if [ ! -d $(OBJDIR) ] ; then echo "creating $(OBJDIR)" ; mkdir $(OBJDIR); fi
	
clean:
	@if [ -d $(OBJDIR) ] ; then echo "deleting $(OBJDIR)" ; rm -r $(OBJDIR); fi

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
