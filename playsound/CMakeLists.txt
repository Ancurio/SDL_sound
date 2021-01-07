add_executable(playsound
  playsound.c
  physfsrwops.c
  physfsrwops.h)
target_link_libraries(playsound SDL2::SDL2main SDL_sound)

add_executable(playsound_simple
  playsound_simple.c)
target_link_libraries(playsound_simple SDL2::SDL2main SDL_sound)

if(ENABLE_PHYSFS)
  target_link_libraries(playsound physfs::physfs)
  target_link_libraries(playsound_simple physfs::physfs)
endif()
