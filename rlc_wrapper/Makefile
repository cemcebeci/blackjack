RLC=/home/ccebeci/rlc/rlc-infrastructure/rlc-debug/tool/rlc/rlc

all: wrapper

wrapper: out/class_to_global_functions.o out/rlc_wrapper.o
	clang++ out/class_to_global_functions.o out/rlc_wrapper.o -o out/wrapper

out/class_to_global_functions.o: class_to_global_functions.cpp include/rlc_names.h
	clang++ -c class_to_global_functions.cpp -o out/class_to_global_functions.o

include/rlc_names.h: rlc_wrapper.rl
	$(RLC) rlc_wrapper.rl --header -o include/rlc_names.h

out/rlc_wrapper.o: rlc_wrapper.rl
	$(RLC) rlc_wrapper.rl -o out/rlc_wrapper -O2 || true

clean:
	rm out/* include/*