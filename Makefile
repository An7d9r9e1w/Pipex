SRCDIR := srcs
BNSDIR := srcs_bonus
CMMDIR := srcs_common
INCDIR := incs
OBJDIR := objs
DEPDIR := $(OBJDIR)/.deps
LIBDIR := libft

CMMS := $(wildcard $(CMMDIR)/*.c)
SRCS := $(wildcard $(SRCDIR)/*.c) $(CMMS)
BNSS := $(wildcard $(BNSDIR)/*.c) $(CMMS)
OBJS := $(addprefix $(OBJDIR)/,$(notdir $(SRCS:%.c=%.o)))
BOBJS := $(addprefix $(OBJDIR)/,$(notdir $(BNSS:%.c=%.o)))
LIBFT := $(LIBDIR)/libft.a

NAME := pipex

CC := gcc
CFLAGS := -Wall -Wextra -Werror -I $(INCDIR) -I $(LIBDIR)
DEPFLAGS = -MT $@ -MMD -MF $(DEPDIR)/$*.tmpd
COMPILE.c = $(CC) $(CFLAGS)  $(DEPFLAGS) -c -o
POSTCOMPILE = mv -f $(DEPDIR)/$*.tmpd $(DEPDIR)/$*.d && touch $@
LINK.c = $(CC) $(CFLAGS) -o

MKDIR = mkdir -p $@
RM := rm -rf


#---------------------------------------------------------------------------#

all: makelib $(NAME)

bonus: $(BOBJS) | makelib
	$(LINK.c) $(NAME) $^ $(LIBFT)

$(NAME): $(LIBFT) $(OBJS)
	$(LINK.c) $@ $^

$(OBJDIR)/%.o: */%.c $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE.c) $@ $<
	@$(POSTCOMPILE)

$(DEPDIR):
	@$(MKDIR)

makelib:
	@$(MAKE) -C $(LIBDIR)

DEPS := $(addprefix $(DEPDIR)/,$(notdir $(SRCS:%.c=%.d)))	\
		$(addprefix $(DEPDIR)/,$(notdir $(CMMS:%.c=%.d)))	\
		$(addprefix $(DEPDIR)/,$(notdir $(BNSS:%.c=%.d)))
$(DEPS):
include $(wildcard $(DEPS))

clean:
	$(RM) $(OBJDIR)
	$(MAKE) -C $(LIBDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBDIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus makelib





#	              .,-:;//;:=,
#	          . :H@@@MM@M#H/.,+%;,
#	       ,/X+ +M@@M@MM%=,-%HMMM@X/,
#	     -+@MM; $M@@MH+-,;XMMMM@MMMM@+-
#	    ;@M@@M- XM@X;. -+XXXXXHHH@M@M#@/.
#	  ,%MM@@MH ,@%=             .---=-=:=,.
#	  =@#@@@MX.,                -%HX$$%%%:;
#	 =-./@M@M$                   .;@MMMM@MM:
#	 X@/ -$MM/                    . +MM@@@M$
#	,@M@H: :@:                    . =X#@@@@-
#	,@@@MMX, .                    /H- ;@M@M=
#	.H@@@@M@+,                    %MM+..%#$.
#	 /MMMM@MMH/.                  XM@MH; =;
#	  /%+%$XHH@$=              , .H@@@@MX,
#	   .=--------.           -%H.,@@@@@MX,
#	   .%MM@@@HHHXX$$$%+- .:$MMX =M@@MM%.
#	     =XMMM@MM@MM#H;,-+HMM@M+ /MMMX=
#	       =%@M@M#@$-.=$@MM@@@M; %M%=
#	         ,:+$+-,/H#MMMMMMM@= =,
#	               =++%%%%+/:-.
