CC=g++
CFLAGS=-g -lrt -Wall -Werror -Iinclude/ 
LDFLAGS=-g -lrt -Wall -Werror
#EDIT THIS:
# ----- 8< ----- 8< ----- 8< ----- 8< ----- 8< ----- 
SOURCES=src/file_utils.cpp src/graph.cpp src/parser.cpp src/timer.cpp src/bfs.cpp
BINARY=bfs
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
