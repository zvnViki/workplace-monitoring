#include "mediapipe_pose.h"
#include <QDebug>

MediaPipePose::MediaPipePose(QObject *parent)
    : QObject(parent)
{
}

void MediaPipePose::start()
{
    process.setProcessChannelMode(QProcess::MergedChannels);

    connect(&process, &QProcess::readyRead, this, [&]() {
        QByteArray data = process.readAll();
        qDebug().noquote() << data;

        if (data.contains("NOTIFY_BAD_POSTURE"))
            emit badPostureDetected();

        if (data.contains("CLEAR_BAD_POSTURE"))
            emit badPostureCleared();
    });

    process.start(
        "C:/Users/Admin/AppData/Local/Programs/Python/Python310/python.exe",
        { "C:/Qt/my_project/WorkplaceMonitorvvvv/mp_pose_stdout.py" }
        );

    process.waitForStarted();
}

void MediaPipePose::sendCalibrate()
{
    if (process.state() == QProcess::Running) {
        process.write("CALIBRATE\n");
        qDebug() << "CALIBRATE sent";
    }
}
