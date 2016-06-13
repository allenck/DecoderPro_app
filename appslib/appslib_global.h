#ifndef APPSLIB_GLOBAL_H
#define APPSLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(APPSLIB_LIBRARY)
#  define APPSLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define APPSLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // APPSLIB_GLOBAL_H
