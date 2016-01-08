if("master" STREQUAL "")
  message(FATAL_ERROR "Tag for git checkout should not be empty.")
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E remove_directory "/home/yam/Documents/Jerome/IMAC/C++/Projet3D/Projet3D/build/third-party/assimp/test/gtest/src/gtest"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/home/yam/Documents/Jerome/IMAC/C++/Projet3D/Projet3D/build/third-party/assimp/test/gtest/src/gtest'")
endif()

execute_process(
  COMMAND "/usr/bin/git" clone "https://chromium.googlesource.com/external/googletest" "gtest"
  WORKING_DIRECTORY "/home/yam/Documents/Jerome/IMAC/C++/Projet3D/Projet3D/build/third-party/assimp/test/gtest/src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://chromium.googlesource.com/external/googletest'")
endif()

execute_process(
  COMMAND "/usr/bin/git" checkout master
  WORKING_DIRECTORY "/home/yam/Documents/Jerome/IMAC/C++/Projet3D/Projet3D/build/third-party/assimp/test/gtest/src/gtest"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'master'")
endif()

execute_process(
  COMMAND "/usr/bin/git" submodule init
  WORKING_DIRECTORY "/home/yam/Documents/Jerome/IMAC/C++/Projet3D/Projet3D/build/third-party/assimp/test/gtest/src/gtest"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to init submodules in: '/home/yam/Documents/Jerome/IMAC/C++/Projet3D/Projet3D/build/third-party/assimp/test/gtest/src/gtest'")
endif()

execute_process(
  COMMAND "/usr/bin/git" submodule update --recursive
  WORKING_DIRECTORY "/home/yam/Documents/Jerome/IMAC/C++/Projet3D/Projet3D/build/third-party/assimp/test/gtest/src/gtest"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/home/yam/Documents/Jerome/IMAC/C++/Projet3D/Projet3D/build/third-party/assimp/test/gtest/src/gtest'")
endif()

