CC = gcc
CFLAGS = -std=c++03 -O3

default: struct

obj:
	g++ -Isrc  -std=c++03 -masm=intel -Wall -Wextra -O3 -DNDEBUG -o src/dispatch/executer.cpp.o -c src/dispatch/executer.cpp
	g++ -Isrc  -std=c++03 -masm=intel -Wall -Wextra -O3 -DNDEBUG -o src/main.cpp.o -c src/main.cpp
	g++ -Isrc  -std=c++03 -masm=intel -Wall -Wextra -O3 -DNDEBUG -o src/ssce/clock.cpp.o -c src/ssce/clock.cpp
	g++ -Isrc  -std=c++03 -masm=intel -Wall -Wextra -O3 -DNDEBUG -o src/ssce/cmd_parser.cpp.o -c src/ssce/cmd_parser.cpp
	g++ -Isrc  -std=c++03 -masm=intel -Wall -Wextra -O3 -DNDEBUG -o src/structures/array/utils.cpp.o -c src/structures/array/utils.cpp
	g++ -Isrc  -std=c++03 -masm=intel -Wall -Wextra -O3 -DNDEBUG -o src/structures/array/veclog.cpp.o -c src/structures/array/veclog.cpp
	g++ -Isrc  -std=c++03 -masm=intel -Wall -Wextra -O3 -DNDEBUG -o src/structures/avl/avl_implementation.cpp.o -c src/structures/avl/avl_implementation.cpp
	g++ -Isrc  -std=c++03 -masm=intel -Wall -Wextra -O3 -DNDEBUG -o src/structures/avl/avl_logic.cpp.o -c src/structures/avl/avl_logic.cpp
	g++ -Isrc  -std=c++03 -masm=intel -Wall -Wextra -O3 -DNDEBUG -o src/structures/dfs/dfs.cpp.o -c src/structures/dfs/dfs.cpp
	g++ -Isrc  -std=c++03 -masm=intel -Wall -Wextra -O3 -DNDEBUG -o src/structures/hash/hash_logic.cpp.o -c src/structures/hash/hash_logic.cpp
	g++ -Isrc  -std=c++03 -masm=intel -Wall -Wextra -O3 -DNDEBUG -o src/structures/hash/hash_set.cpp.o -c src/structures/hash/hash_set.cpp

struct: obj
	g++ src/dispatch/executer.cpp.o src/main.cpp.o src/ssce/clock.cpp.o src/ssce/cmd_parser.cpp.o src/structures/array/utils.cpp.o src/structures/array/veclog.cpp.o src/structures/avl/avl_implementation.cpp.o src/structures/avl/avl_logic.cpp.o src/structures/dfs/dfs.cpp.o src/structures/hash/hash_logic.cpp.o src/structures/hash/hash_set.cpp.o -o struct