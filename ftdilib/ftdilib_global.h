#ifndef FTDILIB_GLOBAL_H
#define FTDILIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FTDILIB_LIBRARY)
#  define FTDILIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FTDILIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FTDILIB_GLOBAL_H
