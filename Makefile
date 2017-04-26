
source_dir=src
build_dir=build

compiler_libs=-lGL -lglfw -lGLEW
compiler_flags = -g --std=c++14 -Wall

source_files = $(wildcard $(source_dir)/*.cpp)
obj_files = $(patsubst src/%.cpp,obj/%.o,$(source_files))


$(build_dir)/game: $(obj_files)
	clang++ $(compiler_libs) -o $@ $^


obj/%.o: src/%.cpp
	g++ $(compiler_flags) -c -o $@ $<

all:
	clang++ -lGL -lglfw -lGLEW -g --std=c++14 -o game $(source_files) -Wall

production:
	clang++ -lSDL2 -g --std=c++14 -o renderer-production main.cpp -O3
	./renderer-production

run: all
	./game
