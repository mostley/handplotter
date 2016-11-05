import math
from kivy.app import App
from kivy.uix.widget import Widget
from kivy.uix.gridlayout import GridLayout
from kivy.properties import NumericProperty, ReferenceListProperty
from kivy.properties import ListProperty
from kivy.vector import Vector
from kivy.graphics import *


class Arm(Widget):
    pos_x = NumericProperty(0)
    pos_y = NumericProperty(0)
    pos = ReferenceListProperty(pos_x, pos_y)
    angle = NumericProperty(0)
    length = NumericProperty(20)
    color = ListProperty((255, 255, 255))

    def __init__(self, **kwargs):
        super(Arm, self).__init__(**kwargs)

        with self.canvas:
            self.colorStyle = Color(*self.color)
            self.line = Line(width=5, points=self.calculateLinePoints())

        self.bind(pos_x=self.update_rect)
        self.bind(pos_y=self.update_rect)
        self.bind(angle=self.update_rect)
        self.bind(length=self.update_rect)
        self.bind(color=self.update_rect)

    def calculateLinePoints(self):
        self.lastEndpoint = self.calculateEndPoint()
        print self.pos, self.lastEndpoint
        return [
            self.pos_x, self.pos_y,
            self.lastEndpoint[0], self.lastEndpoint[1]
        ]

    def calculateEndPoint(self):
        direction = Vector(
            math.cos(math.radians(self.angle)),
            math.sin(math.radians(self.angle)))
        return Vector(self.pos) + direction * self.length

    def update_rect(self, *args):
        self.colorStyle.rgb = self.color
        self.line.points = self.calculateLinePoints()


class HandPlotterSimulator(GridLayout):
    target_pos_x = NumericProperty(0)
    target_pos_y = NumericProperty(0)
    target_pos = ReferenceListProperty(target_pos_x, target_pos_y)

    def __init__(self, **kwargs):
        super(HandPlotterSimulator, self).__init__(**kwargs)

        self.bind(target_pos=self.updatePositions)

    def return_angle(self, a, b, c):
        # cosine rule for angle between c and a
        return acos((a * a + c * c - b * b) / (2 * a * c))

    def updatePositions(self, *args):
        print "updatePositions", self.target_pos

        target = Vector(self.target_pos_x, self.target_pos_y)
        origin = Vector(self.root.width / 2, 20)
        delta = target - origin
        c = delta.length
        a1 = atan2(delta[0], delta[1])
        a2 = atan2(delta[0], delta[1])

        self.ids.arm_end_left.pos = self.ids.arm_base_left.lastEndpoint
        self.ids.arm_end_right.pos = self.ids.arm_base_right.lastEndpoint


class SimulatorApp(App):
    def build(self):
        return HandPlotterSimulator()


if __name__ == '__main__':
    SimulatorApp().run()
