
#ifndef HERMYGL_EXPORT_H
#define HERMYGL_EXPORT_H

#ifdef HERMYGL_STATIC_DEFINE
#  define HERMYGL_EXPORT
#  define HERMYGL_NO_EXPORT
#else
#  ifndef HERMYGL_EXPORT
#    ifdef HermyGL_EXPORTS
        /* We are building this library */
#      define HERMYGL_EXPORT 
#    else
        /* We are using this library */
#      define HERMYGL_EXPORT 
#    endif
#  endif

#  ifndef HERMYGL_NO_EXPORT
#    define HERMYGL_NO_EXPORT 
#  endif
#endif

#ifndef HERMYGL_DEPRECATED
#  define HERMYGL_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef HERMYGL_DEPRECATED_EXPORT
#  define HERMYGL_DEPRECATED_EXPORT HERMYGL_EXPORT HERMYGL_DEPRECATED
#endif

#ifndef HERMYGL_DEPRECATED_NO_EXPORT
#  define HERMYGL_DEPRECATED_NO_EXPORT HERMYGL_NO_EXPORT HERMYGL_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef HERMYGL_NO_DEPRECATED
#    define HERMYGL_NO_DEPRECATED
#  endif
#endif

#endif /* HERMYGL_EXPORT_H */
