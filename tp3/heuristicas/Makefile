CC=g++
CFLAGS=-g -Wall -Werror -Iinclude/ -I../timer -lrt
LDFLAGS=-g -Wall -Werror -lrt
#EDIT THIS:
# ----- 8< ----- 8< ----- 8< ----- 8< ----- 8< ----- 
SOURCES= src/graph.cpp src/parser.cpp src/max_clique.cpp src/file_utils.cpp src/timer.cpp src/nodo.cpp 
BINARY=max_clique
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
