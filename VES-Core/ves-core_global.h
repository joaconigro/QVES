#ifndef VESCORE_GLOBAL_H
#define VESCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(VESCORE_LIBRARY)
#  define VESCORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define VESCORESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // VESCORE_GLOBAL_H
