RLC=/home/ccebeci/rlc/rlc-infrastructure/rlc-debug/tool/rlc/rlc

all: out/rlc_wrapper out/c_wrapper out/fuzzer out/runner

out/runner: fuzz_target.cpp out/class_to_global_functions.o out/rlc_wrapper_nomain.o include/rlc_names.h
	clang++ fuzz_target.cpp out/class_to_global_functions.o out/rlc_wrapper_nomain.o -o out/runner 

out/fuzzer: fuzz_target.cpp out/class_to_global_functions.o out/rlc_wrapper_nomain.o include/rlc_names.h
	clang++ fuzz_target.cpp out/class_to_global_functions.o out/rlc_wrapper_nomain.o -o out/fuzzer -DFUZZING -fsanitize=fuzzer,address

out/c_wrapper: out/class_to_global_functions.o out/driver.o out/rlc_wrapper_nomain.o include/rlc_names.h
	clang++ out/class_to_global_functions.o out/driver.o out/rlc_wrapper_nomain.o -o out/c_wrapper

out/rlc_wrapper: out/class_to_global_functions.o out/rlc_wrapper.o
	clang++ out/class_to_global_functions.o out/rlc_wrapper.o -o out/rlc_wrapper

out/class_to_global_functions.o: class_to_global_functions.cpp include/rlc_names.h
	clang++ -c class_to_global_functions.cpp -o out/class_to_global_functions.o

include/rlc_names.h: rlc_wrapper.rl
	$(RLC) rlc_wrapper.rl --header -o include/rlc_names.h

out/driver.o: driver.cpp
	clang++ -c driver.cpp -o out/driver.o

out/rlc_wrapper.o: rlc_wrapper.rl
	$(RLC) rlc_wrapper.rl -o out/rlc_wrapper -O2 || true

out/rlc_wrapper_nomain.o: rlc_wrapper.rl
	$(RLC) rlc_wrapper.rl -o out/rlc_wrapper_nomain.o -O2 --compile

clean:
	rm out/* include/*