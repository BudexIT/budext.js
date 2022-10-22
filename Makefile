CC  = gcc
CXX = g++
G = Unix Makefiles
J = 10
BT = Release

usual: build-usual
	cmake --build ./build -j $(J)

build-usual:
	cmake -B ./build "-DCMAKE_C_COMPILER:FILEPATH=$(CC)" "-DCMAKE_CXX_COMPILER:FILEPATH=$(CXX)" "-DCMAKE_BUILD_TYPE=$(BT)" -G "$(G)"

clean:
	git clean -d -f -x ./build