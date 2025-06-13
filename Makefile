include				$(shell git rev-parse --show-toplevel)/build/setup.mk


# ***************************** CONFIGURATION ******************************** #

NAME			:=	ft_shmup
MSG_PROGRESS	:=	"👾"
MSG_USAGE		?=	"Usage: ./$(NAME)"
COLOR_MAKE		=	$(STY_MAG)


#	Dependencies

LIBS_LOCAL		=	$(LIB_ROOT_DIR)/libftpp/libftpp.a \
					$(LIB_ROOT_DIR)/libft/libft.a

#	macOS
ifeq ($(shell uname), Darwin)

ifneq (, $(wildcard /usr/local/opt/ncurses/lib))
LDFLAGS			:=	-L/usr/local/opt/ncurses/lib
endif
ifneq (, $(wildcard /usr/local/opt/ncurses/lib/ncursesw))
LIBS_EXTERN		:=	ncursesw
else
LIBS_EXTERN		:=	ncurses
endif

else

LIBS_EXTERN		:=	ncursesw

endif

CPPFLAGS		:=	-D _XOPEN_SOURCE_EXTENDED=1


include				$(MAKEFILES_DIR)/config.mk
include				$(MAKEFILES_DIR)/build.mk
include				$(MAKEFILES_DIR)/doc.mk
include				$(MAKEFILES_DIR)/help.mk
