#ifndef JGLOBJECT_H
#define JGLOBJECT_H

#include "jplot3d_global.h"
#include "jglmatrix.h"
#include <QObject>
#include <QVector3D>
#include <QQuaternion>
#include <QGLWidget>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

class QGLWidget;
class QGLContext;

namespace J3D {

// - class JGLObject -

class JGLObjectPrivate;
class JGLPainter;
class JGLScene;

class J3D_EXPORT JGLObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString identity READ identity WRITE setIdentity NOTIFY identityChanged)
    Q_PROPERTY(QVector3D pos READ pos WRITE setPos NOTIFY posChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(qreal scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(qreal rotationAngle READ rotationAngle WRITE setRotationAngle NOTIFY rotationAngleChanged)
    Q_PROPERTY(QVector3D rotationVector READ rotationVector WRITE setRotationVector NOTIFY rotationVectorChanged)
    Q_PROPERTY(bool focusable READ focusable WRITE setFocusable NOTIFY focusableChanged)
    Q_PROPERTY(bool pickable READ pickable WRITE setPickable NOTIFY pickableChanged)
    Q_PROPERTY(bool picking READ picking WRITE setPicking NOTIFY pickingChanged)
    Q_PROPERTY(bool outlineEnabled READ outlineEnabled WRITE setOutlineEnabled NOTIFY outlineEnabledChanged)
    Q_PROPERTY(JRect3D box READ box WRITE setBox NOTIFY boxChanged)
    Q_PROPERTY(QVector3D offsetVector READ offsetVector WRITE setOffsetVector NOTIFY offsetVectorChanged)
    Q_PROPERTY(QVector3D scaleVector READ scaleVector WRITE setScaleVector NOTIFY scaleVectorChanged)
public:
    explicit JGLObject(QObject *parent = 0);
    explicit JGLObject(const QString &identity, QObject *parent = 0);
    explicit JGLObject(const QString &identity, const QColor &color, QObject *parent = 0);
    explicit JGLObject(const QString &identity, const QColor &color, const QVector3D &pos,
                       QObject *parent = 0);
    virtual ~JGLObject();

    unsigned int objectId() const;

    QString identity() const;

    QVector3D pos() const;
    QColor color() const;
    qreal scale() const;
    qreal rotationAngle() const;
    QVector3D rotationVector() const;
    bool focusable() const;
    bool pickable() const;
    bool picking() const;
    bool outlineEnabled() const;

    bool isDirty() const;
    void setDirty();

    JRect3D box() const;
    JRect3D scaledBox() const;

    QVector3D offsetVector() const;
    QVector3D scaleVector() const;

    bool makeCurrent();
    bool doneCurrent();

    QGLWidget *viewport() const;
    void setViewport(QGLWidget *viewport);

    QGLContext *context() const;

    bool beginContext();
    bool doneContext();

    QVariant data(int role = Qt::UserRole + 1) const;
    void setData(const QVariant &value, int role = Qt::UserRole + 1);

public:
    virtual void initialize(JGLScene *scene);
    virtual void draw(JGLPainter *painter);

protected:
    virtual bool event(QEvent *e);
    virtual void update();

Q_SIGNALS:
    void repaint();

    void pressed();
    void clicked();
    void released();
    void doubleClicked();
    void entered();
    void left();
    void rightPressed();
    void rightClicked();

    void identityChanged(const QString &);
    void posChanged(const QVector3D &);
    void colorChanged(const QColor &);
    void scaleChanged(qreal);
    void rotationAngleChanged(qreal);
    void rotationVectorChanged(const QVector3D &);
    void focusableChanged(bool);
    void pickableChanged(bool);
    void pickingChanged(bool);
    void outlineEnabledChanged(bool);

    void boxChanged(const JRect3D &);
    void offsetVectorChanged(const QVector3D &);
    void scaleVectorChanged(const QVector3D &);

public Q_SLOTS:
    void setIdentity(const QString &value);
    void setPos(const QVector3D &value, bool animation = false);
    void setColor(const QColor &value, bool animation = false);
    void setScale(qreal value, bool animation = false);
    void setRotationAngle(qreal value, bool animation = false);
    void setRotationVector(const QVector3D &value, bool animation = false);
    void setFocusable(bool value);
    void setPickable(bool value);
    void setPicking(bool value);
    void setOutlineEnabled(bool value);

    void setBox(const JRect3D &value);
    void setOffsetVector(const QVector3D &value, bool animation = false);
    void setScaleVector(const QVector3D &value, bool animation = false);

protected:
    unsigned int glListId() const;
    void setGLListId(unsigned int id);

private:
    Q_DISABLE_COPY(JGLObject)
    J_DECLARE_PRIVATE(JGLObject)
};

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JGLOBJECT_H
