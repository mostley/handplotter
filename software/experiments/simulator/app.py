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
        target = Vector(self.target_pos_x + 0.001, self.target_pos_y + 0.001) + Vector(self.center_x, self.center_y)

        L = 500

        delta_r = target - Vector(self.origin)
        c = delta_r.length()
        a1 = math.atan2(delta_r[0], delta_r[1])
        a2 = self.return_angle(L, L, c)

        self.ids.arm_base_left.angle = 90 - math.degrees(a1 - a2)

        ### Debug output
        # print "[updatePositions:1] l_angle: {l_angle:.2f}; delta_r: [{delta_r[0]:.2f}, {delta_r[1]:.2f}] ({delta_r_len:.2f}); a1: {a1:.2f}; a2: {a2:.2f}".format(\
        #     l_angle=self.ids.arm_base_left.angle, 
        #     delta_r_len=c,
        #     delta_r=delta_r,
        #     a1=math.degrees(a1),
        #     a2=math.degrees(a2)
        # )

        # We might need this if we use a setup with unequal arm length ... (not sure if this code works)
        # H = target + L * Vector(math.cos((a1 - a2 + 0.621) + math.pi), math.sin((a1 - a2 + 0.621) + math.pi))
        # delta_l = H - Vector(self.origin)

        # c = delta_l.length()
        # a1 = math.atan2(delta_l[0], delta_l[1])
        # a2 = self.return_angle(L, L, c)

        self.ids.arm_base_right.angle = 90 - math.degrees(a1 + a2)

        ### Debug output
        # print "[updatePositions:2] r_angle: {r_angle:.2f}; delta_l: [{delta_l[0]:.2f}, {delta_l[1]:.2f}] ({delta_l_len:.2f}); a1: {a1:.2f}; a2: {a2:.2f}".format(\
        #     r_angle=self.ids.arm_base_right.angle, 
        #     delta_l_len=c,
        #     delta_l=delta_l,
        #     a1=math.degrees(a1),
        #     a2=math.degrees(a2)
        # )

        self.ids.arm_end_left.pos = self.ids.arm_base_left.lastEndpoint
        self.ids.arm_end_left.angle = self.ids.arm_base_right.angle
        self.ids.arm_end_right.pos = self.ids.arm_base_right.lastEndpoint
        self.ids.arm_end_right.angle = self.ids.arm_base_left.angle


class SimulatorApp(App):
    def build(self):
        self.simulator = HandPlotterSimulator()
        return self.simulator

    def on_start(self, **kwargs):
        print("STARTING...")
        self.simulator.on_start(**kwargs)

if __name__ == '__main__':
    SimulatorApp().run()
