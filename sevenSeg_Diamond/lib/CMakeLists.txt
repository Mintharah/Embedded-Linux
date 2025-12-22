add_library(StreamLib 
src/GPIO.cpp 
src/iStream.cpp 
src/sevenSegmentOutput.cpp 
src/Terminal.cpp)

target_include_directories(StreamLib 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/private
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/interface
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
