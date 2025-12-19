import cv2
import mediapipe as mp
import math
import numpy as np
from collections import deque

mp_drawing = mp.solutions.drawing_utils
mp_pose = mp.solutions.pose

# ---------- НАСТРОЙКИ ----------
ANGLE_THRESHOLD = 150        # угол ухо–плечо–бедро
SHOULDER_DIFF_THRESHOLD = 30 # перекос плеч
SMOOTH_WINDOW = 5            # сглаживание

# ---------- СГЛАЖИВАНИЕ ----------
angle_buffer = deque(maxlen=SMOOTH_WINDOW)
shoulder_buffer = deque(maxlen=SMOOTH_WINDOW)

def smooth(val, buffer):
    buffer.append(val)
    return sum(buffer) / len(buffer)

# ---------- УГОЛ ----------
def calculate_angle(a, b, c):
    a = np.array(a)
    b = np.array(b)
    c = np.array(c)

    ba = a - b
    bc = c - b

    cosine = np.dot(ba, bc) / (np.linalg.norm(ba) * np.linalg.norm(bc) + 1e-6)
    angle = np.degrees(np.arccos(np.clip(cosine, -1.0, 1.0)))
    return angle

# ---------- КАМЕРА ----------
cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

with mp_pose.Pose(
    min_detection_confidence=0.6,
    min_tracking_confidence=0.6
) as pose:

    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            break

        image_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        result = pose.process(image_rgb)

        h, w, _ = frame.shape

        if result.pose_landmarks:
            landmarks = result.pose_landmarks.landmark

            # ---------- ТОЧКИ ----------
            ear = (
                int(landmarks[mp_pose.PoseLandmark.LEFT_EAR].x * w),
                int(landmarks[mp_pose.PoseLandmark.LEFT_EAR].y * h)
            )
            shoulder = (
                int(landmarks[mp_pose.PoseLandmark.LEFT_SHOULDER].x * w),
                int(landmarks[mp_pose.PoseLandmark.LEFT_SHOULDER].y * h)
            )
            hip = (
                int(landmarks[mp_pose.PoseLandmark.LEFT_HIP].x * w),
                int(landmarks[mp_pose.PoseLandmark.LEFT_HIP].y * h)
            )

            right_shoulder = (
                int(landmarks[mp_pose.PoseLandmark.RIGHT_SHOULDER].x * w),
                int(landmarks[mp_pose.PoseLandmark.RIGHT_SHOULDER].y * h)
            )

            # ---------- ВЫЧИСЛЕНИЯ ----------
            angle = calculate_angle(ear, shoulder, hip)
            shoulder_diff = abs(shoulder[1] - right_shoulder[1])

            angle = smooth(angle, angle_buffer)
            shoulder_diff = smooth(shoulder_diff, shoulder_buffer)

            bad_posture = angle < ANGLE_THRESHOLD or shoulder_diff > SHOULDER_DIFF_THRESHOLD

            # ---------- ОТРИСОВКА ----------
            mp_drawing.draw_landmarks(
                frame,
                result.pose_landmarks,
                mp_pose.POSE_CONNECTIONS
            )

            # контрольные точки
            cv2.circle(frame, ear, 6, (255, 0, 0), -1)
            cv2.circle(frame, shoulder, 6, (0, 255, 255), -1)
            cv2.circle(frame, hip, 6, (255, 255, 0), -1)

            cv2.line(frame, ear, shoulder, (255, 255, 0), 2)
            cv2.line(frame, shoulder, hip, (255, 255, 0), 2)

            # ---------- ТЕКСТ ----------
            if bad_posture:
                cv2.putText(frame, "BAD POSTURE",
                            (30, 40),
                            cv2.FONT_HERSHEY_SIMPLEX,
                            1.2,
                            (0, 0, 255), 3)
            else:
                cv2.putText(frame, "GOOD POSTURE",
                            (30, 40),
                            cv2.FONT_HERSHEY_SIMPLEX,
                            1.2,
                            (0, 255, 0), 3)

        cv2.imshow("Posture Monitor (MediaPipe)", frame)

        if cv2.waitKey(5) & 0xFF == 27:
            break

cap.release()
cv2.destroyAllWindows()
