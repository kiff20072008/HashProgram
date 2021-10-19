#!/bin/bash

if [ "$1x" = "Testx" ]; then
	Build_dir=build_test
	Release_type=Testing
else
	Build_dir=build
	Release_type=Release
fi

mkdir -p ${Build_dir}
cd ${Build_dir}

cmake -DCMAKE_BUILD_TYPE=${Release_type} ..
make -j