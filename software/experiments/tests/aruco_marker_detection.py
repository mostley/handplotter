import cv2, imutils, time
from cv2 import aruco

camera = cv2.VideoCapture(1)
time.sleep(0.25)

dictionary = aruco.getPredefinedDictionary(aruco.DICT_6X6_250)

while True:
    (grabbed, frame) = camera.read()

    if not grabbed:
        break

    frame = imutils.resize(frame, width=800)

    corners, ids, rejected = aruco.detectMarkers(frame, dictionary)

    frame_copy = frame.copy()

    if (ids is not None) and len(ids) > 0:
        aruco.drawDetectedMarkers(frame_copy, corners, ids)   

    cv2.imshow("Aruco - Detected Markers", frame_copy)

    key = cv2.waitKey(1) & 0xFF

    if key == ord("q"):
        break

camera.release()
cv2.destroyAllWindows()