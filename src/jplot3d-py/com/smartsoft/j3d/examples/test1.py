'''
Created on Dec 28, 2015

@author: iclosure
'''
from PyQt5.Qt import QApplication
from com.smartsoft.j3d.View import JView

if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    
    view3d = JView()
    view3d.resize(800, 480)
    view3d.show()
    
    sys.exit(app.exec_())