# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.69])

AC_INIT([SDL_sound],[1.0.3],[Ryan C. Gordon <icculus@icculus.org>])

dnl ---------------------------------------------------------------------
dnl System/version info
dnl ---------------------------------------------------------------------

# Making releases:
#   MICRO_VERSION += 1;
#   INTERFACE_AGE += 1;
#   BINARY_AGE += 1;
# if any functions have been added, set INTERFACE_AGE to 0.
# if backwards compatibility has been broken,
# set BINARY_AGE and INTERFACE_AGE to 0.

MAJOR_VERSION=1
MINOR_VERSION=0
MICRO_VERSION=1
INTERFACE_AGE=0
BINARY_AGE=0
VERSION=$MAJOR_VERSION.$MINOR_VERSION.$MICRO_VERSION

AC_SUBST(MAJOR_VERSION)
AC_SUBST(MINOR_VERSION)
AC_SUBST(MICRO_VERSION)
AC_SUBST(INTERFACE_AGE)
AC_SUBST(BINARY_AGE)
AC_SUBST(VERSION)

# libtool versioning
LT_RELEASE=$MAJOR_VERSION.$MINOR_VERSION
LT_CURRENT=`expr $MICRO_VERSION - $INTERFACE_AGE`
LT_REVISION=$INTERFACE_AGE
LT_AGE=`expr $BINARY_AGE - $INTERFACE_AGE`

AC_SUBST(LT_RELEASE)
AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION)
AC_SUBST(LT_AGE)

dnl Detect the canonical host and target build environment
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

