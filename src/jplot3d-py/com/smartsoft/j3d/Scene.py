'''
Created on Dec 28, 2015

@author: iclosure
'''
from com.smartsoft.j3d.GLScene import JGLScene
from PyQt5.Qt import QRectF

class JScene(JGLScene):
    '''
    classdocs
    '''
    def __init__(self, sceneRect = QRectF(0, 0, 1024, 768), viewport = None, parent = None):
        '''
        Constructor
        '''
        super(JScene, self).__init__(sceneRect, viewport, parent)
        