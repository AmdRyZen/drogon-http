#protoc -I=./ --cpp_out=./ ./user.proto

# ./configure CXX=/usr/local/bin/g++-11
# cmake -DCMAKE_BUILD_TYPE=Release
# make -j8 CXX=/usr/local/bin/g++-11 CFLAGS=-Ofast

#g++ -std=c++20 main.cpp game.pb.cc `pkg-config --cflags --libs protobuf` -lpthread