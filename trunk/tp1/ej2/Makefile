CC=g++
CFLAGS=-g -Wall -Werror -Iinclude/
LDFLAGS=-g
#EDIT THIS:
# ----- 8< ----- 8< ----- 8< ----- 8< ----- 8< ----- 
SOURCES= src/graph.cpp src/parser.cpp src/ronda.cpp src/file_utils.cpp
BINARY=ronda
# ----- 8< ----- 8< ----- 8< ----- 8< ----- 8< ----- 
OBJECTS=$(SOURCES:src/%.cpp=.bin/%.o)


all: $(BINARY)

#target for the executable
$(BINARY): deps $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)

#generate folder .bin for the objects
$(OBJECTS): .bin

.bin:
	mkdir .bin

#generate every target and its depdencies.
deps: Makefile
	$(CC) $(CFLAGS) -MM $(SOURCES) > $@
	sed -i 's/.*\.o/.bin\/&/g' $@
	echo >> $@
	sed -i ':a;N;$$!ba;s/\\\n //g' $@
	sed -i ':a;N;$$!ba;s_\n_\n\t$(CC) $(CFLAGS) -c $$< -o $$@\n_g' $@
-include deps 
	
clean:
	rm -f deps $(BINARY) $(OBJECTS)

new: clean all
