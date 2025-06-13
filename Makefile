include				$(shell git rev-parse --show-toplevel)/build/setup.mk


# ***************************** CONFIGURATION ******************************** #

NAME			:=	ft_shmup
MSG_PROGRESS	:=	"👾"
MSG_USAGE		?=	"Usage: ./$(NAME)"
COLOR_MAKE		=	$(STY_MAG)


#	Dependencies

LIBS_LOCAL		=	$(LIB_ROOT_DIR)/libftpp/libftpp.a \
					$(LIB_ROOT_DIR)/libft/libft.a

#	macOS Homebrew path
ifneq (, $(wildcard /usr/local/opt/ncurses/lib))
LDFLAGS			:=	-L/usr/local/opt/ncurses/lib
endif

#	Compile tiny test program to see if ncursesw is available
HAS_NCURSESW	=	$(shell echo 'int main(){}' | c++ -x c++ $(LDFLAGS) -lncursesw -o /dev/null - 2>/dev/null && echo yes || echo no)
HAS_NCURSES		=	$(shell echo 'int main(){}' | c++ -x c++ $(LDFLAGS) -lncurses -o /dev/null - 2>/dev/null && echo yes || echo no)
ifeq (yes, $(HAS_NCURSESW))
LIBS_EXTERN		:=	ncursesw
else ifeq (yes, $(HAS_NCURSES))
LIBS_EXTERN		:=	ncurses
else
$(error No ncurses/ncursesw found)
endif

CPPFLAGS		:=	-D _XOPEN_SOURCE_EXTENDED=1


include				$(MAKEFILES_DIR)/config.mk
include				$(MAKEFILES_DIR)/build.mk
include				$(MAKEFILES_DIR)/doc.mk
include				$(MAKEFILES_DIR)/help.mk
