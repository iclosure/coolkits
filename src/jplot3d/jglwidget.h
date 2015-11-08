#ifndef JGLWIDGET_H
#define JGLWIDGET_H

#include "jplot3d_global.h"
#include <QGLWidget>
#include <QVector3D>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace J3D {

// - class JGLWidget -

class JGLWidgetPrivate;
class JGLObject;
class JGLPainter;
class JGLIndicator;

class J3D_EXPORT JGLWidget : public QGLWidget
{
    Q_OBJECT
    Q_PROPERTY(QVector3D scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(QVector3D center READ center WRITE setCenter NOTIFY centerChanged)
    Q_PROPERTY(QVector3D offset READ offset WRITE setOffset NOTIFY offsetChanged)
    Q_PROPERTY(qreal depth READ depth WRITE setDepth NOTIFY depthChanged)
    Q_PROPERTY(QColor viewportColor READ viewportColor WRITE setViewportColor NOTIFY viewportColorChanged)
    Q_PROPERTY(QVector3D defaultCenter READ defaultCenter WRITE setDefaultCenter NOTIFY defaultCenterChanged)
public:
    explicit JGLWidget(QWidget *parent = 0);
    virtual ~JGLWidget();

    enum Option {
        ObjectPicking = 0x0001,
        ShowPicking = 0x0002,
        CameraNavigation = 0x0004,
        PaintingLog = 0x0008
    };
    Q_DECLARE_FLAGS(Options, Option)

    Options options() const;
    void setOptions(Options value);
    void setOption(Option option, bool enable);

    void registerObject(unsigned int objectId, JGLObject *object, bool update = true);
    void deregisterObject(unsigned int objectId, bool update = true);
    JGLObject *objectForPoint(const QPointF &point);

    void addObject(JGLObject *object, bool update = true);
    void removeObject(JGLObject *object, bool update = true);
    void clearObjects(bool update = true);

    QVector3D scale() const;
    QVector3D center() const;
    QVector3D offset() const;
    qreal depth() const;
    QColor viewportColor() const;
    QVector3D defaultCenter() const;

    bool indicatorDrawable() const;
    void setIndicatorDrawable(bool value);

    //QGraphicsItem *jindicator() const;

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);

    virtual void earlyPaintGL(JGLPainter *painter);
    virtual void paintGL(JGLPainter *painter) = 0;

    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void wheelEvent(QWheelEvent *e);

    virtual void enterEvent(QEvent *e);
    virtual void leaveEvent(QEvent *e);

    virtual void keyPressEvent(QKeyEvent *e);

Q_SIGNALS:
    void scaleChanged(const QVector3D &);
    void centerChanged(const QVector3D &);
    void offsetChanged(const QVector3D &);
    void depthChanged(qreal);
    void viewportColorChanged(const QColor &);
    void defaultCenterChanged(const QVector3D &);

    void doubleClicked();

public Q_SLOTS:
    void setScale(const QVector3D &value, bool animation = false);
    void setCenter(const QVector3D &value, bool animation = false);
    void setOffset(const QVector3D &value, bool animation = false);
    void setDepth(qreal value, bool animation = false);
    void setViewportColor(const QColor &value, bool animation = false);
    void setDefaultCenter(const QVector3D &value, bool animation = false);

    void reset(bool animation = false);
    void resetScale(bool animation = false);
    void resetCenter(bool animation = false);
    void resetOffset(bool animation = false);
    void resetDepth(bool animation = false);
    void resetRotation(bool animation = false);

protected:
    const QList<JGLObject *> &objects() const;
    const QMap<unsigned int, JGLObject *> &registerObjects() const;

private:
    Q_DISABLE_COPY(JGLWidget)
    J_DECLARE_PRIVATE(JGLWidget)
};

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JGLWIDGET_H
