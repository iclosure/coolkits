#ifndef JGLPAINTER_H
#define JGLPAINTER_H

#include "jplot3d_global.h"
#include <QObject>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace J3D {

// - class JGLPainter -

class JGLPainterPrivate;
class JGLScene;

class J3D_EXPORT JGLPainter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool picking READ picking WRITE setPicking NOTIFY pickingChanged)
public:
    explicit JGLPainter(QObject *parent = 0);
    explicit JGLPainter(JGLScene *scene, QObject *parent = 0);
    virtual ~JGLPainter();

    JGLScene *scene() const;

    bool picking() const;

    unsigned int objectPickId() const;
    void setObjectPickId(unsigned int id);
    void clearPickObjects();

    void begin();
    void end();

    void save();
    void restore();

Q_SIGNALS:
    void pickingChanged(bool);

public Q_SLOTS:
    void setPicking(bool value);

private:
    Q_DISABLE_COPY(JGLPainter)
    J_DECLARE_PRIVATE(JGLPainter)
};

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JGLPAINTER_H
