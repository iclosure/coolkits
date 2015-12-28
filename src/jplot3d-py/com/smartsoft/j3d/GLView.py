'''
Created on Dec 28, 2015

@author: iclosure
'''
from PyQt5.QtWidgets import QGraphicsView
from PyQt5.QtGui import QPainter
from PyQt5.QtOpenGL import QGLWidget, QGLFormat, QGL
from PyQt5.Qt import QRectF, QPointF

class JGLView(QGraphicsView):
    '''
    classdocs
    '''
    def __init__(self, parent = None):
        '''
        Constructor
        '''
        super(JGLView, self).__init__(parent)
        self.setObjectName("JGLView")
        self.setMouseTracking(True)
        self.setRenderHints(QPainter.Antialiasing |
                            QPainter.SmoothPixmapTransform |
                            QPainter.HighQualityAntialiasing |
                            QPainter.TextAntialiasing)
        self.setTransformationAnchor(QGraphicsView.AnchorViewCenter)
        glWidget = QGLWidget(QGLFormat(QGL.SampleBuffers), self)
        glWidget.makeCurrent()
        self.setViewport(glWidget)
        self.setViewportUpdateMode(QGraphicsView.FullViewportUpdate)
        
    def resizeEvent(self, e):
        if self.scene():
            self.scene().setSceneRect(0, 0, e.size().width(), e.size().height())
    
    def wheelEvent(self, e):
        QGraphicsView.wheelEvent(e)