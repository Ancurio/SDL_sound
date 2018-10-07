project(SDL_sound)
cmake_minimum_required(VERSION 3.1.2)

set(VERSION 1.0.1)
set(SOVERSION 1)

macro(doption name help default def)
  option(${name} ${help} ${default})
  if(${name})
    add_definitions(-D${def}=1)
  endif()
endmacro()

macro(make_simple_import name varname header library)
  add_library(${name} UNKNOWN IMPORTED)
  find_path(${varname}_INCLUDE ${header})
  find_library(${varname}_LIB NAMES ${library}-static ${library})
  set_target_properties(${name} PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${${varname}_INCLUDE}"
    IMPORTED_LOCATION "${${varname}_LIB}")
endmacro()

option(BUILD_SHARED_LIBS "build shared library" ON)
doption(ENABLE_VOC "enable VOC decoding" ON SOUND_SUPPORTS_VOC)
doption(ENABLE_WAV "enable WAV decoding" ON SOUND_SUPPORTS_WAV)
doption(ENABLE_RAW "enable RAW audio \"decoding\"" ON SOUND_SUPPORTS_RAW)
doption(ENABLE_AIFF "enable AIFF decoding" ON SOUND_SUPPORTS_AIFF)
doption(ENABLE_AU "enable AU decoding" ON SOUND_SUPPORTS_AU)
doption(ENABLE_SHN "enable SHN decoding" ON SOUND_SUPPORTS_SHN)
doption(ENABLE_MIDI "enable software MIDI music" ON SOUND_SUPPORTS_MIDI)
doption(ENABLE_MPG123 "enable MP3 decoding" ON SOUND_SUPPORTS_MPG123)
doption(ENABLE_MIKMOD "enable MOD decoding via mikmod" OFF SOUND_SUPPORTS_MIKMOD)
doption(ENABLE_MODPLUG "enable MOD decoding via modplug" OFF SOUND_SUPPORTS_MODPLUG)
doption(ENABLE_OGG "enable OGG decoding via libvorbis" OFF SOUND_SUPPORTS_OGG)
doption(ENABLE_FLAC "enable FLAG decoding via libFLAC" OFF SOUND_SUPPORTS_FLAC)
doption(ENABLE_SPEEX "enable SPX decoding via libspeex" OFF SOUND_SUPPORTS_SPEEX)
doption(ENABLE_PHYSFS "enable PhysicsFS in playsound" OFF SUPPORT_PHYSFS)
doption(STATIC_FLAC "FLAC should be linked as a static library" OFF FLAC__NO_DLL)

# SDL2
add_library(SDL2::SDL2 UNKNOWN IMPORTED)
find_path(SDL2_INCLUDE SDL.h PATH_SUFFIXES SDL2)
find_library(SDL2_LIB NAMES SDL2 SDL2d)
set_target_properties(SDL2::SDL2 PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${SDL2_INCLUDE}"
  IMPORTED_LOCATION "${SDL2_LIB}")
if(WIN32)
  set(libs user32 gdi32 winmm imm32 ole32 oleaut32 version uuid advapi32 shell32)
else()
  set(libs dl rt pthread m)
endif()
set_target_properties(SDL2::SDL2 PROPERTIES
  INTERFACE_LINK_LIBRARIES "${libs}")
unset(libs)

if(WIN32)
  add_library(SDL2::SDL2main UNKNOWN IMPORTED)
  set(libs)
  if(MINGW)
    list(APPEND libs mingw32)
  endif()
  find_library(SDL2MAIN_LIB NAMES SDL2main SDL2maind)
  list(APPEND libs "${SDL2MAIN_LIB}")
  set_target_properties(SDL2::SDL2main PROPERTIES
    IMPORTED_LOCATION "${SDL2MAIN_LIB}"
    INTERFACE_LINK_LIBRARIES "${libs}")
  unset(libs)
else()
  add_library(SDL2::SDL2main INTERFACE IMPORTED)
endif()

# mikmod
if(ENABLE_MIKMOD)
  make_simple_import(mikmod::mikmod MIKMOD mikmod.h mikmod)
endif()

# modplug
if(ENABLE_MODPLUG)
  make_simple_import(modplug::modplug MODPLUG modplug.h modplug)
endif()

# ogg
if(ENABLE_OGG OR ENABLE_FLAC OR ENABLE_SPEEX)
  make_simple_import(ogg::ogg OGG ogg/ogg.h ogg)
endif()

# ogg/vorbis
if(ENABLE_OGG)
  make_simple_import(ogg::vorbis VORBIS vorbis/codec.h vorbis)
  make_simple_import(ogg::vorbisfile VORBISFILE vorbis/vorbisfile.h vorbisfile)
endif()

# ogg/flac
if(ENABLE_FLAC)
  add_library(ogg::FLAC UNKNOWN IMPORTED)
  find_path(FLAC_INCLUDE FLAC/stream_decoder.h)
  find_library(FLAC_LIB NAMES flac FLAC)
  set_target_properties(ogg::FLAC PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${FLAC_INCLUDE}"
    IMPORTED_LOCATION "${FLAC_LIB}")
endif()

# ogg/speex
if(ENABLE_SPEEX)
  make_simple_import(ogg::speex SPEEX speex/speex.h speex)
endif()

# physfs
if(ENABLE_PHYSFS)
  make_simple_import(physfs::physfs PHYSFS physfs.h physfs)
endif()

# Build targets
include_directories(.)

add_library(SDL_sound
  SDL_sound.c
  SDL_sound_internal.h
  audio_convert.c
  extra_rwops.c
  extra_rwops.h)

add_subdirectory(decoders)

target_link_libraries(SDL_sound decoders SDL2::SDL2)
set_target_properties(SDL_sound PROPERTIES VERSION ${VERSION} SOVERSION ${SOVERSION})
target_include_directories(SDL_sound PUBLIC .)

add_subdirectory(playsound)

# pkg-config file
set(prefix "${CMAKE_INSTALL_PREFIX}")
set(exec_prefix "${CMAKE_INSTALL_PREFIX}")
set(libdir "${CMAKE_INSTALL_PREFIX}/lib")
set(includedir "${CMAKE_INSTALL_PREFIX}/include")
set(SDL_VERSION 2.0.0)
configure_file(SDL_sound.pc.in SDL_sound.pc)

# install
install(TARGETS SDL_sound DESTINATION lib)
install(FILES SDL_sound.h DESTINATION include/SDL2)
install(FILES SDL_sound.pc DESTINATION lib/pkgconfig)
