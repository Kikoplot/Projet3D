

set(command "/usr/bin/cmake;-P;/home/jeremie/Documents/IMAC2/Projet3D/build/third-party/assimp/test/gtest/tmp/gtest-gitclone.cmake")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/home/jeremie/Documents/IMAC2/Projet3D/build/third-party/assimp/test/gtest/src/gtest-stamp/gtest-download-out.log"
  ERROR_FILE "/home/jeremie/Documents/IMAC2/Projet3D/build/third-party/assimp/test/gtest/src/gtest-stamp/gtest-download-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /home/jeremie/Documents/IMAC2/Projet3D/build/third-party/assimp/test/gtest/src/gtest-stamp/gtest-download-*.log\n")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "gtest download command succeeded.  See also /home/jeremie/Documents/IMAC2/Projet3D/build/third-party/assimp/test/gtest/src/gtest-stamp/gtest-download-*.log\n")
  message(STATUS "${msg}")
endif()
