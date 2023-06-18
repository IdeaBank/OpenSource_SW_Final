cmake_minimum_required(VERSION 3.25)
project(TicTacToe_CPP)

set(CMAKE_CXX_STANDARD 17)

add_executable(TicTacToe_CPP main.cpp AlignType.h constant/Constants.h model/BoardData.cpp model/BoardData.h util/OSDependent.cpp view/BoardView.cpp view/BoardView.h util/headers.h controller/BoardController.cpp controller/BoardController.h)