#ifndef SHAPETEST_H
#define SHAPETEST_H

#include <QWidget>
#include "jplot3d_view.h"
#include "jplot3d_glwidget.h"
#include "jplot3d_shape.h"

// - class ShapeTest -

class ShapeTest : public QWidget
{
    Q_OBJECT
public:
    ShapeTest(QWidget *parent = 0);

    void initView(J3D::JView *jview);
    void updateShape(J3D::JShape *jshape);

Q_SIGNALS:

public Q_SLOTS:
    void buttonTestClicked();

private:
    J3D::JView *q_jview1;
    J3D::JView *q_jview2;
    J3D::JShape *q_jshape1;
    J3D::JShape *q_jshape2;
};

// - class ShapeTest2 -

class ShapeTest2 : public QWidget
{
    Q_OBJECT
public:
    ShapeTest2(QWidget *parent = 0);

    void init(J3D::JWidget *jwidget);
    void updateShape(J3D::JShape *jshape);

Q_SIGNALS:

public Q_SLOTS:
    void buttonTestClicked();

private:
    J3D::JWidget *q_jwidget1;
    J3D::JWidget *q_jwidget2;
    J3D::JShape *q_jshape1;
    J3D::JShape *q_jshape2;
};

#endif // SHAPETEST_H
