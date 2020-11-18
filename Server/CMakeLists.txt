set(SERVER_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(SERVER_SRCS ${ENGINE_SRC} main.cpp Server.cpp Room/Room.cpp)

add_executable(r-type_server ${SERVER_SRCS})

set_target_properties(r-type_server PROPERTIES LINKER_LANGUAGE CXX
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

target_link_libraries(r-type_server ${CONAN_LIBS})

target_include_directories(r-type_client PUBLIC ${ENGINE_DIR})