#ifndef LIBPR3_GLOBAL_H
#define LIBPR3_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBPR3_LIBRARY)
#  define LIBPR3SHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBPR3SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBPR3_GLOBAL_H
