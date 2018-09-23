add_library(mpg123 STATIC
  compat.c
  compat.h
  parse.c
  parse.h
  frame.c
  format.c
  frame.h
  reader.h
  debug.h
  decode.h
  decode_2to1.c
  decode_4to1.c
  decode_ntom.c
  equalizer.c
  huffman.h
  icy.c
  icy.h
  icy2utf8.c
  icy2utf8.h
  id3.c
  id3.h
  true.h
  l2tables.h
  layer1.c
  layer2.c
  layer3.c
  getbits.h
  optimize.h
  optimize.c
  readers.c
  tabinit.c
  stringbuf.c
  libmpg123.c
  mpg123lib_intern.h
  mangle.h
  getcpuflags.h
  index.h
  index.c
  mpg123.h
  config.h
  dct64.c
  decode.c
  libmpg123.sym)

target_include_directories(mpg123 PUBLIC . ${SDL2_INCLUDE})

target_compile_definitions(mpg123 PRIVATE
  -DMPG123_NO_CONFIGURE
  -DOPT_GENERIC
  -DREAL_IS_FLOAT
  -D_CRT_SECURE_NO_WARNINGS)

target_link_libraries(mpg123 PUBLIC)

if(NOT BUILD_SHARED_LIBS)
  install(TARGETS mpg123 DESTINATION lib)
endif()
