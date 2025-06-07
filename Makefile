include				$(shell git rev-parse --show-toplevel)/build/setup.mk


# ***************************** CONFIGURATION ******************************** #

NAME			:=	ft_shmup
MSG_PROGRESS	:=	"👾"
MSG_USAGE		?=	"Usage: ./$(NAME)"
COLOR_MAKE		=	$(STY_MAG)


#	Dependencies

LIBS_LOCAL		=	$(LIB_ROOT_DIR)/libftpp/libftpp.a \
					$(LIB_ROOT_DIR)/libft/libft.a
LIBS_EXTERN		:=	ncursesw


include				$(MAKEFILES_DIR)/config.mk
include				$(MAKEFILES_DIR)/build.mk
include				$(MAKEFILES_DIR)/doc.mk
include				$(MAKEFILES_DIR)/help.mk
