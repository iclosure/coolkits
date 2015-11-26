#ifndef JPLOT3D_MARKER_H
#define JPLOT3D_MARKER_H

#include "jplot3d_global.h"
#include <QWidget>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace J3D {

// - class JMarker -

class JMarkerPrivate;
class JGLScene;

class J3D_EXPORT JMarker : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
public:
    explicit JMarker(JGLScene *jscene, QWidget *parent = 0);
    virtual ~JMarker();

    QString text() const;

    JGLScene *jscene() const;

Q_SIGNALS:
    void textChanged(const QString &);

public Q_SLOTS:
    void setText(const QString &text);

private:
    Q_DISABLE_COPY(JMarker)
    J_DECLARE_PRIVATE(JMarker)
};

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JPLOT3D_MARKER_H
