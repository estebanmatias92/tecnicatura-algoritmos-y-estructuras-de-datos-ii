# Agrega "shape.h" al conjunto de encabezados de la biblioteca de interfaz "geo".
target_sources(geo
    INTERFACE
        FILE_SET HEADERS

        # Define la carpeta base desde la que se organiza el encabezado.
        BASE_DIRS
            ${PROJECT_SOURCE_DIR}

        # Encabezado que se comparte con los objetivos que enlacen con "geo".
        FILES
            shape.h
)



#PRIVATE: is a private header of this library, a user doesn’t need to know about it. The same for files as they are only needed to compile the library, but a user doesn’t need them.info.h*.cpp
#PUBLIC: Any files added after is used for compiling the library and included for any other target that linking to this library.PUBLIC
#FILE_SET HEADERS BASE_DIRS ${PROJECT_SOURCE_DIR} FILES square.h: is a CMake 3.23 feature. We know to link to a library, we need its public headers. This line makes sure any other target linking to , gets aware of the header location. The base directory is droped from header file path so it will be accessible with a relative path. For example will be included as .geo/path/to/geometry/square/square.hsquare/square.h