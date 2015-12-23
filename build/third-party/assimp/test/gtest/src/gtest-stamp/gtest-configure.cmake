

set(command "/usr/bin/cmake;-DCMAKE_BUILD_TYPE=;-Dgtest_force_shared_crt=ON;-Dgtest_disable_pthreads:BOOL=OFF;-GUnix Makefiles;/home/jeremie/Documents/IMAC2/Projet3D/build/third-party/assimp/test/gtest/src/gtest")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/home/jeremie/Documents/IMAC2/Projet3D/build/third-party/assimp/test/gtest/src/gtest-stamp/gtest-configure-out.log"
  ERROR_FILE "/home/jeremie/Documents/IMAC2/Projet3D/build/third-party/assimp/test/gtest/src/gtest-stamp/gtest-configure-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /home/jeremie/Documents/IMAC2/Projet3D/build/third-party/assimp/test/gtest/src/gtest-stamp/gtest-configure-*.log\n")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "gtest configure command succeeded.  See also /home/jeremie/Documents/IMAC2/Projet3D/build/third-party/assimp/test/gtest/src/gtest-stamp/gtest-configure-*.log\n")
  message(STATUS "${msg}")
endif()
