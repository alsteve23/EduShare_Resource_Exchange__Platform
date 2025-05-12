cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(My_First_Big_Project)

# Estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Incluir directorios de cabeceras
include_directories(
    libraries
    mainEntities
    systemFunctions
)

# Archivos fuente
set(SOURCES
    libraries/sqlite3.c
    mainEntities/career.cpp
    mainEntities/resource.cpp
    mainEntities/school.cpp
    mainEntities/subject.cpp
    systemFunctions/ResourceSystem.cpp
)

# Crear el ejecutable
add_executable(My_First_Big_Project ${SOURCES})
