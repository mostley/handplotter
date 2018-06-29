import numpy as np
import cv2
import cv2.aruco as aruco

aruco_dict = aruco.Dictionary_get(aruco.DICT_6X6_250)

board = aruco.CharucoBoard_create(
    5, 7, 0.04, 0.02, aruco.getPredefinedDictionary(aruco.DICT_6X6_250))
img = board.draw((1024, 1024 * 7 / 5), 128)
cv2.imwrite("board.jpg", img)
