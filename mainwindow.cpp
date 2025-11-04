#include <>

"mainwindow.h"
#include <>

"ui_mainwindow.h"
#include <qtserialport>
#include <qtnetwork>
#include <qaxobject>
#include <qprogressdialog>
#include <qdebug>
#include <qmessagebox>
#include <qtimer>
#include <qsqldatabase>
#include <qsqlquery>
#include <qsqlquerymodel>
#include <qsqltablemodel>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("GymDB.db");
    db.open();
    zk1 = new QAxObject(this);
    zk2 = new QAxObject(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::initFingerDevice(QString ip1, QString ip2, int port1, int port2)
{
    // this test
    for(int i = 1; i <= 10; i++) {
        qDebug() << "i = " << i;
    }
    zk1->setControl("zkemkeeper.ZKEM.1");
    zk2->setControl("zkemkeeper.ZKEM.1");
    
    dev_connect(ip1,ip2,port1,port2);
}
void MainWindow::dev_connect(QString ip1, QString ip2, int p1, int p2)
{
    QProgressDialog progress(tr("در حال همسان سازی اطلاعات"),tr("لطفا منتظر بمانید "),0,100);
    progress.setWindowModality(Qt::WindowModal);
    progress.setValue(0);
    progress.setWindowTitle(tr("نرم افزار"));
    progress.show();
    progress.setValue(25);
    progress.setLabelText(tr("در حال اتصال به دستگاه 1"));
    
    if(zk1->dynamicCall("Connect_Net(string, int)",ip1,p1) == true){
        connect(zk1,SIGNAL(OnAttTransactionEx(QString , int , int , int , int , int , int , int , int , int , int )),SLOT(onVerfy_1(QString , int , int , int , int , int , int , int , int , int , int )));
        zk1->dynamicCall("RegEvent(int, int)",1,65535);
        qDebug("connected 1");
    }
    else {
        progress.setValue(65);
//        if(ui->checkBox->isChecked())
//            progress.setLabelText(tr("در حال اتصال به دستگاه 1"));
        QMessageBox::critical(this,"خطا","خطا در اتصال به دستگاه 1");
    }
    progress.setValue(65);
    
    if(ui->checkBox->isChecked()){
        progress.setLabelText(tr("در حال اتصال به دستگاه 2"));
        
        if(zk2->dynamicCall("Connect_Net(string, int)",ip2,p2) == true){
            connect(zk2,SIGNAL(OnAttTransactionEx(QString , int , int , int , int , int , int , int , int , int , int )),SLOT(onVerfy_2(QString , int , int , int , int , int , int , int , int , int , int )));
            zk2->dynamicCall("RegEvent(int, int)",1,65535);
            qDebug("connected 2");
        }
        else {
            progress.setValue(99);
