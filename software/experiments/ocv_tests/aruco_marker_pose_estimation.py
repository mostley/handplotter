import cv2, imutils, time
from cv2 import aruco
import numpy

camera = cv2.VideoCapture(1)
time.sleep(0.25)

dictionary = aruco.getPredefinedDictionary(aruco.DICT_6X6_250)

calibration_file = 'calibration.npz'
calib_data = numpy.load(calibration_file)
camera_matrix = calib_data['camera_matrix']
dist_coeffs = calib_data['dist_coeffs']


while True:
    (grabbed, frame) = camera.read()

    if not grabbed:
        break

    frame = imutils.resize(frame, width=800)

    corners, ids, rejected = aruco.detectMarkers(frame, dictionary)

    frame_copy = frame.copy()

    if (ids is not None) and len(ids) > 0:
        aruco.drawDetectedMarkers(frame_copy, corners, ids)

        rvecs, tvecs = aruco.estimatePoseSingleMarkers(corners, 35.5, camera_matrix, dist_coeffs)

        for i in range(len(ids)):
            aruco.drawAxis(frame_copy, camera_matrix, dist_coeffs, rvecs[i], tvecs[i], 20.0)


    cv2.imshow("Aruco - Pose detection", frame_copy)

    key = cv2.waitKey(1) & 0xFF

    if key == ord("q"):
        break

camera.release()
cv2.destroyAllWindows()