set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")

file(GLOB SRC
    "${SRC_DIR}/*.cpp"
)

file(GLOB INC
    "${SRC_DIR}/*.h"
)

add_executable(Client ${SRC} ${INC})

install(TARGETS Client RUNTIME DESTINATION bin)

enable_testing()
add_test(NAME Client COMMAND Client)