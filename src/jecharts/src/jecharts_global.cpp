#include "precomp.h"
#include "jecharts_global.h"

namespace JEcharts {

// class JEchartsGlobalPrivate

class JEchartsGlobalPrivate
{
public:
    JEchartsGlobalPrivate(JEchartsGlobal *parent)
        : q_ptr(parent)
    {

    }

    void init();

private:
    J_DECLARE_PUBLIC(JEchartsGlobal)
};

void JEchartsGlobalPrivate::init()
{
    //
}

// class JEchartsGlobal

/**
 * @brief JEchartsGlobal::JEchartsGlobal
 */
JEchartsGlobal::JEchartsGlobal()
    : d_ptr(new JEchartsGlobalPrivate(this))
{
    Q_D(JEchartsGlobal);
    d->init();
}

/**
 * @brief JEchartsGlobal::~JEchartsGlobal
 */
JEchartsGlobal::~JEchartsGlobal()
{
    Q_D(JEchartsGlobal);
    delete d;
}

} // end of namespace JECharts
