#!/bin/bash

install_dir="$PWD/wt_install"

sudo apt update

sudo apt install -y cmake g++ libboost-all-dev libssl-dev

wget -c https://github.com/emweb/wt/archive/4.10.4.tar.gz

tar -zxvf 4.10.4.tar.gz

cd wt-4.10.4

mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$install_dir" ..
make -j 8 # -I$install_dir/include
make install

cd ../..

rm -rf wt-4.10.4
rm 4.10.4.tar.gz

echo "Library Wt has been successfully installed in dir: $install_dir"