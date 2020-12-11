#!/bin/bash

#Install RedisAI
if [[ -f ./RedisAI/install-cpu/redisai.so ]]; then
    echo "RedisAI CPU has already been downloaded and installed"
else
    if [[ ! -d "./RedisAI" ]]; then
        git clone --recursive https://github.com/RedisAI/RedisAI.git RedisAI
        cd RedisAI
        git checkout tags/v1.0.2
        cd ..
    else
        echo "RedisAI downloaded"
    fi
    cd RedisAI
    echo "Downloading RedisAI CPU dependencies"
    CC=gcc CXX=g++ bash get_deps.sh cpu
    echo "Building RedisAI v1.0.2"
    CC=gcc CXX=g++ ALL=1 make -C opt clean build GPU=0 WITH_PT=$1 WITH_TF=$2 WITH_TFLITE=$3 WITH_ORT=$4

    if [ -f "./install-cpu/redisai.so" ]; then
        echo "Finished installing RedisAI"
        cd ../
    else
        echo "ERROR: RedisAI failed to build"
        exit 1
    fi
fi
