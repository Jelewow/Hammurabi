cmake_minimum_required(VERSION 3.19)
project(Hammurabi_v2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Hammurabi_v2 main.cpp Core/Headers/GameFramework.h Core/Sources/GameFramework.cpp Core/Headers/PlayerStats.h Core/Headers/Core.h Core/Headers/InputInfo.h Core/Sources/Core.cpp Core/Headers/ValidateInfo.h Core/Headers/RoundInfo.h Core/Headers/Saver.h Core/Sources/Saver.cpp Core/Sources/PlayerStats.cpp Core/Sources/RoundInfo.cpp)