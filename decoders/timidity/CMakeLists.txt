add_library(timidity STATIC
  common.c
  common.h
  dls1.h
  dls2.h
  instrum.c
  instrum.h
  instrum_dls.c
  instrum_dls.h
  mix.c
  mix.h
  options.h
  output.c
  output.h
  playmidi.c
  playmidi.h
  readmidi.c
  readmidi.h
  resample.c
  resample.h
  tables.c
  tables.h
  timidity.c
  timidity.h)


target_include_directories(timidity PUBLIC . "${SDL2_INCLUDE}")

target_compile_definitions(timidity PRIVATE
  -D_CRT_SECURE_NO_WARNINGS)

target_link_libraries(timidity PUBLIC)

if(NOT BUILD_SHARED_LIBS)
  install(TARGETS timidity DESTINATION lib)
endif()
