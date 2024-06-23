CXX=g++
CXXFLAGS=-std=c++14 -O3 -ggdb -Wall -w -lm -g

SRCDIR=src
OBJDIR=obj

# Lista de archivos fuente (excluyendo los archivos main_*.cpp)
SRCS=$(filter-out $(SRCDIR)/main_%.cpp, $(wildcard $(SRCDIR)/*.cpp))

# Lista de archivos objeto generados a partir de los archivos fuente (excluyendo main_*.o)
OBJS=$(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

# Archivos fuente principales
MAIN_SRCS=$(SRCDIR)/main_normal.cpp $(SRCDIR)/main_gap.cpp $(SRCDIR)/main_huffman.cpp

# Archivos objeto principales
MAIN_OBJS=$(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(MAIN_SRCS))

TARGET1=normal
TARGET2=gap
TARGET3=huffman

all: $(TARGET1) $(TARGET2) $(TARGET3)

$(TARGET1): $(OBJS) $(OBJDIR)/main_normal.o
	$(CXX) -o $@ $(OBJS) $(OBJDIR)/main_normal.o $(CXXFLAGS)

$(TARGET2): $(OBJS) $(OBJDIR)/main_gap.o
	$(CXX) -o $@ $(OBJS) $(OBJDIR)/main_gap.o $(CXXFLAGS)

$(TARGET3): $(OBJS) $(OBJDIR)/main_huffman.o
	$(CXX) -o $@ $(OBJS) $(OBJDIR)/main_huffman.o $(CXXFLAGS)

# Regla de compilación para los archivos fuente en src/
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	rm -f $(TARGET1) $(TARGET2) $(TARGET3)
	rm -f $(OBJDIR)/*.o
	rm -f *~
