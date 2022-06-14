protoc -I=./ --cpp_out=./ ./user.proto


./configure CXX=/usr/local/bin/g++-11
make -j8 CXX=/usr/local/bin/g++-11 CFLAGS=O3

g++ -std=c++20 main.cpp game.pb.cc `pkg-config --cflags --libs protobuf` -lpthread