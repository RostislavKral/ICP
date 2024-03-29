# Authors: Lukas Jezek, Rostislav Kral
# název cíle
TARGET = pacman

# nastavení kompilátoru a jeho parametrů

CC = g++
CFLAGS = -g -Wall -std=c++17 $(shell pkg-config --cflags Qt5Widgets Qt5Core) -fPIC -I/usr/local/share/Qt-5.5.1/include
LFLAGS = $(shell pkg-config --libs Qt5Widgets Qt5Core) -I/usr/local/share/Qt-5.5.1/lib

# cesty k zdrojovým a hlavičkovým souborům
SRC_DIR = src
INC_DIR = $(SRC_DIR)
OBJ_DIR = obj
BIN_DIR = .

# vstupní a výstupní soubory
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
INCS = $(wildcard $(INC_DIR)/*.h)
DEPS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.d,$(SRCS))
BIN = $(BIN_DIR)/$(TARGET)

SRC_FILES_ZIP = $(wildcard $(SRC_DIR)/*)
ZIP_FILE = xkralr06-xjezek19.zip $(wildcard examples/*) $(wildcard images/*) README.md README.txt Makefile Doxyfile
ZIP_DEST_DIR = .

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
pack:
	# Create zip file and include source files and additional files
	zip $(ZIP_DEST_DIR)/$(ZIP_FILE) $(SRCS) $(INCS)

# generování Doxygen dokumentace
doxygen:
	doxygen Doxyfile

# smazání objektových souborů, spustitelného souboru a Doxygen dokumentace
clean:
	rm -rf $(OBJ_DIR) pacman doc

# kompilace + spuštění hry
run: $(BIN)
	./pacman
