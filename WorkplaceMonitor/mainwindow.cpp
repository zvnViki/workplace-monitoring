#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Загружаем модель лица
    if (!faceCascade.load("haarcascade_frontalface_default.xml")) {
        QMessageBox::critical(this, "Ошибка", "Не найден файл haarcascade_frontalface_default.xml!");
        return;
    }

    // Создаем поток камеры
    cameraThread = new CameraThread(this);

    // При поступлении кадра -> обработка
    connect(cameraThread, &CameraThread::frameReady,
            this, &MainWindow::processFrame);

    // Запуск потока
    cameraThread->start();
}

MainWindow::~MainWindow()
{
    cameraThread->stop();
    cameraThread->wait();
    delete ui;
}

// === ОБРАБОТКА КАДРА И ОСАНКИ ===
void MainWindow::processFrame(const cv::Mat& frame)
{
    cv::Mat img = frame.clone();

    // Перевод в серый
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    // Поиск лиц
    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(gray, faces, 1.1, 3);

    postureBad = true; // по умолчанию плохая осанка

    if (!faces.empty())
    {
        cv::Rect face = faces[0];

        // Обводка лица
        cv::rectangle(img, face, cv::Scalar(0,255,0), 2);

        // Анализ высоты головы
        if (face.y < img.rows / 2)
            postureBad = false;
    }

    // Пишем результат
    if (postureBad)
    {
        cv::putText(img, "BAD POSTURE",
                    cv::Point(20,50),
                    cv::FONT_HERSHEY_SIMPLEX,
                    1.0,
                    cv::Scalar(0,0,255),
                    2);
    }
    else
    {
        cv::putText(img, "GOOD POSTURE",
                    cv::Point(20,50),
                    cv::FONT_HERSHEY_SIMPLEX,
                    1.0,
                    cv::Scalar(0,255,0),
                    2);
    }

    // Конвертация для Qt
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);

    QImage qimg(img.data,
                img.cols,
                img.rows,
                img.step,
                QImage::Format_RGB888);

    // Вывод в QLabel
    ui->cameraLabel->setPixmap(QPixmap::fromImage(qimg).scaled(
        ui->cameraLabel->size(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation));
}
