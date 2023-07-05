# Fetch all files in current dir
file(GLOB FILES *.cpp)
add_library(quadrature-encoder-pico ${FILES})

# IMPORTANT define where to find the files when the lib is included from a different folder!
target_include_directories(quadrature-encoder-pico PUBLIC ../include)
