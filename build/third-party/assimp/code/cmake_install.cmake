# Install script for directory: /home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.3.2.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.3"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      FILE(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    ENDIF()
  ENDFOREACH()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/jeremie/Documents/IMAC2/Projet3D/build/third-party/assimp/code/libassimp.so.3.2.0"
    "/home/jeremie/Documents/IMAC2/Projet3D/build/third-party/assimp/code/libassimp.so.3"
    "/home/jeremie/Documents/IMAC2/Projet3D/build/third-party/assimp/code/libassimp.so"
    )
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.3.2.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.3"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "${file}")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDFOREACH()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "assimp-dev")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/anim.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/ai_assert.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/camera.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/color4.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/color4.inl"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/config.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/defs.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/cfileio.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/light.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/material.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/material.inl"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/matrix3x3.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/matrix3x3.inl"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/matrix4x4.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/matrix4x4.inl"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/mesh.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/postprocess.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/quaternion.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/quaternion.inl"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/scene.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/metadata.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/texture.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/types.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/vector2.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/vector2.inl"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/vector3.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/vector3.inl"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/version.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/cimport.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/importerdesc.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/Importer.hpp"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/DefaultLogger.hpp"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/ProgressHandler.hpp"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/IOStream.hpp"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/IOSystem.hpp"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/Logger.hpp"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/LogStream.hpp"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/NullLogger.hpp"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/cexport.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/Exporter.hpp"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "assimp-dev")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "assimp-dev")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/Compiler/poppack1.h"
    "/home/jeremie/Documents/IMAC2/Projet3D/project/third-party/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "assimp-dev")

