set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")

file(GLOB SRC
    "${SRC_DIR}/*.cpp"
)

file(GLOB INC
    "${SRC_DIR}/*.h"
)

add_executable(Server ${SRC} ${INC})

install(TARGETS Server RUNTIME DESTINATION bin)

enable_testing()
add_test(NAME Server COMMAND Server)