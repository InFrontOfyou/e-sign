SNDR		=	sender
RCPNT		=	recipient
OUTEXT		=	out
SRCEXT		=	cpp
OBJEXT		=	o
LIB			=	math.cpp	\
				sha1.cpp	\
				rsa.cpp		\
				print.cpp	\
				read.cpp
LIBOBJ		=	$(LIB:%.$(SRCEXT)=%.$(OBJEXT))
SNDROBJ		=	$(SNDR:%=%.$(OBJEXT))
RCPNTOBJ	=	$(RCPNT:%=%.$(OBJEXT))
SRCDIR		=	src
OBJDIR		=	.$(OBJEXT)bj
LIBDIR		=	$(SRCDIR)/lib
HDRDIR		=	$(SRCDIR)/include
CFLAGS		+=	--std=c++11
CFLAGS		+=	-I $(HDRDIR)
CC			=	g++

vpath %.$(SRCEXT) $(SRCDIR)
vpath %.$(SRCEXT) $(LIBDIR)
vpath %.$(OBJEXT) $(OBJDIR)

all: $(SNDR:%=%.$(OUTEXT)) $(RCPNT:%=%.$(OUTEXT))

$(SNDR:%=%.$(OUTEXT)) $(RCPNT:%=%.$(OUTEXT)): %.$(OUTEXT): %.$(OBJEXT) $(LIBOBJ)
	@echo "Building out: $@"
	@$(CC) $(addprefix $(OBJDIR)/,$< $(LIBOBJ)) -o $@ $(CFLAGS)

$(SNDR:%=%.$(OBJEXT)) $(RCPNT:%=%.$(OBJEXT)) $(LIBOBJ): %.$(OBJEXT): %.$(SRCEXT) $(OBJDIR) $(HDR)
	@echo "Building object: $@"
	@$(CC) -c $< -o $(OBJDIR)/$@ $(CFLAGS)

$(OBJDIR):
	@mkdir $(OBJDIR)

clean:
	@echo "Removing objects"
	@rm -Rf $(OBJDIR)

fclean: clean
	@echo "Removing outs"
	@rm -Rf $(SNDR:%=%.$(OUTEXT))
	@rm -Rf $(RCPNT:%=%.$(OUTEXT))

re: fclean all
	
run: all $(DOC)
	DOC=$(DOC); ./$(SNDR:%=%.$(OUTEXT)) $$DOC | ./$(RCPNT:%=%.$(OUTEXT)) $$DOC

help:
	@echo "DOC=[document_name] make run"
