/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_5;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QTableWidget *table_device;
    QPushButton *pushButton_8;
    QCheckBox *checkBox;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QLineEdit *lineEdit_6;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QPushButton *pushButton_15;
    QPushButton *pushButton_16;
    QPushButton *pushButton_17;
    QPushButton *pushButton_18;
    QPushButton *pushButton_19;
    QPushButton *pushButton_20;
    QLineEdit *lineEdit_7;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1195, 811);
        QFont font;
        font.setPointSize(14);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(220, 50, 121, 41));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(390, 50, 121, 41));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(160, 179, 121, 31));
        lineEdit->setAlignment(Qt::AlignCenter);
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(160, 230, 121, 31));
        lineEdit_2->setAlignment(Qt::AlignCenter);
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(160, 330, 121, 41));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(480, 300, 121, 41));
        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(480, 180, 121, 31));
        lineEdit_3->setAlignment(Qt::AlignCenter);
        lineEdit_4 = new QLineEdit(centralwidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(480, 230, 121, 31));
        lineEdit_4->setAlignment(Qt::AlignCenter);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 180, 41, 31));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 230, 71, 31));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(430, 180, 51, 31));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(400, 230, 71, 31));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(80, 280, 71, 31));
        lineEdit_5 = new QLineEdit(centralwidget);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(160, 280, 121, 31));
        lineEdit_5->setAlignment(Qt::AlignCenter);
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(40, 430, 121, 41));
        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(40, 480, 121, 41));
        pushButton_7 = new QPushButton(centralwidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(690, 520, 121, 41));
        table_device = new QTableWidget(centralwidget);
        if (table_device->columnCount() < 3)
            table_device->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        table_device->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        table_device->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        table_device->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        table_device->setObjectName(QString::fromUtf8("table_device"));
        table_device->setGeometry(QRect(690, 20, 481, 491));
        QFont font1;
        font1.setFamily(QString::fromUtf8("B Nazanin"));
        font1.setPointSize(10);
        font1.setBold(true);
        table_device->setFont(font1);
        table_device->setLayoutDirection(Qt::RightToLeft);
        table_device->setFrameShape(QFrame::Box);
        table_device->setSortingEnabled(true);
        table_device->horizontalHeader()->setDefaultSectionSize(150);
        table_device->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        table_device->verticalHeader()->setVisible(false);
        pushButton_8 = new QPushButton(centralwidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(880, 520, 121, 41));
        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(29, 60, 131, 21));
        pushButton_9 = new QPushButton(centralwidget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(40, 610, 121, 41));
        pushButton_10 = new QPushButton(centralwidget);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(220, 580, 121, 41));
        pushButton_11 = new QPushButton(centralwidget);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(220, 640, 121, 41));
        lineEdit_6 = new QLineEdit(centralwidget);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(190, 530, 181, 41));
        QFont font2;
        font2.setFamily(QString::fromUtf8("B Nazanin"));
        font2.setPointSize(14);
        font2.setBold(true);
        lineEdit_6->setFont(font2);
        lineEdit_6->setAlignment(Qt::AlignCenter);
        pushButton_12 = new QPushButton(centralwidget);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setGeometry(QRect(440, 600, 121, 41));
        pushButton_13 = new QPushButton(centralwidget);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));
        pushButton_13->setGeometry(QRect(1040, 590, 80, 24));
        pushButton_14 = new QPushButton(centralwidget);
        pushButton_14->setObjectName(QString::fromUtf8("pushButton_14"));
        pushButton_14->setGeometry(QRect(1040, 620, 80, 24));
        pushButton_15 = new QPushButton(centralwidget);
        pushButton_15->setObjectName(QString::fromUtf8("pushButton_15"));
        pushButton_15->setGeometry(QRect(1040, 650, 80, 24));
        pushButton_16 = new QPushButton(centralwidget);
        pushButton_16->setObjectName(QString::fromUtf8("pushButton_16"));
        pushButton_16->setGeometry(QRect(1040, 680, 80, 24));
        pushButton_17 = new QPushButton(centralwidget);
        pushButton_17->setObjectName(QString::fromUtf8("pushButton_17"));
        pushButton_17->setGeometry(QRect(950, 590, 80, 24));
        pushButton_18 = new QPushButton(centralwidget);
        pushButton_18->setObjectName(QString::fromUtf8("pushButton_18"));
        pushButton_18->setGeometry(QRect(950, 620, 80, 24));
        pushButton_19 = new QPushButton(centralwidget);
        pushButton_19->setObjectName(QString::fromUtf8("pushButton_19"));
        pushButton_19->setGeometry(QRect(950, 650, 80, 24));
        pushButton_20 = new QPushButton(centralwidget);
        pushButton_20->setObjectName(QString::fromUtf8("pushButton_20"));
        pushButton_20->setGeometry(QRect(950, 680, 80, 24));
        lineEdit_7 = new QLineEdit(centralwidget);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(950, 710, 171, 24));
        lineEdit_7->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1195, 22));
        QFont font3;
        font3.setPointSize(10);
        menubar->setFont(font3);
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "connect", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "connect fast", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "send user", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "set finger", nullptr));
        lineEdit_4->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "ID :", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Name :", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "ID : ", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Finger :", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Card :", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "OFF", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Info", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Copy to 2", nullptr));
        QTableWidgetItem *___qtablewidgetitem = table_device->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\330\264\331\205\330\247\330\261\331\207 \330\271\330\266\331\210\333\214\330\252", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = table_device->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\331\206\330\247\331\205 \331\210 \331\206\330\247\331\205 \330\256\330\247\331\206\331\210\330\247\330\257\332\257\333\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = table_device->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\331\206\331\210\330\271 \330\264\331\206\330\247\330\263\330\247\333\214\333\214 \330\257\330\263\330\252\332\257\330\247\331\207 ", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "Two Device", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Message", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "Show", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        lineEdit_6->setText(QCoreApplication::translate("MainWindow", "Text Test", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow", "Show 2", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        pushButton_14->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        pushButton_15->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        pushButton_16->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        pushButton_17->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        pushButton_18->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        pushButton_19->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        pushButton_20->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
