#!/usr/bin/zsh

if [ "$1" = "build" ] ; then
  rm -rf /build/{*,.*}
  mkdir -p build
  cd build
  cmake ..
  make clean
  make
  cd ..

elif [ -n "$1" ] ; then
  # print usage
  echo "Usage:     ./run.sh       - to run   the project"
  echo "           ./run.sh build - to build the project"

fi

# run the project
cd build
./source/PROJECT > image.ppm
pnmtopng image.ppm > ../result.png
rm image.ppm
cd ..



