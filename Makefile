LMXDIR = libmx
LMXA := $(LMXDIR)/libmx.a

MODELDIR = model
MODELA  := $(MODELDIR)/libmodel.a

NETWORKDIR = network
NETWORKA  := $(NETTWORKDIR)/libnetwork.a

CJSONDIR  = cjson
CJSONA   := $(CJSONDIR)/libcjson.a

SERVERDIR = server
SERVER = uchat_server

CLIENTDIR = client
CLIENT = uchat

all: install

install:
		if [ -f $(LMXA) ]; then echo "libmx exists" ; else make -sC $(LMXDIR); fi
		if [ -f $(MODELA) ]; then echo "libmodel exists" ; else make -sC $(MODELDIR); fi
		@make -sC $(NETWORKDIR) reinstall
		@make -sC $(CJSONDIR)
		@make -sC $(SERVERDIR)
		@make -sC $(CLIENTDIR)

		
#model and protocol

client:
		@make -sC $(CLIENTDIR)

server:
		@make -sC $(SERVERDIR)

$(LMXA):
		@make -sC $(LMXDIR)

$(SERVER):
		@make -sC $(SERVERDIR)

$(CLIENT):
		@make -sC $(CLIENTDIR)

uninstall:
	@make -sC $(CLIENTDIR) $@
	@make -sC $(SERVERDIR) $@
	@make -sC $(LMXDIR) $@
	@make -sC $(NETWORKDIR) $@
	@make -sC $(MODELDIR) $@
	@make -sC $(CJSONDIR) $@


reinstall: uninstall install