import cv2, imutils, time
import yaml
from cv2 import aruco

camera = cv2.VideoCapture(0)
time.sleep(0.25)

dictionary = aruco.getPredefinedDictionary(aruco.DICT_6X6_250)
board = aruco.CharucoBoard_create(
                squaresX = 5,
                squaresY = 7,
                squareLength = 0.04,
                markerLength = 0.02,
                dictionary = dictionary)

while True:
    (grabbed, frame) = camera.read()

    if not grabbed:
        break

    frame = imutils.resize(frame, width=800)

    corners, ids, rejected = aruco.detectMarkers(frame, dictionary)

    frame_copy = frame.copy()

    if (ids is not None) and len(ids) > 0:
        aruco.drawDetectedMarkers(frame_copy, corners, ids)

        retval, charuco_corners, charuco_ids = aruco.interpolateCornersCharuco(corners, ids, frame, board)
        if (charuco_ids is not None) and len(charuco_ids) > 0:
            aruco.drawDetectedCornersCharuco(frame_copy, charuco_corners, charuco_ids)

    cv2.imshow("ChArucoBoard - Detect Board & Markers", frame_copy)

    key = cv2.waitKey(1) & 0xFF

    if key == ord("q"):
        break

camera.release()
cv2.destroyAllWindows()