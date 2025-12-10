#ifndef CAMERA_THREAD_H
#define CAMERA_THREAD_H

#include <QThread>
#include <opencv2/opencv.hpp>

class CameraThread : public QThread
{
    Q_OBJECT

public:
    explicit CameraThread(QObject *parent = nullptr);
    void stop();

signals:
    void frameReady(const cv::Mat& frame);

protected:
    void run() override;

private:
    bool running = true;
    cv::VideoCapture cap;
};

#endif
