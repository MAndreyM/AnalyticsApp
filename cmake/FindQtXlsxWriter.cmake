# FindQtXlsxWriter.cmake
find_path(QtXlsxWriter_INCLUDE_DIR
    NAMES QtXlsx/xlsxdocument.h
    PATHS /usr/local/include
          /usr/include
          ${CMAKE_INSTALL_PREFIX}/include
)

find_library(QtXlsxWriter_LIBRARY
    NAMES QtXlsxWriter
    PATHS /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          ${CMAKE_INSTALL_PREFIX}/lib
)

if(QtXlsxWriter_INCLUDE_DIR AND QtXlsxWriter_LIBRARY)
    set(QtXlsxWriter_FOUND TRUE)
    set(QtXlsxWriter_INCLUDE_DIRS ${QtXlsxWriter_INCLUDE_DIR})
    set(QtXlsxWriter_LIBRARIES ${QtXlsxWriter_LIBRARY})
    
    if(NOT TARGET QtXlsx::Writer)
        add_library(QtXlsx::Writer UNKNOWN IMPORTED)
        set_target_properties(QtXlsx::Writer PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${QtXlsxWriter_INCLUDE_DIR}"
            IMPORTED_LOCATION "${QtXlsxWriter_LIBRARY}"
        )
    endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(QtXlsxWriter
    REQUIRED_VARS QtXlsxWriter_LIBRARY QtXlsxWriter_INCLUDE_DIR
)