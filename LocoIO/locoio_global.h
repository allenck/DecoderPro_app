#ifndef LOCOIO_GLOBAL_H
#define LOCOIO_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LOCOIO_LIBRARY)
#  define LOCOIOSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LOCOIOSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LOCOIO_GLOBAL_H
