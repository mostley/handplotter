# -*- coding: utf-8 -*-
import numpy as np
from pyqtgraph.Qt import QtCore, QtGui
import pyqtgraph as pg
import pyqtgraph.opengl as gl

app = QtGui.QApplication([])
w = gl.GLViewWidget()
w.show()
w.setWindowTitle('You gotta track \'em all!')
w.setCameraPosition(distance=40)

g = gl.GLGridItem()
g.scale(2,2,1)
w.addItem(g)


vertices = np.array([
        [0, 0, 0], [0, 0, 1],
        [0, 0, 0], [0, 1, 0],
        [0, 0, 0], [1, 0, 0],
    ])
colors = np.array([
        [1, 0, 0, 1], [1, 0, 0, 1],
        [0, 1, 0, 1], [0, 1, 0, 1],
        [0, 0, 1, 1], [0, 0, 1, 1],
    ])
v = gl.GLLinePlotItem(pos=vertices, width=5, color=colors, mode='lines')
w.addItem(v)


    


## Start Qt event loop unless running in interactive mode.
if __name__ == '__main__':
    import sys
    if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
        QtGui.QApplication.instance().exec_()
