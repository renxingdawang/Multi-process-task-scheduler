#!/bin/bash

# 检查build目录是否存在，存在则删除
[ -d build ] && rm -rf build

# 创建build目录并执行构建
mkdir build && cd build && cmake .. && make
