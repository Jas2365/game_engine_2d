# folders
build = build
src = src
include = -Iinclude
sprites = $(include)/sprites
collisions = $(include)/collisions

# files
src_files = $(wildcard $(src)/*.cpp)
sub_src_files = $(wildcard $(src)/**/*.cpp)

target =$(build)/main

# compilers, linkers and emulators
cxx = g++

# flags
cflags = -O2 -ld2d1 -lole32 -loleaut32 -luuid -static -lgdi32 -luser32 -municode -ldwrite

.PHONY: all build run clean  

all: build run

build: 
	$(cxx) $(include) $(sprites) $(collisions)  $(src_files) $(sub_src_files) -o $(target) $(cflags)

run:
	./$(target)

clean:
	rm $(target) 
