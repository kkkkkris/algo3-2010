CC=g++
#CFLAGS=-g -Wall -Werror -pedantic -Iinclude/
CFLAGS=-g -lrt -Wall -Werror -Iinclude/ 
#LDFLAGS=-g -Wall -Werror -pedantic
LDFLAGS=-g -lrt -Wall -Werror
#EDIT THIS:
# ----- 8< ----- 8< ----- 8< ----- 8< ----- 8< ----- 
SOURCES= src/ej1.cpp src/modulo.cpp src/parser.cpp src/file_utils.cpp src/timer.cpp
BINARY=modulo
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
