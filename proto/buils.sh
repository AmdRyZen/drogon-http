#protoc -I=./ --cpp_out=./ ./user.proto

# ./configure CXX=/opt/homebrew/Cellar/gcc/14.1.0_1/bin/g++-14
# cmake -DCMAKE_BUILD_TYPE=Release
# make -j8 CXX=/opt/homebrew/Cellar/gcc/14.1.0_1/bin/g++-14 CFLAGS=-Ofast

#g++ -std=c++20 main.cpp game.pb.cc `pkg-config --cflags --libs protobuf` -lpthread