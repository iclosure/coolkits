#ifndef JECHARTS_GLOBAL_H
#define JECHARTS_GLOBAL_H

#include <qglobal.h>

// JECHARTS_VERSION is (major << 16) + (minor << 8) + patch.

#define JECHARTS_VERSION       0x000001
#define JECHARTS_VERSION_STR   "0.0.1"

#if defined(Q_WS_WIN) || defined(Q_OS_WIN) || defined(Q_WS_S60)

#if defined(_MSC_VER) // MSVC Compiler
// template-class specialization 'identifier' is already instantiated
#pragma warning(disable: 4660)
#pragma warning(disable: 4819)  // warning : 936
#endif // _MSC_VER

#ifdef JECHARTS_DLL

#if defined(JECHARTS_MAKEDLL)
#define JECHARTS_EXPORT  Q_DECL_EXPORT
#else
#define JECHARTS_EXPORT  Q_DECL_IMPORT

#ifdef _DEGBU
#pragma comment(lib, "jechartsd.lib")
#else
#pragma comment(lib, "jecharts.lib")
#endif

#endif

#endif // JECHARTS_DLL

#endif // Q_WS_WIN || Q_WS_S60

#ifndef JECHARTS_EXPORT
#define JECHARTS_EXPORT
#endif

// - private pointer
#define J_DECLARE_PRIVATE(name) \
    name ## Private *d_ptr; \
    Q_DECLARE_PRIVATE(name)
#define J_DECLARE_PUBLIC(name) \
    name *q_ptr; \
    Q_DECLARE_PUBLIC(name)

namespace JEcharts {

// - class JEchartsGlobal -

class JEchartsGlobalPrivate;

class JECHARTS_EXPORT JEchartsGlobal
{
public:
    explicit JEchartsGlobal();
    ~JEchartsGlobal();

private:
    Q_DISABLE_COPY(JEchartsGlobal)
    J_DECLARE_PRIVATE(JEchartsGlobal)
};

} // - end of namespace JEcharts

#endif // JECHARTS_GLOBAL_H
