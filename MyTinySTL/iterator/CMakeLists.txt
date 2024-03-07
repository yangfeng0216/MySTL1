FILE(GLOB source_file CONFIGURE_DEPENDS ./*.cpp )
add_library(iterator ${source_file})
target_include_directories(iterator PUBLIC .)
target_link_libraries(iterator PRIVATE utils)