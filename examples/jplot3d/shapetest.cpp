#include "shapetest.h"
#include <QHBoxLayout>
#include <QPushButton>
#include "jplot3d_view.h"
#include "jplot3d_scene.h"
#include "jplot3d_coord.h"
#include "jglscale.h"
#include "jglfunction.h"

// - class ShapeTest -

ShapeTest::ShapeTest(QWidget *parent)
    : QWidget(parent)
    , q_jview1(0)
    , q_jview2(0)
    , q_jshape1(0)
    , q_jshape2(0)
{
    setObjectName("ShapeTest");
    resize(800, 480);
    setWindowTitle("example of jplot3d");

    QHBoxLayout *horiLayoutTop = new QHBoxLayout();
    horiLayoutTop->setContentsMargins(0, 0, 0, 0);
    horiLayoutTop->setSpacing(0);

#if 1
    q_jview1 = new J3D::JView(this);
    q_jview1->setObjectName("jview1");
    horiLayoutTop->addWidget(q_jview1);
    initView(q_jview1);
#endif

#if 1
    q_jview2 = new J3D::JView(this);
    q_jview2->setObjectName("jview2");
    horiLayoutTop->addWidget(q_jview2);
    initView(q_jview2);
#endif
    QVBoxLayout *vertLayoutMain = new QVBoxLayout(this);
    vertLayoutMain->setContentsMargins(0, 0, 0, 6);
    vertLayoutMain->addLayout(horiLayoutTop);

    QPushButton *buttonTest = new QPushButton("Test", this);
    buttonTest->setFocusPolicy(Qt::TabFocus);
    buttonTest->setFocus();
    vertLayoutMain->addWidget(buttonTest);

    connect(buttonTest, SIGNAL(clicked(bool)), SLOT(buttonTestClicked()));

    //
    buttonTestClicked();
}

void ShapeTest::initView(J3D::JView *jview)
{
    if (!jview) {
        return;
    }

    jview->setFocusPolicy(Qt::NoFocus);

    J3D::JScene *jscene = qobject_cast<J3D::JScene *>(jview->scene());
    if (jview->objectName() == "jview1") {
        jscene->setOption(J3D::JGLScene::ObjectPicking, true);
        jscene->setDefaultCenter(QVector3D(0.5f, 0.5f, 0.5f));

        J3D::JCoord *jcoord = jscene->jcoord();
        jcoord->setAxisLabelHints(J3D::JCoord::MajorAxes);
        jcoord->setLineHints(J3D::AllLines);
        jcoord->setSideHints(J3D::MajorSides);
        jcoord->setTickDrawable(true);
        jcoord->setTickMajorDrawable(true);
        jcoord->setTickMinorDrawable(true);
        //
        jscene->jscale()->setAutoScale(true);
        // jmarker
        J3D::JMarker *jmarker = jscene->jmarker();
        jmarker->setVisible(true);
        //
        q_jshape1 = new J3D::JShape(jview);
        q_jshape1->setObjectName("jshape1");
        q_jshape1->setFocusable(true);
        q_jshape1->setPickable(true);
        q_jshape1->attach(jscene);
    } else {
        jscene->setOption(J3D::JGLScene::ObjectPicking, true);
        jscene->setDefaultCenter(QVector3D(0.5f, 0.5f, 0.5f));

        J3D::JCoord *jcoord = jscene->jcoord();
        jcoord->setAxisLabelHints(J3D::JCoord::MajorAxes);
        jcoord->setLineHints(J3D::AllLines);
        jcoord->setSideHints(J3D::MajorSides);
        jcoord->setTickDrawable(true);
        jcoord->setTickMajorDrawable(true);
        jcoord->setTickMinorDrawable(true);
        //
        jscene->jscale()->setAutoScale(true);

        q_jshape2 = new J3D::JShape(jview);
        q_jshape2->setObjectName("jshape2");
        q_jshape2->setFocusable(true);
        q_jshape2->setPickable(true);
        q_jshape2->attach(jscene);
    }
}

void ShapeTest::updateShape(J3D::JShape *jshape)
{
    if (!jshape) {
        return;
    }

    jshape->clearShape();
    if (jshape->objectName() == "jshape1") {
        for (int i = 0; i < 5; ++i) {
            J3D::JRect3D box(1000 - qrand() % 2000,
                             1000 - qrand() % 2000,
                             1000 - qrand() % 2000,
                             qrand() % 1000 + 10,
                             qrand() % 1000 + 10,
                             qrand() % 1000 + 10);
#if 1
            jshape->addBox(QString("box #%1").arg(i + 1), box,
                           J3D::JGLFunction::rangColor(220));
#else
            jshape->addCircle(QString("box #%1").arg(i + 1), box.center(), (qrand() % 100) + 10,
                              J3D::JGLFunction::rangColor(220), 50, 50);
#endif
        }
#if 1
        for (int i = 0; i < 10; ++i) {
            J3D::JRect3D box(1000 - qrand() % 2000,
                             1000 - qrand() % 2000,
                             1000 - qrand() % 2000,
                             qrand() % 1000 + 10,
                             qrand() % 1000 + 10,
                             qrand() % 1000 + 10);
            jshape->addCircle(QString("box #%1").arg(i + 1), box.center(), (qrand() % 100) + 10,
                              J3D::JGLFunction::rangColor(220), 50, 50);
        }
#endif
    } else {
        for (int i = 0; i < 10; ++i) {
            J3D::JRect3D box(1000 - qrand() % 2000,
                             1000 - qrand() % 2000,
                             1000 - qrand() % 2000,
                             qrand() % 1000 + 10,
                             qrand() % 1000 + 10,
                             qrand() % 1000 + 10);
#if 1
            jshape->addBox(QString("box #%1").arg(20 + i + 1), box,
                           J3D::JGLFunction::rangColor(220));
#else
            jshape->addCircle(QString("box #%1").arg(20 + i + 1), box.center(), (qrand() % 100) + 10,
                              J3D::JGLFunction::rangColor(220), 50, 50);
#endif
        }
    }
}

