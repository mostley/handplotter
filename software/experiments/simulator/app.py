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
    length = NumericProperty(500)
    color = ListProperty((255, 255, 255))

    def __init__(self, **kwargs):
        super(Arm, self).__init__(**kwargs)

        with self.canvas:
            self.colorStyle = Color(*self.color)
            self.line = Line(width=10, points=self.calculateLinePoints())

        self.bind(pos_x=self.update_rect)
        self.bind(pos_y=self.update_rect)
        self.bind(angle=self.update_rect)
        self.bind(length=self.update_rect)
        self.bind(color=self.update_rect)

    def calculateLinePoints(self):
        self.lastEndpoint = self.calculateEndPoint()
        return [
            self.pos_x, self.pos_y,
            self.lastEndpoint[0], self.lastEndpoint[1]
        ]

    def calculateEndPoint(self):
        direction = Vector(
            math.cos(math.radians(90 - self.angle)),
            math.sin(math.radians(90 - self.angle)))
        return Vector(self.pos) + direction * self.length

    def update_rect(self, *args):
        self.colorStyle.rgb = self.color
        self.line.points = self.calculateLinePoints()


class HandPlotterSimulator(GridLayout):
    target_pos_x = NumericProperty(0)
    target_pos_y = NumericProperty(0)
    target_pos = ReferenceListProperty(target_pos_x, target_pos_y)
    center_x = NumericProperty(0)
    center_y = NumericProperty(725)
    center = ReferenceListProperty(center_x, center_y)
    origin_x = NumericProperty(0)
    origin_y = NumericProperty(20)
    origin = ReferenceListProperty(origin_x, origin_y)

    def __init__(self, **kwargs):
        super(HandPlotterSimulator, self).__init__(**kwargs)

        self.previous_target = Vector(0, 0)

        self.bind(target_pos=self.updatePositions)

    def on_start(self, **kwargs):
        self.origin_x = self.get_root_window().width / 2
        self.center_x = self.get_root_window().width / 2

        self.ids.arm_end_left.pos = self.ids.arm_base_left.lastEndpoint
        self.ids.arm_end_right.pos = self.ids.arm_base_right.lastEndpoint

    def return_angle(self, a, b, c):
        # cosine rule for angle between c and a
        return math.acos((a * a + c * c - b * b) / (2 * a * c))

    def updatePositions(self, *args):
        target = Vector(self.target_pos_x + 0.001, self.target_pos_y + 0.001)

        L1 = 500
        L2 = 500

        delta = Vector(self.origin) - target
        c = delta.length()
        a1 = math.atan2(delta[0], delta[1])
        a2 = self.return_angle(L1, L2, c)

        self.ids.arm_base_left.angle = math.degrees(a2 + a1 - math.pi)

        print "updatePositions", self.ids.arm_base_right.angle

        self.ids.arm_end_left.pos = self.ids.arm_base_left.lastEndpoint
        self.ids.arm_end_right.pos = self.ids.arm_base_right.lastEndpoint


class SimulatorApp(App):
    def build(self):
        self.simulator = HandPlotterSimulator()
        return self.simulator

    def on_start(self, **kwargs):
        print("STARTING...")
        self.simulator.on_start(**kwargs)

if __name__ == '__main__':
    SimulatorApp().run()
