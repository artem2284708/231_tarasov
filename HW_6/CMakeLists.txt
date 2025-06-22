cmake_minimum_required(VERSION 3.22)
project(HW6 C)

set(CMAKE_C_STANDARD 99)

add_executable(HW6 endless.c proc.c killn.c catchsig.c childctl.c)