void ShapeTest::buttonTestClicked()
{
    updateShape(q_jshape1);
    updateShape(q_jshape2);
}

// - class ShapeTest2 -

ShapeTest2::ShapeTest2(QWidget *parent)
    : QWidget(parent)
    , q_jwidget1(0)
    , q_jwidget2(0)
    , q_jshape1(0)
    , q_jshape2(0)
{
    setObjectName("ShapeTest2");
    resize(800, 480);
    setWindowTitle("example of jplot3d");

    QHBoxLayout *horiLayoutTop = new QHBoxLayout();
    horiLayoutTop->setContentsMargins(0, 0, 0, 0);
    horiLayoutTop->setSpacing(0);

#if 1
    q_jwidget1 = new J3D::JWidget(this);
    q_jwidget1->setObjectName("jwidget1");
    horiLayoutTop->addWidget(q_jwidget1);
    init(q_jwidget1);
#endif

#if 1
    q_jwidget2 = new J3D::JWidget(this);
    q_jwidget2->setObjectName("jwidget2");
    horiLayoutTop->addWidget(q_jwidget2);
    init(q_jwidget2);
#endif
    QVBoxLayout *vertLayoutMain = new QVBoxLayout(this);
    vertLayoutMain->setContentsMargins(0, 0, 0, 6);
    vertLayoutMain->addLayout(horiLayoutTop);

    QPushButton *buttonTest = new QPushButton("Test", this);
    buttonTest->setFocusPolicy(Qt::TabFocus);
    buttonTest->setFocus();
    vertLayoutMain->addWidget(buttonTest);

    connect(buttonTest, SIGNAL(clicked(bool)), SLOT(buttonTestClicked()));

    //
    buttonTestClicked();
}

void ShapeTest2::init(J3D::JWidget *jwidget)
{
    if (!jwidget) {
        return;
    }

    jwidget->setFocusPolicy(Qt::NoFocus);

    if (jwidget->objectName() == "jwidget1") {
        jwidget->setOption(J3D::JGLWidget::ObjectPicking, true);
        jwidget->setDefaultCenter(QVector3D(0.5f, 0.5f, 0.5f));

        J3D::JCoord *jcoord = jwidget->jcoord();
        jcoord->setAxisLabelHints(J3D::JCoord::MajorAxes);
        jcoord->setLineHints(J3D::AllLines);
        jcoord->setSideHints(J3D::MajorSides);
        jcoord->setTickDrawable(true);
        jcoord->setTickMajorDrawable(true);
        jcoord->setTickMinorDrawable(true);
        //
        jwidget->jscale()->setAutoScale(true);

        q_jshape1 = new J3D::JShape(jwidget);
        q_jshape1->setObjectName("jshape1");
        q_jshape1->setFocusable(true);
        q_jshape1->setPickable(true);
        q_jshape1->attach(jwidget);
    } else {
        jwidget->setOption(J3D::JGLWidget::ObjectPicking, true);
        jwidget->setDefaultCenter(QVector3D(0.5f, 0.5f, 0.5f));

        J3D::JCoord *jcoord = jwidget->jcoord();
        jcoord->setAxisLabelHints(J3D::JCoord::MajorAxes);
        jcoord->setLineHints(J3D::AllLines);
        jcoord->setSideHints(J3D::MajorSides);
        jcoord->setTickDrawable(true);
        jcoord->setTickMajorDrawable(true);
        jcoord->setTickMinorDrawable(true);
        //
        jwidget->jscale()->setAutoScale(true);

        q_jshape2 = new J3D::JShape(jwidget);
        q_jshape2->setObjectName("jshape2");
        q_jshape2->setFocusable(true);
        q_jshape2->setPickable(true);
        q_jshape2->attach(jwidget);
    }
}

void ShapeTest2::updateShape(J3D::JShape *jshape)
{
    if (!jshape) {
        return;
    }

    jshape->clearShape();
    if (jshape->objectName() == "jshape1") {
        for (int i = 0; i < 10; ++i) {
            J3D::JRect3D box(1000 - qrand() % 2000,
                             1000 - qrand() % 2000,
                             1000 - qrand() % 2000,
                             qrand() % 1000 + 10,
                             qrand() % 1000 + 10,
                             qrand() % 1000 + 10);
            jshape->addBox(QString("box #%1").arg(i + 1), box,
                           J3D::JGLFunction::rangColor(220));
        }
    } else {
        for (int i = 0; i < 10; ++i) {
            J3D::JRect3D box(1000 - qrand() % 2000,
                             1000 - qrand() % 2000,
                             1000 - qrand() % 2000,
                             qrand() % 1000 + 10,
                             qrand() % 1000 + 10,
                             qrand() % 1000 + 10);
            jshape->addBox(QString("box #%1").arg(20 + i + 1), box,
                           J3D::JGLFunction::rangColor(220));
        }
    }
}

void ShapeTest2::buttonTestClicked()
{
    updateShape(q_jshape1);
    updateShape(q_jshape2);
}
