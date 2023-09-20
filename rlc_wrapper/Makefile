RLC=/home/ccebeci/rlc/rlc-infrastructure/rlc-debug/tool/rlc/rlc

all: bin/rlc_driver bin/c_driver bin/fuzzer bin/runner

bin/runner: fuzz_target.cpp obj/class_to_global_functions.o obj/rlc_wrapper_nomain.o include/rlc_names.h
	clang++ fuzz_target.cpp obj/class_to_global_functions.o obj/rlc_wrapper_nomain.o -o bin/runner 

bin/fuzzer: fuzz_target.cpp obj/class_to_global_functions.o obj/rlc_wrapper_nomain.o include/rlc_names.h
	clang++ fuzz_target.cpp obj/class_to_global_functions.o obj/rlc_wrapper_nomain.o -o bin/fuzzer -DFUZZING -fsanitize=fuzzer,address

bin/c_driver: obj/class_to_global_functions.o obj/driver.o obj/rlc_wrapper_nomain.o include/rlc_names.h
	clang++ obj/class_to_global_functions.o obj/driver.o obj/rlc_wrapper_nomain.o -o bin/c_driver

bin/rlc_driver: obj/class_to_global_functions.o obj/rlc_wrapper.o
	clang++ obj/class_to_global_functions.o obj/rlc_wrapper.o -o bin/rlc_driver

obj/class_to_global_functions.o: class_to_global_functions.cpp include/rlc_names.h
	clang++ -c class_to_global_functions.cpp -o obj/class_to_global_functions.o

include/rlc_names.h: rlc_wrapper.rl
	$(RLC) rlc_wrapper.rl --header -o include/rlc_names.h

obj/driver.o: driver.cpp
	clang++ -c driver.cpp -o obj/driver.o

obj/rlc_wrapper.o: rlc_wrapper.rl
	$(RLC) rlc_wrapper.rl -o obj/rlc_wrapper -O2 || true

obj/rlc_wrapper_nomain.o: rlc_wrapper.rl
	$(RLC) rlc_wrapper.rl -o obj/rlc_wrapper_nomain.o -O2 --compile

clean:
	rm bin/* obj/* include/*