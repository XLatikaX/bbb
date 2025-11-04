#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAxObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initFingerDevice(QString ip1, QString ip2,int port1, int port2);
    void dev_connect(QString ip1,QString ip2,int p1,int p2);
    void dev_connect2(QString ip1,int p1);

    ///////////////////////////////////////////////////////////////////

    void uploadUserToDevice(int id, QString name, QString card, QString pass);
    QString getDeviceError(int devID);

    ///////////////////////////////////////////////////////////////////

    int getDeviceStatus(int command);
    void setFingerprint(QString id);

    ///////////////////////////////////////////////////////////////////

    QVector<QVector<QString> > getUsersData(int sts);
    bool synktwoDevice(QVector<QVector<QString> > inp);

private slots:
    void onVerfy_1(QString EnrollNumber, int IsInValid, int AttState, int VerifyMethod, int Year, int Month, int Day, int Hour, int Minute, int Second, int WorkCode);
    void onVerfy_2(QString EnrollNumber, int IsInValid, int AttState, int VerifyMethod, int Year, int Month, int Day, int Hour, int Minute, int Second, int WorkCode);

    void onRegisterFinger(QString EnrollNumber, int FingerIndex, int ActionResult, int TemplateLength);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

private:
    Ui::MainWindow *ui;
    QAxObject *zk1, *zk2;
};
#endif // MAINWINDOW_H
