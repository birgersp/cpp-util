set -e

make -f cpp-util.mak -j8 test

./bin/cpp-util-test

make -f cpp-util.mak -j executable
