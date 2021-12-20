TARGETS = atest

#CC = gcc
CFLAGS = -g0 -O0 -Wall -g

# auto generate dependency files
CFLAGS += -MMD

.PHONY: default all clean info Debug cleanDebug

default: $(TARGETS)
all: default
Debug: all
cleanDebug: clean

LIBS =
SOURCES     = $(wildcard *.c)
OBJECTS     = $(patsubst %.c, %.o, $(SOURCES))
MAINOBJS    = $(patsubst %, %.o,$(TARGETS))
LINKOBJECTS = $(filter-out $(MAINOBJS), $(OBJECTS))
DEPS        = $(OBJECTS:.o=.d)

# include dependencies if they exist
-include $(DEPS)

%.o: %.c
	@echo -n "compiling $@ "
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo ""

.PRECIOUS: $(TARGETS) $(ALLOBJECTS)

$(TARGETS): $(OBJECTS)
	@echo -n "linking $@ $(LIBS)"
	@$(CC) $@.o $(LINKOBJECTS) -Wall $(LIBS) -o $@
	@echo ""


build: clean all

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGETS)
	-rm -f $(DEPS)

info:
	@echo "    TARGETS: $(TARGETS)"
	@echo "    SOURCES: $(SOURCES)"
	@echo "    OBJECTS: $(OBJECTS)"
	@echo "LINKOBJECTS: $(LINKOBJECTS)"
	@echo "   MAINOBJS: $(MAINOBJS)"
	@echo "       DEPS: $(DEPS)"
	@echo "         CC: $(CC)"
	@echo "     CFLAGS: $(CFLAGS)"
	@echo "       LIBS: $(LIBS)"
