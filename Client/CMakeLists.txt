set(CLIENT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CLIENT_SRCS ${ENGINE_SRC} main.cpp Client.cpp Window/Window.cpp
        State/SHome/SHome.cpp State/SGame/SGame.cpp
        State/SCreate/SCreate.cpp State/SJoin/SJoin.cpp)

add_executable(r-type_client ${CLIENT_SRCS})

set_target_properties(r-type_client PROPERTIES LINKER_LANGUAGE CXX
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

target_link_libraries(r-type_client ${CONAN_LIBS})