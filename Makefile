TARGET := tst

SRC := main.cpp
SRC += $(wildcard src/*.cpp)
 
HDR := $(wildcard src/*.h)

OBJ := main.o
OBJ += $(patsubst src/%.cpp, obj/%.o, $(wildcard src/*.cpp))

# GCC := arm-linux-gnueabihf-g++
GCC := g++

CFLAGS := -g3 -Wall

LDFLAG := -lpthread

all : $(TARGET)
	
%.o : %.cpp $(HDR)
	$(GCC) -c $< -o $@ $(CFLAGS) -I ./src/

obj/%.o : src/%.cpp $(HDR)
	$(GCC) -c $< -o $@ $(CFLAGS) -I ./src/
	

$(TARGET) : $(OBJ)
	$(GCC) -o $(TARGET) $(OBJ) $(LDFLAG)

clean:
	rm -f $(TARGET)
	rm -f $(OBJ)

