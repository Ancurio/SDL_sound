add_library(decoders STATIC
  aiff.c
  au.c
  coreaudio.c
  flac.c
  midi.c
  mikmod.c
  modplug.c
  mpg123.c
  ogg.c
  raw.c
  shn.c
  speex.c
  voc.c
  wav.c)

if(ENABLE_MIDI)
  add_subdirectory(timidity)
  target_link_libraries(decoders PUBLIC timidity)
endif()

if(ENABLE_MPG123)
  add_subdirectory(libmpg123)
  target_link_libraries(decoders PUBLIC mpg123)
endif()

if(ENABLE_MIKMOD)
  target_link_libraries(decoders PUBLIC mikmod::mikmod)
endif()

if(ENABLE_MODPLUG)
  target_link_libraries(decoders PUBLIC modplug::modplug)
endif()

# ogg/flac
if(ENABLE_FLAC)
  target_link_libraries(decoders PUBLIC ogg::FLAC)
endif()

# ogg/vorbis
if(ENABLE_OGG)
  target_link_libraries(decoders PUBLIC ogg::vorbisfile ogg::vorbis)
endif()

# ogg/speex
if(ENABLE_SPEEX)
  target_link_libraries(decoders PUBLIC ogg::speex)
endif()

# ogg
if(ENABLE_OGG OR ENABLE_FLAC OR ENABLE_SPEEX)
  target_link_libraries(decoders PUBLIC ogg::ogg)
endif()

# physfs
if(ENABLE_PHYSFS)
  target_link_libraries(decoders PUBLIC physfs::physfs)
endif()

if(NOT BUILD_SHARED_LIBS)
  install(TARGETS decoders DESTINATION lib)
endif()
