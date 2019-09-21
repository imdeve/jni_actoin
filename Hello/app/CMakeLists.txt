
cmake_minimum_required(VERSION 3.4.1)

aux_source_directory(./callbacks CALL_BACKS)
aux_source_directory(./task TASK_SRC)
aux_source_directory(./sdkout SDKOUT_SRC)
aux_source_directory(./clog  CLOG_SRC)
aux_source_directory(./testexample2  TEST_EXAMPLE_SRC)

include_directories(./callbacks)
include_directories(./sdkout)
include_directories(./task)


add_library( # Sets the name of the library.
             jnithread

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/native-lib.cpp
             src/main/cpp/WlListener.cpp
             ${TASK_SRC}
             ${SDKOUT_SRC}
             ${CLOG_SRC}
             ${TEST_EXAMPLE_SRC}
             ${CALL_BACKS}
        )


find_library( # Sets the name of the path variable.
              log-lib
              log )


target_link_libraries( # Specifies the target library.
                       jnithread

                       ${log-lib} )