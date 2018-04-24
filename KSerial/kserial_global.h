#ifndef KSERIAL_GLOBAL_H
#define KSERIAL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(KSERIAL_LIBRARY)
#  define KSERIALSHARED_EXPORT Q_DECL_EXPORT
#else
#  define KSERIALSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // KSERIAL_GLOBAL_H
