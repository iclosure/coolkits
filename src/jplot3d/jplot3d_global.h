#ifndef J3D_GLOBAL_H
#define J3D_GLOBAL_H

#include <qglobal.h>

// J3D_VERSION is (major << 16) + (minor << 8) + patch.

#define J3D_VERSION       0x000001
#define J3D_VERSION_STR   "0.0.1"

#if defined(Q_WS_WIN) || defined(Q_OS_WIN) || defined(Q_WS_S60)

#if defined(_MSC_VER) // MSVC Compiler
// template-class specialization 'identifier' is already instantiated
#pragma warning(disable: 4660)
#pragma warning(disable: 4819)  // warning : 936
#endif // _MSC_VER

#ifdef J3D_DLL

#if defined(J3D_MAKEDLL)
#define J3D_EXPORT  Q_DECL_EXPORT
#else
#define J3D_EXPORT  Q_DECL_IMPORT

#ifdef _DEGBU
#pragma comment(lib, "JPlot3Dd.lib")
#else
#pragma comment(lib, "JPlot3D.lib")
#endif

#endif

#endif // J3D_DLL

#endif // Q_WS_WIN || Q_WS_S60

#ifndef J3D_EXPORT
#define J3D_EXPORT
#endif

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

// - namespace J3D -
#define J3D_NAMESPACE J3D
#define J3D_BEGIN_NAMESPACE namespace J3D_NAMESPACE {
#define J3D_END_NAMESPACE }
#define J3D_USE_NAMESPACE using namespace J3D_NAMESPACE;

// - private pointer
#define J_DECLARE_PRIVATE(name) \
    name ## Private *d_ptr; \
    Q_DECLARE_PRIVATE(name)
#define J_DECLARE_PUBLIC(name) \
    name *q_ptr; \
    Q_DECLARE_PUBLIC(name)

namespace J3D {

// - class J3DGlobal -

class J3D_EXPORT J3DGlobal
{
public:
    J3DGlobal();
    ~J3DGlobal();
};

// - line of coordinate -

enum LineHint {
    NoLine = 0x00,
    LeftLine = 0x01,
    RightLine = 0x02,
    FloorLine = 0x04,
    CeilLine = 0x08,
    BackLine = 0x10,
    FrontLine = 0x20,

    MajorLines = LeftLine | FloorLine | BackLine,
    AllLines = 0x3f
};
Q_DECLARE_FLAGS(LineHints, LineHint)

// - side of coordinate -

enum SideHint {
    NoSide = 0x00,
    LeftSide = 0x01,
    RightSide = 0x02,
    BackSide = 0x04,
    FrontSide = 0x08,
    FloorSide = 0x10,
    CeilSide = 0x20,

    MajorSides = LeftSide | BackSide | FloorSide,
    AllSides = 0x3f
};
Q_DECLARE_FLAGS(SideHints, SideHint)

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // J3D_GLOBAL_H
