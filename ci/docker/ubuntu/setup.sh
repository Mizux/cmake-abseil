#!/usr/bin/env bash

set -x
apt-get update -q
apt-get install -yq git wget build-essential cmake
#wget https://cmake.org/files/v3.10/cmake-3.10.2-Linux-x86_64.sh && \
#chmod a+x cmake-3.10.2-Linux-x86_64.sh && \
#./cmake-3.10.2-Linux-x86_64.sh --prefix=/usr/local/ --skip-license && \
#rm cmake-3.10.2-Linux-x86_64.sh

