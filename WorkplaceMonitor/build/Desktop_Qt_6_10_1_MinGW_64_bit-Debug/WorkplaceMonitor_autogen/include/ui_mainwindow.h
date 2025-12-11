/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QGroupBox *groupBox;
    QPushButton *pushButton;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_2;
    QLabel *temperatureLabel;
    QLabel *lightLabel;
    QLabel *CO2Label;
    QLabel *cameraLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 20, 201, 20));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(40, 100, 120, 80));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 40, 90, 29));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(470, 100, 120, 80));
        pushButton_2 = new QPushButton(groupBox_2);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(10, 40, 90, 29));
        temperatureLabel = new QLabel(centralwidget);
        temperatureLabel->setObjectName("temperatureLabel");
        temperatureLabel->setGeometry(QRect(70, 230, 111, 20));
        lightLabel = new QLabel(centralwidget);
        lightLabel->setObjectName("lightLabel");
        lightLabel->setGeometry(QRect(70, 270, 111, 20));
        CO2Label = new QLabel(centralwidget);
        CO2Label->setObjectName("CO2Label");
        CO2Label->setGeometry(QRect(70, 310, 111, 20));
        cameraLabel = new QLabel(centralwidget);
        cameraLabel->setObjectName("cameraLabel");
        cameraLabel->setGeometry(QRect(310, 240, 281, 231));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\274\320\276\320\275\320\270\321\202\320\276\321\200\320\270\320\275\320\263 \321\200\320\260\320\261\320\276\321\207\320\265\320\263\320\276 \320\274\320\265\321\201\321\202\320\260", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\224\320\260\321\202\321\207\320\270\320\272\320\270", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\262\320\272\320\273.", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\320\232\320\260\320\274\320\265\321\200\320\260", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\320\262\320\272\320\273.", nullptr));
        temperatureLabel->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\274\320\277\320\265\321\200\320\260\321\202\321\203\321\200\320\260:", nullptr));
        lightLabel->setText(QCoreApplication::translate("MainWindow", "\320\236\321\201\320\262\320\265\321\211\320\265\320\275\320\275\320\276\321\201\321\202\321\214:", nullptr));
        CO2Label->setText(QCoreApplication::translate("MainWindow", "CO2:", nullptr));
        cameraLabel->setText(QCoreApplication::translate("MainWindow", "\320\222\320\270\320\264\320\265\320\276 \320\275\320\265\321\202!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
