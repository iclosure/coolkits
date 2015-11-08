#ifndef JPLOT3D_VIEW_H
#define JPLOT3D_VIEW_H

#include "jplot3d_global.h"
#include "jglview.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace J3D {

// - class JView -

class JViewPrivate;

class J3D_EXPORT JView : public JGLView
{
    Q_OBJECT
public:
    explicit JView(QWidget *parent = 0);
    virtual ~JView();

private:
    Q_DISABLE_COPY(JView)
    J_DECLARE_PRIVATE(JView)
};

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JPLOT3D_VIEW_H
