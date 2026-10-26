# TODO: Remove magic string
cd ../../build-bench/benchmark/RelWithDebInfo/ || exit
./dieharderSFMT 10000
cd ../../../benchmark/files || exit
dieharder -a -f sfmt.dat