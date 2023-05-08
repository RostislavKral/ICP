# název cíle
TARGET = pacman

# nastavení kompilátoru a jeho parametrů
CC = g++
CFLAGS = -Wall -std=c++17 $(shell pkg-config --cflags Qt5Widgets) -fPIC
LFLAGS = $(shell pkg-config --libs Qt5Widgets)

# cesty k zdrojovým a hlavičkovým souborům
SRC_DIR = src
INC_DIR = $(SRC_DIR)
OBJ_DIR = obj
BIN_DIR = bin

# vstupní a výstupní soubory
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
INCS = $(wildcard $(INC_DIR)/*.h)
DEPS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.d,$(SRCS))
BIN = $(BIN_DIR)/$(TARGET)

# výchozí cíl
all: $(BIN)

# kompilace všech zdrojových souborů
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# linkování všech objektových souborů do spustitelného souboru
$(BIN): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) $(LFLAGS) -o $(BIN)

# vytvoření archivu se zdrojovými soubory
archive:
	mkdir -p archive
	tar -cvzf archive/$(TARGET).tar.gz $(SRC_DIR) $(INCS) Makefile

# generování Doxygen dokumentace
doc:
	doxygen Doxyfile

# smazání objektových souborů, spustitelného souboru a Doxygen dokumentace
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) doc
