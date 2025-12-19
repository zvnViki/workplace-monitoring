#ifndef CAMERA_THREAD_H
#define CAMERA_THREAD_H

#include <QThread>

class CameraThread : public QThread
{
    Q_OBJECT
public:
    explicit CameraThread(QObject *parent = nullptr)
        : QThread(parent) {}
};

#endif
