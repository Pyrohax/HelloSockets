set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")

file(GLOB_RECURSE SRC
    "${SRC_DIR}/*.cpp"
)

file(GLOB_RECURSE INC
    "${SRC_DIR}/*.h"
)

add_executable(Server ${SRC} ${INC})

install(TARGETS Server RUNTIME DESTINATION bin)