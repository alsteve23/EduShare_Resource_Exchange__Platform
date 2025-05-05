# Mínima versión requerida de CMake
cmake_minimum_required(VERSION 3.10)
# Nombre del proyecto
project(My_First_Big_Project)
# Establecer la versión del estándar de C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Agregar el ejecutable principal
add_executable(ResourceSystem
mainEntities/school.cpp
mainEntities/career.cpp
mainEntities/subject.cpp
mainEntities/resource.cpp
systemFunctions/ResourceSystem.cpp
)