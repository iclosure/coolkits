'''
Created on Dec 28, 2015

@author: iclosure
'''
from com.smartsoft.j3d.GLView import JGLView
from com.smartsoft.j3d.Scene import JScene
from PyQt5.Qt import QRectF

class JView(JGLView):
    '''
    classdocs
    '''
    def __init__(self, parent = None):
        '''
        Constructor
        '''
        super(JView, self).__init__(parent)
        self.setObjectName("JView")
        sceneRect = QRectF(0, 0, 1024, 768)
        self.setScene(JScene(sceneRect, self.viewport(), self))