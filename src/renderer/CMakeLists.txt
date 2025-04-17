file(GLOB SRC "*.cpp" "*.mm")

add_library(renderer ${SRC})

target_link_libraries(renderer "-framework Cocoa" "-framework QuartzCore" "-framework Metal")
