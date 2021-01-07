
/* Define if .align takes 3 for alignment of 2^3=8 bytes instead of 8. */
/* #undef ASMALIGN_EXP */

/* Define if __attribute__((aligned(16))) shall be used */
/* #undef CCALIGN */

/* Define if checking of stack alignment is wanted. */
#define CHECK_ALIGN 1

/* Define if debugging is enabled. */
/* #undef DEBUG */

/* The default audio output module(s) to use */
#define DEFAULT_OUTPUT_MODULE "alsa,oss,esd,pulse,sdl,nas,arts"

/* Define if building with dynamcally linked libmpg123 */
#define DYNAMIC_BUILD 1

/* Define if FIFO support is enabled. */
#define FIFO 1

/* Define if frame index should be used. */
#define FRAME_INDEX 1

/* Define if gapless is enabled. */
#define GAPLESS 1

/* size of the frame index seek table */
#define INDEX_SIZE 1000

/* Define if IPV6 support is enabled. */
#define IPV6 1

/* Define if network support is enabled. */
#define NETWORK 1

/* Name of package */
#define PACKAGE "mpg123"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "mpg123-devel@lists.sourceforge.net"

/* Define to the full name of this package. */
#define PACKAGE_NAME "mpg123"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "mpg123 1.6.4"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "mpg123"

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.6.4"

/* Define if portaudio v18 API is wanted. */
/* #undef PORTAUDIO18 */

/* The size of `long', as computed by sizeof. */
/*#define SIZEOF_LONG sizeof (long)*/

/* The size of `off_t', as computed by sizeof. */
/*#define SIZEOF_OFF_T sizeof (off_t)*/

/* The size of `size_t', as computed by sizeof. */
/*#define SIZEOF_SIZE_T sizeof (size_t)*/

/* The size of `ssize_t', as computed by sizeof. */
/*#define SIZEOF_SSIZE_T sizeof (ssize_t)*/

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define if modules are enabled */
#define USE_MODULES 1

/* Version number of package */
#define VERSION "1.6.4"

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to `long int' if <sys/types.h> does not define. */
/* #undef off_t */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef ssize_t */