dnl Setup for automake
AC_CONFIG_SRCDIR([SDL_sound.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS(config.h)
AM_INIT_AUTOMAKE([1.15 foreign -Wall])

dnl ---------------------------------------------------------------------
dnl Compilers and other tools
dnl ---------------------------------------------------------------------

AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AM_PROG_AR
AM_PROG_AS
PKG_PROG_PKG_CONFIG
LT_INIT(win32-dll)

dnl ---------------------------------------------------------------------
dnl Debug mode?
dnl ---------------------------------------------------------------------

AC_ARG_ENABLE([debug],
	AS_HELP_STRING([--enable-debug], [Enable debug mode [default=no]]),
	[enable_debug=yes],[enable_debug=no])
AS_IF([test x$enable_debug = xyes], [
	AS_IF([test x$ac_cv_prog_cc_g = xyes], [
		AX_APPEND_COMPILE_FLAGS([-g -O0],[CFLAGS])], [
		AX_APPEND_COMPILE_FLAGS([-O0],[CFLAGS])
	])
	AX_APPEND_COMPILE_FLAGS([-Werror],[CFLAGS])
	AC_DEFINE([DEBUG],[1],[Define for debug builds.])
	AC_DEFINE([DEBUG_CHATTER],[1],[Define for debug build chattering.])
	], [
	AC_DEFINE([NDEBUG],[1],[Define to disable debugging])
])

dnl ---------------------------------------------------------------------
dnl Have GCC's -fvisibility option?
dnl ---------------------------------------------------------------------

gl_VISIBILITY()
AS_IF([test x$gl_cv_cc_visibility = xyes], [
	AX_APPEND_COMPILE_FLAGS([$CFLAGS_VISIBILITY],[CFLAGS])
])

dnl ---------------------------------------------------------------------
dnl Checks for libraries.
dnl ---------------------------------------------------------------------

dnl Check for voc decoder inclusion...
AC_ARG_ENABLE([voc],
	AS_HELP_STRING([--enable-voc], [enable VOC decoding [default=yes]]),
	[],[enable_voc=yes])
AS_IF([test x$enable_voc = xyes], [
	AC_DEFINE([SOUND_SUPPORTS_VOC],[1],[Define if VOC support is desired])
])

dnl Check for wav decoder inclusion...
AC_ARG_ENABLE([wav],
	AS_HELP_STRING([--enable-wav], [enable WAV decoding [default=yes]]),
	[],[enable_wav=yes])
AS_IF([test x$enable_wav = xyes], [
	AC_DEFINE([SOUND_SUPPORTS_WAV],[1],[Define if WAV support is desired])
])

dnl Check for raw decoder inclusion...
AC_ARG_ENABLE([raw],
	AS_HELP_STRING([--enable-raw], [enable raw audio "decoding" [default=yes]]),
	[],[enable_raw=yes])
AS_IF([test x$enable_raw = xyes], [
	AC_DEFINE([SOUND_SUPPORTS_RAW],[1],[Define if RAW support is desired])
])

dnl Check for aiff decoder inclusion...
AC_ARG_ENABLE([aiff],
	AS_HELP_STRING([--enable-aiff], [enable AIFF decoding [default=yes]]),
	[],[enable_aiff=yes])
AS_IF([test x$enable_aiff = xyes], [
	AC_DEFINE([SOUND_SUPPORTS_AIFF],[1],[Define if AIFF support is desired])
])

dnl Check for au decoder inclusion
AC_ARG_ENABLE([au],
	AS_HELP_STRING([--enable-au], [enable AU decoding [default=yes]]),
	[],[enable_au=yes])
AS_IF([test x$enable_au = xyes], [
	AC_DEFINE([SOUND_SUPPORTS_AU],[1],[Define if AU support is desired.])
])

dnl Check for shn decoder inclusion...
AC_ARG_ENABLE([shn],
	AS_HELP_STRING([--enable-shn], [enable SHN decoding [default=yes]]),
	[],[enable_shn=yes])
AS_IF([test x$enable_shn = xyes], [
	AC_DEFINE([SOUND_SUPPORTS_SHN],[1],[Define if SHN support is desired.])
])

dnl Check for the MIDI decoder...
AC_ARG_ENABLE([midi],
	AS_HELP_STRING([--enable-midi], [enable software MIDI music [default=yes]]]),
	[],[enable_midi=yes])
AS_IF([test x$enable_midi = xyes], [
	AC_DEFINE([SOUND_SUPPORTS_MIDI],[1],[Define if MIDI support is desired.])
])

dnl Check for the MP3 decoder...
AC_ARG_ENABLE([mpg123],
	AS_HELP_STRING([--enable-mpg123], [enable MP3 decoding [default=yes]]),
	[],[enable_mpg123=yes])
AS_IF([test x$enable_mpg123 = xyes], [
	AC_DEFINE([SOUND_SUPPORTS_MPG123],[1],[Define if MPG123 support is desired.])
])

dnl Check for libmikmod
PKG_CHECK_MODULES([MIKMOD],[libmikmod],[mikmod_found=yes],[mikmod_found=false])
AC_ARG_ENABLE([mikmod],
	AS_HELP_STRING([--enable-mikmod],[enable MOD decoding via mikmod [default=yes]]),
	[],[enable_mikmod=yes])
AS_IF([test x$enable_mikmod = xyes], [
	AS_IF([test x$mikmod_found = xyes], [
		AC_DEFINE([SOUND_SUPPORTS_MIKMOD],[1],[Define if mikmod support is desired])
		AX_APPEND_LINK_FLAGS([$MIKMOD_LIBS],[LIBS])
	], [
		AC_MSG_NOTICE([*** mikmod requested but not found!])
	])
])

dnl Check for libmodplug
PKG_CHECK_MODULES([MODPLUG],[libmodplug],[modplug_found=yes],[modplug_found=no])
AC_ARG_ENABLE([modplug],
	AS_HELP_STRING([--enable-modplug],[enable MOD decoding via modplug [default=yes]]),
	[],[enable_modplug=yes])
AC_CHECK_HEADER([modplug.h], [have_modplug_h=yes],[have_modplug_h=no])
AS_IF([test x$have_modplug_h = xno], [
       AC_CHECK_HEADER([libmodplug/modplug.h],[have_libmodplug_modplug_h=yes])])
AS_IF([test x$enable_modplug = xyes], [
	AS_IF([test x$modplug_found = xyes], [
		AC_DEFINE([SOUND_SUPPORTS_MODPLUG],[1],[Define if MODPLUG support is desired])
		AX_APPEND_LINK_FLAGS([$MODPLUG_LIBS],[LIBS])
		AX_APPEND_COMPILE_FLAGS([$MODPLUG_CFLAGS],[CFLAGS])
		AS_IF([test x$have_libmodplug_modplug_h = xyes], [
			AC_DEFINE([SOUND_MODPLUG_IN_OWN_PATH],[1],[Define if modplug header is in own directory])
		])
	], [
		AC_MSG_NOTICE([*** modplug support requested but not found! ***])
	])
])

dnl Check for Ogg Vorbis
PKG_CHECK_MODULES([OGG],[ogg],[ogg_found=yes],[ogg_found=no])
PKG_CHECK_MODULES([VORBIS],[vorbis],[vorbis_found=yes],[vorbis_found=no])
PKG_CHECK_MODULES([VORBISFILE],[vorbisfile],[vorbisfile_found=yes],[vorbis_found=no])
AC_ARG_ENABLE([vorbis],
	AS_HELP_STRING([--enable-vorbis],[enable OGG decoding via libvorbis [default=yes]]),
	[],[enable_vorbis=yes])
AS_IF([test x$enable_vorbis = xyes], [
	AS_IF([test x$ogg_found = xyes -a x$vorbis_found = xyes -a x$vorbisfile_found = xyes ], [
		AC_DEFINE([SOUND_SUPPORTS_OGG],[1],[Define if OGG support is desired.])
		AX_APPEND_LINK_FLAGS([$OGG_LIBS $VORBIS_LIBS $VORBISFILE_LIBS],[LIBS])
		AX_APPEND_COMPILE_FLAGS([$OGG_CFLAGS $VORBIS_CFLAGS $VORBISFILE_LIBS],[CFLAGS])
	], [
		AC_MSG_NOTICE([*** vorbis requested but not found! ***])
	])
])

dnl Check for FLAC
PKG_CHECK_MODULES([FLAC],[ flac >= 1.0.4 ],[flac_found=yes],[flac_found=no])
AC_ARG_ENABLE([flac],
	AS_HELP_STRING([--enable-flac],[enable FLAC decoding via libFLAC [default=yes]]),
	[],[enable_flac=yes])
AS_IF([test x$enable_flac = xyes], [
	AS_IF([test x$flac_found = xyes -a x$ogg_found = xyes], [
		AC_DEFINE([SOUND_SUPPORTS_FLAC],[1],[Define if FLAC support is desired.])
		AX_APPEND_LINK_FLAGS([$FLAC_LIBS $OGG_LIBS],[LIBS])
		AX_APPEND_COMPILE_FLAGS([$FLAC_CFLAGS $OGG_CFLAGS],[CFLAGS])
	], [
		AC_MSG_NOTICE([*** FLAC requested but not found! ***])
	])
])

dnl Check for speex
PKG_CHECK_MODULES([SPEEX],[speex],[speex_found=yes],[speex_found=no])
AC_ARG_ENABLE([speex],
	AS_HELP_STRING([--enable-speex],[enable SPX decoding via libspeex [default=yes]]),
	[],[enable_speex=yes])
AS_IF([test x$enable_speex = xyes], [
	AS_IF([test x$speex_found = xyes -a x$ogg_found = xyes], [
		AC_DEFINE([SOUND_SUPPORTS_SPEEX],[1],[Define if SPEEX support is desired])
		AX_APPEND_LINK_FLAGS([$OGG_LIBS $SPEEX_LIBS],[LIBS])
	], [
		AC_MSG_NOTICE([*** speex requested but not found ***])
	])
])

dnl Check for PhysicsFS http://icculus.org/physfs/
PKG_CHECK_MODULES([PHYSFS],[physfs],[physfs_found=yes],[physfs_found=no])
AC_ARG_ENABLE([physfs],
	AS_HELP_STRING([--enable-physfs],[enable PhysicsFS in playsound [default=yes]]),
	[],[enable_physfs=yes])
AS_IF([test x$enable_physfs = xyes], [
	AS_IF([test x$physfs_found = xyes], [
		enable_physfs="yes"
		AX_APPEND_COMPILE_FLAGS([-DSUPPORT_PHYSFS],[PHYSFS_CFLAGS])
	], [
		enable_physfs="no"
	])
])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h signal.h assert.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_SIZE_T

# Checks for library functions.

AC_FUNC_MEMCMP
AC_CHECK_FUNCS([malloc memset strrchr setbuf])

dnl Check for SDL2
dnl Moved here because the -Dmain=SDL_main in SDL_CFLAGS throws
dnl off quite a lot of other autotools flags.
PKG_CHECK_MODULES([SDL],[sdl2],[sdl_found=yes],[sdl_found=no])
AC_CHECK_LIB(SDL2, SDL_Init, have_sdl=yes)
AS_IF([test x$sdl_found = xyes -a x$have_sdl = xyes], [
	AX_APPEND_LINK_FLAGS([-lSDL2],[LIBS])
	AX_APPEND_COMPILE_FLAGS([$SDL_CFLAGS],[CFLAGS])
	AC_SUBST([SDL_VERSION])
], [
	AC_MSG_ERROR([*** SDL2 required! ***])
])

AX_APPEND_COMPILE_FLAGS([-D_REENTRANT -D_THREAD_SAFE],[CFLAGS])

dnl Add Makefile conditionals
AM_CONDITIONAL(USE_TIMIDITY, test x$enable_midi = xyes)
AM_CONDITIONAL(USE_LIBMPG123, test x$enable_mpg123 = xyes)
AM_CONDITIONAL(USE_PHYSICSFS, test x$enable_physfs = xyes)

AC_CONFIG_FILES([
	Makefile
	decoders/Makefile
	decoders/timidity/Makefile
	decoders/libmpg123/Makefile
	playsound/Makefile
	SDL_sound.pc
])
AC_OUTPUT
