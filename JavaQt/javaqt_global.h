#ifndef JAVAQT_GLOBAL_H
#define JAVAQT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(JAVAQT_LIBRARY)
#  define JAVAQTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define JAVAQTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // JAVAQT_GLOBAL_H
