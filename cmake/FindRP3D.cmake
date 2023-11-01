# - Try to find RP3D
# Once done, this will define
#
# RP3D_FOUND - system has RP3D
# RP3D_INCLUDE_DIR - the RP3D include directories
# RP3D_LIBRARIES - link these to use RP3D
FIND_PATH( RP3D_INCLUDE_DIR reactphysics3d/reactphysics3d.h
        /usr/include
        /usr/local/include
        /opt/local/include
        "${CMAKE_SOURCE_DIR}/include"
)
FIND_LIBRARY( RP3D_LIBRARY reactphysics3d
        /usr/lib64
        /usr/lib
        /usr/local/lib
        /opt/local/lib
        "${CMAKE_SOURCE_DIR}/lib"
)
IF(RP3D_INCLUDE_DIR AND RP3D_LIBRARY)
    SET( RP3D_FOUND TRUE )
    SET( RP3D_LIBRARIES ${RP3D_LIBRARY} )
ENDIF(RP3D_INCLUDE_DIR AND RP3D_LIBRARY)
IF(RP3D_FOUND)
    IF(NOT RP3D_FIND_QUIETLY)
        MESSAGE(STATUS "Found RP3D: ${RP3D_LIBRARY}")
    ENDIF(NOT RP3D_FIND_QUIETLY)
ELSE(RP3D_FOUND)
    IF(RP3D_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find libRP3D")
    ENDIF(RP3D_FIND_REQUIRED)
ENDIF(RP3D_FOUND)
