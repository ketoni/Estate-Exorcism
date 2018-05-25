
EXECUTABLE = EstateExorcism

SOURCE_PATH = src
INCLUDE_PATH = include

CC = clang++-3.8
CFLAGS = -c -g -Wall -std=c++14 -I$(INCLUDE_PATH) -MMD -MP
LFLAGS = -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system -lsfml-network

SOURCES = $(wildcard $(SOURCE_PATH)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
DEPENDS = $(addprefix $(SOURCE_PATH)/.,$(subst .o,.cpp.dep,$(notdir $(OBJECTS))))

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -MF $(SOURCE_PATH)/.$(notdir $<).dep $< -o $@

.PHONY: clean
clean:
	rm -f $(EXECUTABLE) $(OBJECTS) $(DEPENDS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

debug: $(EXECUTABLE)
	gdb ./$(EXECUTABLE)

memtest: $(EXECUTABLE)
	valgrind ./$(EXECUTABLE)


-include $(DEPENDS)
