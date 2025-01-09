# the name of the target operating system
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# which compilers to use
set(CMAKE_C_COMPILER /usr/bin/x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/x86_64-w64-mingw32-g++)

# target environment on the build host
set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32/sys-root/mingw)

# for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Qt6 specific settings
set(QT_QMAKE_EXECUTABLE /usr/x86_64-w64-mingw32/sys-root/mingw/bin/qmake6)
set(Qt6_DIR "/usr/x86_64-w64-mingw32/sys-root/mingw/lib/cmake/Qt6")
set(Qt6Core_DIR "/usr/x86_64-w64-mingw32/sys-root/mingw/lib/cmake/Qt6Core")
set(Qt6Gui_DIR "/usr/x86_64-w64-mingw32/sys-root/mingw/lib/cmake/Qt6Gui")
set(Qt6Widgets_DIR "/usr/x86_64-w64-mingw32/sys-root/mingw/lib/cmake/Qt6Widgets")
set(Qt6PrintSupport_DIR "/usr/x86_64-w64-mingw32/sys-root/mingw/lib/cmake/Qt6PrintSupport")

# Make sure CMake finds the Qt tools
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)