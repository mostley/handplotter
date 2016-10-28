import cv2, imutils, time
import yaml
from cv2 import aruco
import numpy

camera = cv2.VideoCapture(0)
time.sleep(0.25)

dictionary = aruco.getPredefinedDictionary(aruco.DICT_6X6_250)
board = aruco.CharucoBoard_create(
                squaresX = 5,
                squaresY = 7,
                squareLength = 0.04,
                markerLength = 0.02,
                dictionary = dictionary)
calibration_flags = None  # ???

camera_matrix = numpy.empty((3,4), dtype=numpy.float32)
dist_coeffs = numpy.empty((5,), dtype=numpy.float32)

# all_corners = numpy.empty((0,1,2 ), dtype=numpy.float32)
# all_ids = numpy.empty((0,1), dtype=numpy.int32)
all_corners = []
all_ids = []

while True:
    (grabbed, frame) = camera.read()

    if not grabbed:
        print("Image capture failed.")
        break

    frame = imutils.resize(frame, width=800)

    corners, ids, rejected = aruco.detectMarkers(frame, dictionary)

    frame_copy = frame.copy()

    if (ids is not None) and len(ids) > 0:
        aruco.drawDetectedMarkers(frame_copy, corners, ids)

        retval, charuco_corners, charuco_ids = aruco.interpolateCornersCharuco(corners, ids, frame, board)
        if (charuco_ids is not None) and len(charuco_ids) > 0:
            aruco.drawDetectedCornersCharuco(frame_copy, charuco_corners, charuco_ids)

    cv2.imshow("ChArucoBoard - Camera calibration", frame_copy)

    key = cv2.waitKey(1) & 0xFF
    # if key != 255:
    #     print(key)
    if key in (ord("q"), 27): # -> "q" or Escape
        break

    if key == 8: # -> Backspace
        all_corners = numpy.empty((0,1,2 ), dtype=numpy.float32)
        all_ids = numpy.empty((0,1), dtype=numpy.int32)
        print("Points cleared.")

    if key == 32: # -> Spacebar
        if (charuco_ids is not None) and len(charuco_ids) > 0:
            # print(charuco_corners.shape, charuco_corners.dtype, charuco_ids.shape, charuco_ids.dtype)
            # all_corners = numpy.append(all_corners, charuco_corners, axis=0)
            # all_ids = numpy.append(all_ids, charuco_ids, axis=0)
            all_corners.append(charuco_corners)
            all_ids.append(charuco_ids)
            print("Points added. ({} ids)".format(len(all_corners)))

    if key == 10:
        if len(all_corners) > 0:
            print("Calibrating ...")
            # print(type(all_corners), all_corners.shape, all_corners.dtype, "\n",
            #       type(all_ids), all_ids.shape, all_ids.dtype)
            frame_size = frame.shape[:2]
            retval, camera_matrix, dist_coeffs, rvecs, tvecs = \
                aruco.calibrateCameraCharuco(all_corners, all_ids, board, frame_size, camera_matrix, dist_coeffs)
            print(retval)
            print(camera_matrix)
            print(dist_coeffs)
            print(tvecs)
            print(rvecs)

    # 10 -> Enter
    # 32 -> Space
    # 27 -> ESC
    # 8 -> Backspace

camera.release()
cv2.destroyAllWindows()