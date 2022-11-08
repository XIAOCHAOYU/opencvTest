# CMakeList.txt: CMakeProject2 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)


#设置C++的版本，关键字 CMAKE_CXX_STANDARD
set(CMAKE_CXX_STANDARD 17)

MESSAGE(STATUS "----- START opencv_Img -----")


#路径设置

set(USE_VCPKG  TRUE)



if(USE_VCPKG)
    if (WIN32)
        MESSAGE(STATUS "-----Win32 VCPKG")
        set(VCPKG_ROOT "D:/Apply/VCPKG/vcpkg/scripts/buildsystems/vcpkg.cmake")
    endif()
    
    set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT})
    #D:/Apply/VCPKG/vcpkg/installed/x86-windows/share/opencv4
    set(OpencvDir D:/Apply/VCPKG/vcpkg/packages/opencv4_x64-windows/share/opencv)
    list(APPEND CMAKE_PREFIX_PATH ${OpencvDir})



endif()





########################-----Project------#################


project(CMakeProject2 VERSION 0.1.0)



#project ("CMakeProject2")



#########################----EXE的名字-----#################


# 将源代码添加到此项目的可执行文件。
add_executable (CMakeProject2 "CMakeProject2.cpp" "CMakeProject2.h")


#库的设置
############################# OpenCV #############################
find_package(OpenCV REQUIRED)

target_link_libraries(CMakeProject2 PRIVATE ${OpenCV_LIBS})
