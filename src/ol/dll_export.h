//
//
//
#pragma warning ( disable : 4251 )

#ifndef _WIN32
#   define OLQT_EXPORT
#else
#   if defined(OLQT_STATIC)
#       define OLQT_EXPORT
#   elif defined(olqt_EXPORTS)
#       define OLQT_EXPORT __declspec(dllexport)
#   else
#       define OLQT_EXPORT __declspec(dllimport)
#   endif
#endif

