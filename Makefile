flags = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations \
-Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts \
-Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal \
-Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op \
-Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self \
-Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 \
-Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override \
-Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast \
-Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast \
-Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow \
-flto-odr-type-merging -fno-omit-frame-pointer -Wstack-usage=8192 -pie -fPIE -Werror=vla \
-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

#-------------------------------------------------------------------------------------------------------#

# all: mandelbrot.out
# 	./mandelbrot.out
#
# #mondelbrot: main.o
# #g++ main.o $(flags) -o mondelbrot
#
# #mondelbrot:	main.cpp
# #g++ -c $(flags) main.cpp -o main.out -lsfml-window -lsfml-system
#
# mandelbrot.out: main.o
# 	g++ main.o mandelbrot.out -lsfml-graphics -lsfml-window -lsfml-system
#
# main.o: main.cpp
# 	g++ -c -O3 main.cpp
#
# clean:
# 	rm -rf *.o *.exe *.exe.log *.exe.log.dmp

all: mandelbrot

mandelbrot: main.cpp mandelbrot.h
	g++ main.cpp -o mandelbrot.out -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -rf *.o *.out

run:
	./mandelbrot.out
