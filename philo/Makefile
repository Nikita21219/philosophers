NAME = philo
CC = cc
SRCDIR = ./src
OBJDIR = ./objs
HEADDIR = ./includes
CFLAGS = -Wall -Wextra -Werror
HEADER = philo.h
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(addprefix $(OBJDIR)/,$(notdir $(SRC:.c=.o)))

all:    $(NAME)

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(HEADDIR)/$(HEADER)
		gcc $(CFLAGS) -c $< -o $@

$(NAME):    $(OBJDIR) $(OBJ)
	$(CC) -g -fsanitize=thread $(CFLAGS) -o $(NAME) -I $(HEADDIR)/$(HEADER) $(OBJ)

$(OBJDIR):

	@if [ ! -d $(OBJDIR) ] ; then echo "creating $(OBJDIR)" ; mkdir $(OBJDIR); fi
clean:
	@if [ -d $(OBJDIR) ] ; then echo "deleting $(OBJDIR)" ; rm -r $(OBJDIR); fi

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
