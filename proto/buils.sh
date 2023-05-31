#protoc -I=./ --cpp_out=./ ./user.proto

# ./configure CXX=/opt/homebrew/Cellar/gcc/13.1.0/bin/g++-13
# cmake -DCMAKE_BUILD_TYPE=Release
# make -j8 CXX=/opt/homebrew/Cellar/gcc/13.1.0/bin/g++-13 CFLAGS=-Ofast

#g++ -std=c++20 main.cpp game.pb.cc `pkg-config --cflags --libs protobuf` -lpthread