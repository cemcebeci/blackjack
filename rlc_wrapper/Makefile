RLC=/home/ccebeci/rlc/rlc-infrastructure/rlc-debug/tool/rlc/rlc

all: wrapper

wrapper: out/class_to_global_functions.o out/rlc_wrapper.o
	clang++ out/class_to_global_functions.o out/rlc_wrapper.o -o out/wrapper

out/class_to_global_functions.o: class_to_global_functions.cpp
	clang++ -c class_to_global_functions.cpp -o out/class_to_global_functions.o

out/rlc_wrapper.o: rlc_wrapper.rl
	$(RLC) rlc_wrapper.rl -o out/rlc_wrapper || true

clean:
	rm out/*