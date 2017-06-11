import kivy
kivy.require('1.9.1')

from kivy.app import App
from kivy.uix.screenmanager import ScreenManager, Screen, FadeTransition
from kivy.uix.gridlayout import GridLayout
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.pagelayout import PageLayout
from kivy.uix.label import Label
from kivy.uix.textinput import TextInput

from kivy.properties import NumericProperty

from ARSurveyor.camerawidget import Camera

import numpy as np

try:
    import opencv2 as cv2
except ImportError:
    import cv2

class MainLayout(ScreenManager): pass

class MenuScreen(Screen): pass

class CalibrationScreen(Screen): pass

class LoadDrawingScreen(Screen): pass

class PlaceDrawingScreen(Screen): pass

class ProcessingScreen(Screen): pass

class CalibrationCamera(Camera):
    def on_tex(self, camera):
        flag, img = camera._device.read()
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        edges = cv2.Canny(gray,50,150,apertureSize = 3)
        lines = cv2.HoughLines(edges,1,np.pi/180,200)
        for rho,theta in lines[0]:
            a = np.cos(theta)
            b = np.sin(theta)
            x0 = a*rho
            y0 = b*rho
            x1 = int(x0 + 1000*(-b))
            y1 = int(y0 + 1000*(a))
            x2 = int(x0 - 1000*(-b))
            y2 = int(y0 - 1000*(a))

            cv2.line(img,(x1,y1),(x2,y2),(0,0,255),2)


class HandPlotterApp(App):
    kv_file = "handplotter"
    
    def build(self):
        return MainLayout()


if __name__ == '__main__':
    HandPlotterApp().run()
