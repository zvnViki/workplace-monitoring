#include "camera_thread.h"

CameraThread::CameraThread(QObject *parent) : QThread(parent)
{
    cap.open(0);
}

void CameraThread::run()
{
    while (running)
    {
        cv::Mat frame;
        cap >> frame;
        if (!frame.empty())
            emit frameReady(frame);

        msleep(30);
    }
}

void CameraThread::stop()
{
    running = false;
    cap.release();
}
