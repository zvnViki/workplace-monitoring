
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "camera_thread.h"


#include <opencv2/opencv.hpp> // Äëÿ cv::VideoCapture

    QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void processFrame(const cv::Mat& frame);


private:
    Ui::MainWindow *ui;

    CameraThread *cameraThread;


    cv::CascadeClassifier faceCascade;
    bool postureBad = false;

};
#endif // MAINWINDOW_H
