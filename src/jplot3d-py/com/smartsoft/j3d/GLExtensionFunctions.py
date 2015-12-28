'''
Created on Dec 28, 2015

@author: iclosure
'''

class GLExtensionFunctions(object):
    '''
    classdocs
    '''
    def __init__(self, params):
        '''
        Constructor
        '''
        
    def resolve(self, context):
        pass
    
    def fboSupported(self):
        pass
    
    def openGL15Supported(self):
        pass
    
_instance = GLExtensionFunctions()

def getGLExtensionFunctions():
    return _instance
