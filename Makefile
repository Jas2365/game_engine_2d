# folders
build = build
src = src
include = -Iinclude

# files
src_files = $(wildcard $(src)/*.cpp)

target =$(build)/main

# compilers, linkers and emulators
cxx = g++

# flags
cflags = -O2 -ld2d1 -lole32 -loleaut32 -luuid -static -lgdi32 -luser32 -municode -ldwrite

.PHONY: all build run clean  

all: build run

build: 
	$(cxx) $(include) $(src_files) -o $(target) $(cflags)

run:
	./$(target)

clean:
	rm $(target) 
