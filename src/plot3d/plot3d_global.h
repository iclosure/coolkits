#ifndef JPLOT3D_GLOBAL_H
#define JPLOT3D_GLOBAL_H

#include <qglobal.h>

// JPLOT3D_VERSION is (major << 16) + (minor << 8) + patch.

#define JPLOT3D_VERSION       0x000001
#define JPLOT3D_VERSION_STR   "0.0.1"

#if defined(Q_WS_WIN) || defined(Q_WS_S60)

#if defined(_MSC_VER) // MSVC Compiler
// template-class specialization 'identifier' is already instantiated
#pragma warning(disable: 4660)
#pragma warning(disable: 4819)  // warning : 936
#endif // _MSC_VER

#ifdef JPLOT3D_DLL

#if defined(JPLOT3D_MAKEDLL)
#define JPLOT3D_EXPORT  Q_DECL_EXPORT
#else
#define JPLOT3D_EXPORT  Q_DECL_IMPORT
#endif

#endif // JPLOT3D_DLL

#endif // Q_WS_WIN || Q_WS_S60

#ifndef JPLOT3D_EXPORT
#define JPLOT3D_EXPORT
#endif

namespace Plot3D {

// - class JPlot3DGlobal -

class JPLOT3D_EXPORT JPlot3DGlobal
{
public:
    JPlot3DGlobal();
    ~JPlot3DGlobal();
};

} // - end of namespace Plot3D

#endif // JPLOT3D_GLOBAL_H
