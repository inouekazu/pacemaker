/*
 * Copyright 2001-2021 the Pacemaker project contributors
 *
 * The version control history for this file may have further details.
 *
 * This source code is licensed under the GNU Lesser General Public License
 * version 2.1 or later (LGPLv2.1+) WITHOUT ANY WARRANTY.
 */
#ifndef PORTABILITY_H
#  define PORTABILITY_H

/* Needs to be defined before any other includes, otherwise some system
 * headers do not behave as expected! Major black magic... */
#  undef _GNU_SOURCE            /* in case it was defined on the command line */
#  define _GNU_SOURCE

/* Please leave this as the first #include - Solaris needs it there */
#  ifdef HAVE_CONFIG_H
#    ifndef PCMK__CONFIG_H
#      define PCMK__CONFIG_H
#      include <config.h>
#    endif
#  endif

/* Prototypes for libreplace functions */

#  ifndef HAVE_DAEMON
  /* We supply a replacement function, but need a prototype */
int daemon(int nochdir, int noclose);
#  endif                        /* HAVE_DAEMON */

#  ifndef HAVE_SETENV
  /* We supply a replacement function, but need a prototype */
int setenv(const char *name, const char *value, int why);
#  endif                        /* HAVE_SETENV */

#  ifndef HAVE_STRERROR
  /* We supply a replacement function, but need a prototype */
char *strerror(int errnum);
#  endif                        /* HAVE_STRERROR */

#  ifndef HAVE_STRCHRNUL
  /* We supply a replacement function, but need a prototype */
char *strchrnul(const char *s, int c_in);
#  endif                        /* HAVE_STRCHRNUL */

#  ifndef HAVE_ALPHASORT
#    include <dirent.h>
int
 alphasort(const void *dirent1, const void *dirent2);
#  endif                        /* HAVE_ALPHASORT */

#  ifndef HAVE_STRNLEN
size_t strnlen(const char *s, size_t maxlen);
#  else
#    	define USE_GNU
#  endif

#  ifndef HAVE_STRNDUP
char *strndup(const char *str, size_t len);
#  else
#    	define USE_GNU
#  endif

#  if SUPPORT_DBUS
#    ifndef HAVE_DBUSBASICVALUE
#      include <stdint.h>
#      include <dbus/dbus.h>
/**
 * An 8-byte struct you could use to access int64 without having
 * int64 support
 */
typedef struct
{
  uint32_t first32;  /**< first 32 bits in the 8 bytes (beware endian issues) */
  uint32_t second32; /**< second 32 bits in the 8 bytes (beware endian issues) */
} DBus8ByteStruct;

/**
 * A simple value union that lets you access bytes as if they
 * were various types; useful when dealing with basic types via
 * void pointers and varargs.
 *
 * This union also contains a pointer member (which can be used
 * to retrieve a string from dbus_message_iter_get_basic(), for
 * instance), so on future platforms it could conceivably be larger
 * than 8 bytes.
 */
typedef union
{
  unsigned char bytes[8]; /**< as 8 individual bytes */
  int16_t  i16;   /**< as int16 */
  uint16_t u16;   /**< as int16 */
  int32_t  i32;   /**< as int32 */
  uint32_t u32;   /**< as int32 */
  uint32_t bool_val; /**< as boolean */
#      ifdef DBUS_HAVE_INT64
  int64_t  i64;   /**< as int64 */
  uint64_t u64;   /**< as int64 */
#      endif
  DBus8ByteStruct eight; /**< as 8-byte struct */
  double dbl;          /**< as double */
  unsigned char byt;   /**< as byte */
  char *str;           /**< as char* (string, object path or signature) */
  int fd;              /**< as Unix file descriptor */
} DBusBasicValue;
#    endif
#  endif

/* Replacement error codes for non-linux */
#  include <errno.h>

#  ifndef ENOTUNIQ
#    define ENOTUNIQ  190
#  endif

#  ifndef ECOMM
#    define ECOMM     191
#  endif

#  ifndef ELIBACC
#    define ELIBACC   192
#  endif

#  ifndef EREMOTEIO
#    define EREMOTEIO 193
#  endif

#  ifndef EUNATCH
#    define EUNATCH   194
#  endif

#  ifndef ENOKEY
#    define ENOKEY    195
#  endif

#  ifndef ENODATA
#    define ENODATA   196
#  endif

#  ifndef ETIME
#    define ETIME     197
#  endif

#  ifndef ENOSR
#    define ENOSR     198
#  endif

#  ifndef ENOSTR
#    define ENOSTR    199
#  endif

#  ifndef EKEYREJECTED
#    define EKEYREJECTED 200
#  endif

#endif                          /* PORTABILITY_H */
