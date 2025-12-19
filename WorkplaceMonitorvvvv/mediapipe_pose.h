#ifndef MEDIAPIPE_POSE_H
#define MEDIAPIPE_POSE_H

#include <QObject>
#include <QProcess>

class MediaPipePose : public QObject
{
    Q_OBJECT
public:
    explicit MediaPipePose(QObject *parent = nullptr);
    void start();
    void sendCalibrate();

signals:
    void badPostureDetected();
    void badPostureCleared();

private:
    QProcess process;
};

#endif
