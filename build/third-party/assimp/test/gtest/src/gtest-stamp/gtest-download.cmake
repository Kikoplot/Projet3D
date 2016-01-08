

set(ENV{VS_UNICODE_OUTPUT} "")
set(command "/usr/bin/cmake;-P;/home/yam/Documents/Jerome/IMAC/C++/Projet3D/Projet3D/build/third-party/assimp/test/gtest/tmp/gtest-gitclone.cmake")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/home/yam/Documents/Jerome/IMAC/C++/Projet3D/Projet3D/build/third-party/assimp/test/gtest/src/gtest-stamp/gtest-download-out.log"
  ERROR_FILE "/home/yam/Documents/Jerome/IMAC/C++/Projet3D/Projet3D/build/third-party/assimp/test/gtest/src/gtest-stamp/gtest-download-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach(arg)
  set(msg "${msg}\nSee also\n  /home/yam/Documents/Jerome/IMAC/C++/Projet3D/Projet3D/build/third-party/assimp/test/gtest/src/gtest-stamp/gtest-download-*.log\n")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "gtest download command succeeded.  See also /home/yam/Documents/Jerome/IMAC/C++/Projet3D/Projet3D/build/third-party/assimp/test/gtest/src/gtest-stamp/gtest-download-*.log\n")
  message(STATUS "${msg}")
endif()
