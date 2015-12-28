'''
Created on Dec 28, 2015

@author: iclosure
'''
from PyQt5.QtWidgets import QGraphicsScene
from PyQt5.Qt import QRectF

class JGLScene(QGraphicsScene):
    '''
    classdocs
    '''
    def __init__(self, sceneRect=QRectF(0, 0, 1024, 768), viewport = None, parent = None):
        '''
        Constructor
        '''
        super(JGLScene, self).__init__(sceneRect, parent)