compile-and-run:
	cd build && make || exit 1
	./build/guiHannah

test:
	cmake -S . -B build
	cmake --build build
	cd build && ctest --output-on-failure


