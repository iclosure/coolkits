#ifndef JGLSCENE_H
#define JGLSCENE_H

#include "jplot3d_global.h"
#include <QGraphicsScene>
#include <QVector3D>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

class QGLWidget;

namespace J3D {

// - class JGLScene -

class JGLScenePrivate;
class JGLObject;
class JGLPainter;
class JGLIndicator;

class J3D_EXPORT JGLScene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(QVector3D scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(QVector3D center READ center WRITE setCenter NOTIFY centerChanged)
    Q_PROPERTY(QVector3D offset READ offset WRITE setOffset NOTIFY offsetChanged)
    Q_PROPERTY(qreal depth READ depth WRITE setDepth NOTIFY depthChanged)
    Q_PROPERTY(QColor viewportColor READ viewportColor WRITE setViewportColor NOTIFY viewportColorChanged)
    Q_PROPERTY(QVector3D defaultCenter READ defaultCenter WRITE setDefaultCenter NOTIFY defaultCenterChanged)
public:
    explicit JGLScene(QGLWidget *viewport, QObject *parent = 0);
    JGLScene(const QRectF &sceneRect, QGLWidget *viewport, QObject *parent = 0);
    JGLScene(qreal x, qreal y, qreal width, qreal height,
             QGLWidget *viewport, QObject *parent = 0);
    virtual ~JGLScene();

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

    QGraphicsItem *jindicator() const;

    QGLWidget *viewport() const;

protected:
    virtual void initializeGL();
    virtual void earlyPaintGL(JGLPainter *painter);
    virtual void paintGL(JGLPainter *painter) = 0;

    void drawBackground(QPainter *painter, const QRectF &rect);
    void drawForeground(QPainter *painter, const QRectF &rect);

    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *e);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *e);
    void wheelEvent(QGraphicsSceneWheelEvent *e);

    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);

    void keyPressEvent(QKeyEvent *e);

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
    Q_DISABLE_COPY(JGLScene)
    J_DECLARE_PRIVATE(JGLScene)
};

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JGLSCENE_H
