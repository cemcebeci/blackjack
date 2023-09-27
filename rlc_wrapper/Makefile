RLC=/home/ccebeci/rlc/rlc-infrastructure/rlc-debug/tool/rlc/rlc

all: bin/rlc_driver bin/c_driver bin/fuzzer_static_64 bin/runner_static_64 bin/fuzzer_static_4 bin/runner_static_4 bin/fuzzer_static_64 bin/runner_static_4 bin/fuzzer_dynamic bin/runner_dynamic

bin/runner_static_64: fuzz_targets/static_64_bits.cpp obj/class_to_global_functions.o obj/rlc_wrapper_nomain.o include/rlc_names.h
	clang++ fuzz_targets/static_64_bits.cpp obj/class_to_global_functions.o obj/rlc_wrapper_nomain.o -o bin/runner_static_64 

bin/fuzzer_static_64: fuzz_targets/static_64_bits.cpp obj/class_to_global_functions.o obj/rlc_wrapper_nomain.o include/rlc_names.h
	clang++ fuzz_targets/static_64_bits.cpp obj/class_to_global_functions.o obj/rlc_wrapper_nomain.o -o bin/fuzzer_static_64 -DFUZZING -fsanitize=fuzzer,address

bin/runner_static_4: fuzz_targets/static_4_bits.cpp obj/class_to_global_functions.o obj/rlc_wrapper_nomain.o include/rlc_names.h
	clang++ fuzz_targets/static_4_bits.cpp obj/class_to_global_functions.o obj/rlc_wrapper_nomain.o -o bin/runner_static_4 

bin/fuzzer_static_4: fuzz_targets/static_4_bits.cpp obj/class_to_global_functions.o obj/rlc_wrapper_nomain.o include/rlc_names.h
	clang++ fuzz_targets/static_4_bits.cpp obj/class_to_global_functions.o obj/rlc_wrapper_nomain.o -o bin/fuzzer_static_4 -DFUZZING -fsanitize=fuzzer,address

bin/runner_dynamic: fuzz_targets/dynamic.cpp obj/class_to_global_functions.o obj/rlc_wrapper_nomain.o include/rlc_names.h
	clang++ fuzz_targets/dynamic.cpp obj/class_to_global_functions.o obj/rlc_wrapper_nomain.o -o bin/runner_dynamic 

bin/fuzzer_dynamic: fuzz_targets/dynamic.cpp obj/class_to_global_functions.o obj/rlc_wrapper_nomain.o include/rlc_names.h
	clang++ fuzz_targets/dynamic.cpp obj/class_to_global_functions.o obj/rlc_wrapper_nomain.o -o bin/fuzzer_dynamic -DFUZZING -fsanitize=fuzzer,address

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