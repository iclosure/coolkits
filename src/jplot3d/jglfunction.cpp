#include "precomp.h"
#include "jglfunction.h"

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

// - class JGLFunction

/**
 * @brief JGLFunction::loadMatrix
 * @param m
 */
void JGLFunction::loadMatrix(const QMatrix4x4 &m)
{
    // static to precent glLoadMatrixf to fail on certain drivers
    static GLfloat mat[16];
#if QT_VERSION < 0x050000
    const qreal *data = m.constData();
#else
    const float *data = m.constData();
#endif
    for (int i = 0; i < 16; ++i) {
        mat[i] = data[i];
    }

    glLoadMatrixf(mat);
}

/**
 * @brief JGLFunction::multMatrix
 * @param m
 */
void JGLFunction::multMatrix(const QMatrix4x4 &m)
{
    // static to precent glLoadMatrixf to fail on certain drivers
    static GLfloat mat[16];
#if QT_VERSION < 0x050000
    const qreal *data = m.constData();
#else
    const float *data = m.constData();
#endif
    for (int i = 0; i < 16; ++i) {
        mat[i] = data[i];
    }

    glMultMatrixf(mat);
}

/**
 * @brief JGLFunction::pixelPosToViewPos
 * @param viewport
 * @param pos
 * @return
 */
QPointF JGLFunction::pixelPosToViewPos(const QRect &viewport, const QPoint &pos)
{
    return QPointF(2.0 * float(pos.x()) / viewport.width() - 1.0,
                   1.0 - 2.0 * float(pos.y()) / viewport.height());
}

/**
 * @brief JGLFunction::pixelPosToViewPos
 * @param viewport
 * @param pos
 * @return
 */
QPointF JGLFunction::pixelPosToViewPos(const QRectF &viewport, const QPointF &pos)
{
    return QPointF(2.0 * float(pos.x()) / viewport.width() - 1.0,
                   1.0 - 2.0 * float(pos.y()) / viewport.height());
}

/**
 * @brief JGLFunction::gbk2utf8
 * @param text
 * @return
 */
QString JGLFunction::gbk2utf8(const QString &text)
{
    QTextCodec *gbk = QTextCodec::codecForName("GB18030");
    return gbk->toUnicode(gbk->fromUnicode(text));
}

/**
 * @brief JGLFunction::utf82gbk
 * @param text
 * @return
 */
QString JGLFunction::utf82gbk(const QString &text)
{
    QTextCodec *gbk = QTextCodec::codecForName("GB18030");
    return gbk->toUnicode(text.toLocal8Bit());
}

/**
 * @brief JGLFunction::rangColor
 * @param opacity
 * @return
 */
QColor JGLFunction::rangColor(qreal opacity)
{
    return QColor(qrand() % 200 + 10,
                  qrand() % 200 + 10,
                  qrand() % 200 + 10,
                  opacity);
}

/**
 * @brief JGLFunction::clearAnnotate
 * @param folder
 */
void JGLFunction::clearAnnotate(const QString &folder)
{
    QDir dir(folder, QString("*.h;*.cpp"));
    if (!dir.exists()) {
        qDebug() << QString("\"%1\" direction is not exists!").arg(dir.path());
    }

    QFileInfoList entryList = dir.entryInfoList(QDir::Readable |
                                                QDir::NoDotAndDotDot |
                                                QDir::NoSymLinks |
                                                QDir::Files);
    foreach (QFileInfo fileInfo, entryList) {
        qDebug() << fileInfo.filePath();
        QFile file(fileInfo.filePath());
        if (file.open(QFile::ReadOnly)) {
            if (file.size() > 1024 * 1024 * 50) {  // if size > 50MB
                //
            } else {
                QString text = file.readAll();
                file.close();
                file.remove();
                text.remove(QRegExp("/\\*[^*]*\\*+(?:[^"));
                text.replace(QRegExp("(\r\n){2,}"), "\r\n");
                file.open(QFile::WriteOnly);
                file.write(text.toUtf8());
                file.close();
            }
        }
    }
}

QT_END_NAMESPACE
