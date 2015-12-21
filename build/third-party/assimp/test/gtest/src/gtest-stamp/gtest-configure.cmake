

set(ENV{VS_UNICODE_OUTPUT} "")
set(command "/usr/bin/cmake;-DCMAKE_BUILD_TYPE=;-Dgtest_force_shared_crt=ON;-Dgtest_disable_pthreads:BOOL=OFF;-GUnix Makefiles;/home/yam/Documents/Jerome/IMAC/C++/Projet3D/Projet3D/build/third-party/assimp/test/gtest/src/gtest")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/home/yam/Documents/Jerome/IMAC/C++/Projet3D/Projet3D/build/third-party/assimp/test/gtest/src/gtest-stamp/gtest-configure-out.log"
  ERROR_FILE "/home/yam/Documents/Jerome/IMAC/C++/Projet3D/Projet3D/build/third-party/assimp/test/gtest/src/gtest-stamp/gtest-configure-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach(arg)
  set(msg "${msg}\nSee also\n  /home/yam/Documents/Jerome/IMAC/C++/Projet3D/Projet3D/build/third-party/assimp/test/gtest/src/gtest-stamp/gtest-configure-*.log\n")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "gtest configure command succeeded.  See also /home/yam/Documents/Jerome/IMAC/C++/Projet3D/Projet3D/build/third-party/assimp/test/gtest/src/gtest-stamp/gtest-configure-*.log\n")
  message(STATUS "${msg}")
endif()
