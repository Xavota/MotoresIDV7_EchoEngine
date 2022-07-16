enable_testing()



file(GLOB sources src/*.cpp)


add_executable(eeUtilities_UnitTest ${sources})

target_include_directories(eeUtilities_UnitTest PUBLIC include)
include(GoogleTest)


target_link_libraries(eeUtilities_UnitTest PUBLIC eeUtilities googletest)