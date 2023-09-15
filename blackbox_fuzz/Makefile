CC=clang++

all: fuzzer runner

fuzzer: fuzz_target.cpp
	clang++ fuzz_target.cpp -o fuzzer -DFUZZING -fsanitize=fuzzer,address

runner: fuzz_target.cpp
	clang++ fuzz_target.cpp -o runner