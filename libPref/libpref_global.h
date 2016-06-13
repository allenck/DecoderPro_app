#ifndef LIBPREF_GLOBAL_H
#define LIBPREF_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBPREF_LIBRARY)
#  define LIBPREFSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBPREFSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBPREF_GLOBAL_H
