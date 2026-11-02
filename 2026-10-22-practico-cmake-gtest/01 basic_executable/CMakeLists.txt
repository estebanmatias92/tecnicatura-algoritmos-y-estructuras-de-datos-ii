# Establece que se requiere como mínimo la versión 3.20 de CMake para procesar este archivo.
cmake_minimum_required(VERSION 3.20)

# Define el nombre del proyecto como "geometry" e indica explícitamente que solo se usará el lenguaje C++ (CXX), evitando que CMake pierda tiempo buscando un compilador de C puro.
project(geometry LANGUAGES CXX)

# Redefine el proyecto "geometry" con la configuración por defecto (habilita tanto C como C++); esta línea está repetida respecto a la anterior y podrías borrarla sin problema.
project(geometry)

# Declara que se va a crear un archivo ejecutable llamado "app" (en CMake moderno se puede declarar vacío aquí y asignarle los archivos fuente en la línea siguiente).
add_executable(app)

# Asigna los archivos que componen el ejecutable "app". "PRIVATE" indica que estos archivos (app.cpp, shape.cpp y shape.h) se usan únicamente para compilar "app" y no se heredan a otros objetivos.
target_sources(app PRIVATE app.cpp shape.cpp shape.h)

# Define la regla de instalación para que, cuando ejecutes "make install" (o "cmake --install"), el binario compilado "app" se copie al directorio de programas del sistema (por ejemplo, /usr/local/bin).
install(TARGETS app)


#add_executable(): used to declare the executable target, . You can choose any other name instead of .appapp
#target_sources(): we add source files necessary to compile target.app
#PRIVATE: to say that sources are just for creating target and nothing else.app
#install(): will copy the compiled executable into when you run