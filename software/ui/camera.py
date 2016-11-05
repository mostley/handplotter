from kivy.logger import Logger
from kivy.clock import Clock
from kivy.graphics.texture import Texture
from kivy.core.camera import CameraBase

import numpy as np

try:
    import opencv2 as cv2
except ImportError:
    import cv2


class CameraOpenCV(CameraBase):
    '''Implementation of CameraBase using OpenCV
    '''

    _update_ev = None

    def __init__(self, **kwargs):
        self._device = None
        super(CameraOpenCV, self).__init__(**kwargs)

    def init_camera(self):
        # create the device
        self._device = cv2.VideoCapture(self._index)

        # Set preferred resolution
        self._device.set(cv2.cv.CV_CAP_PROP_FRAME_WIDTH, self.resolution[0])
        self._device.set(cv2.cv.CV_CAP_PROP_FRAME_HEIGHT, self.resolution[1])

        # and get frame to check if it's ok
        flag, frame = self._device.read()
        self.lastFrame = frame
        # Just set the resolution to the frame we just got, but don't use
        # self.resolution for that as that would cause an infinite recursion
        # with self.init_camera (but slowly as we'd have to always get a
        # frame).
        width = np.size(frame, 1)
        height = np.size(frame, 0)
        self._resolution = (int(width), int(height))

        #get fps
        self.fps = self._device.get(cv2.cv.CV_CAP_PROP_FPS)
        if self.fps <= 0:
            self.fps = 1 / 30.

        if not self.stopped:
            self.start()

    def _update(self, dt):
        if self.stopped:
            return
        if self._texture is None:
            # Create the texture
            self._texture = Texture.create(self._resolution)
            self._texture.flip_vertical()
            self.dispatch('on_load')
        try:
            flag, frame = self._device.read()
            frame = self.process(frame)
            self._format = 'bgr'
            try:
                self._buffer = frame.imageData
            except AttributeError:
                # On OSX there is no imageData attribute but a tostring()
                # method.
                self._buffer = frame.tostring()
            self._copy_to_gpu()
        except:
            Logger.exception('OpenCV: Couldn\'t get image from Camera')

    def process(self, frame):
        return frame

    def start(self):
        super(CameraOpenCV, self).start()
        if self._update_ev is not None:
            self._update_ev.cancel()
        self._update_ev = Clock.schedule_interval(self._update, self.fps)

    def stop(self):
        super(CameraOpenCV, self).stop()
        if self._update_ev is not None:
            self._update_ev.cancel()
            self._update_ev = None
