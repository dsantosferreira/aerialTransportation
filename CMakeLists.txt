cmake_minimum_required(VERSION 3.24)
project(aerialTransportation)

set(CMAKE_CXX_STANDARD 17)

add_executable(aerialTransportation src/main.cpp src/Graph.h src/Graph.cpp src/Airline.h src/Airline.cpp src/Program.h src/Program.cpp src/Database.h src/Database.cpp src/Airport.cpp src/Airport.h)
