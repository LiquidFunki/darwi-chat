NAME = ../uchat
# CFLAGS = -std=c11 $(addprefix -W, extr error pedantic) `pkg-config --cflags --libs glib-2.0` -g

CFLAGS = -std=c11 `pkg-config --cflags --libs gtk+-3.0 glib-2.0` -w
COMP = clang

SRCDIR = src
INCDIR = inc
OBJDIR = obj

LMXDIR = ../libmx
LMXA := $(LMXDIR)/libmx.a
LMXINC := $(LMXDIR)/inc

MODELDIR = ../model
MODELINC = $(MODELDIR)/inc
MODELA = $(MODELDIR)/libmodel.a 

#network
NETWORKDIR = ../network
NETWORKINC = $(NETWORKDIR)/inc
NETWORKA = $(NETWORKDIR)/libnetwork.a

JSONDIR = ../cjson
JSONINC = $(JSONDIR)/inc
JSONA = $(JSONDIR)/libcjson.a


INCS = $(wildcard $(INCDIR)/*.h)
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:%.c=%.o)))

all: install

install: $(NAME)

$(NAME): $(OBJS)
	@clang $(OBJS) -L$(LMXDIR) -lmx -L$(MODELDIR) -lmodel -L$(NETWORKDIR) -lnetwork -L$(JSONDIR) -lcjson -lsqlite3 -o $@ $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCS)
	@clang -c $< -o $@ -I$(INCDIR) -I$(LMXINC) -I$(MODELINC) -I$(NETWORKINC) -I$(JSONINC) $(CFLAGS)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
		@mkdir -p $@

clean:
	@rm -rf $(OBJDIR)

uninstall: clean
	@rm -rf $(OBJDIR)
	@rm -rf $(NAME)

reinstall: uninstall install

