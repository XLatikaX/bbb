#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort>
#include <QtNetwork>
#include <QAxObject>
#include <QProgressDialog>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>


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
            QMessageBox::critical(this,"خطا","خطا در اتصال به دستگاه 2");
        }
    }

    progress.setValue(100);

}

void MainWindow::dev_connect2(QString ip1, int p1)
{

    QProgressDialog progress(tr("در حال اتصال به دستگاه 1"),tr("لطفا منتظر بمانید "),0,100);
    progress.setWindowModality(Qt::WindowModal);

    progress.setValue(0);
    progress.setWindowTitle(tr("نرم افزار"));

    progress.show();

    progress.setValue(25);

    if(zk1->dynamicCall("Connect_Net(string, int)",ip1,p1) == true)
        zk1->dynamicCall("RegEvent(int, int)",1,65535);
    else {
        progress.setValue(65);
        QMessageBox::critical(this,"خطا","خطا در اتصال به دستگاه 1");
    }

    progress.setValue(100);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::uploadUserToDevice(int id, QString name, QString card, QString pass)
{
    QList<QVariant> inplist;
    QVariant dwMachineNumber(1);
    QVariant dwEnrollNumber(id);
    QVariant Name(name);
    QVariant Password(pass);
    QVariant Privilege(0);
    QVariant Enabled(true);

    inplist << dwMachineNumber << dwEnrollNumber << Name << Password  << Privilege << Enabled ;


   // qDebug()<<inplist;
    //device 1
    if(zk1->dynamicCall("EnableDevice(int,bool)",1,false) == true){
        zk1->dynamicCall("SetStrCardNumber(string)",card);
        if(zk1->dynamicCall("SSR_SetUserInfo(int,int,string,string,int,bool)",inplist) == true)
            QMessageBox::information(this,tr("دستگاه"),tr("اطلاعات در دستگاه 1 با موفقیت ذخیره شد"));
        else{
            QString err=getDeviceError(1);

            QMessageBox::critical(this,tr("دستگاه"),tr("خطا در ذخیره اطلاعات در دستگاه 1\n")+ err);
        }
        zk1->dynamicCall("EnableDevice(int,bool)",1,true);

        if(ui->checkBox->isChecked()){
            //device 2
            if(zk2->dynamicCall("EnableDevice(int,bool)",1,false) == true){
                zk2->dynamicCall("SetStrCardNumber(string)",card);
                if(zk2->dynamicCall("SSR_SetUserInfo(int,int,string,string,int,bool)",inplist) == true)
                     QMessageBox::critical(this,tr("دستگاه"),tr("اطلاعات در دستگاه 2 با موفقیت ذخیره شد"));
                else{
                    QString err=getDeviceError(2);

                    QMessageBox::critical(this,tr("دستگاه"),tr("خطا در ذخیره اطلاعات در دستگاه 2\n")+ err);
                }
                zk2->dynamicCall("EnableDevice(int,bool)",1,true);
            }

            else{
                QMessageBox::critical(this,tr("دستگاه"),tr("خطا در اتصال به دستگاه 2"));
            }
        }

    }
    else{
       QMessageBox::critical(this,tr("دستگاه"),tr("خطا در اتصال به دستگاه 1"));
    }

}

QString MainWindow::getDeviceError(int devID)
{
    QList<QVariant> inplist;
    QVariant ans(-1);
    inplist << ans;
    if(devID == 1)
        zk1->dynamicCall("GetLastError(int&)",inplist);
    if(devID == 2)
        if(ui->checkBox->isChecked())
            zk2->dynamicCall("GetLastError(int&)",inplist);

    QString msg = tr("خطای شماره  " )+ inplist.at(0).toString();
    return msg;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int MainWindow::getDeviceStatus(int command){

    QList<QVariant> inplist1;
    QVariant dwMachineNumber(1);
    QVariant cmd(command);//user remaind capacity
    QVariant ans(0);
    inplist1 << dwMachineNumber <<  cmd << ans  ;


    if(zk1->dynamicCall("EnableDevice(int,bool)",1,false) == true){
        zk1->dynamicCall("GetDeviceStatus(int,int,int&)",inplist1);
        zk1->dynamicCall("EnableDevice(int,bool)",1,true);
    }
    return inplist1.at(2).toInt();
}

void MainWindow::setFingerprint(QString id){

    QList<QVariant> inplist;
    QVariant dwMachineNumber(1);
    QVariant dwEnrollNumber(id);
    QVariant fingerIndex(ui->lineEdit_4->text().toInt());
    QVariant flag(1);


    inplist << dwMachineNumber << dwEnrollNumber << fingerIndex ;


    // SSR_DelUserTmpExt(iMachineNumber, sUserID, iFingerIndex);
    // StartEnrollEx(sUserID, iFingerIndex, iFlag)
    //device 1
    if(zk1->dynamicCall("EnableDevice(int,bool)",1,false)== true){

        zk1->dynamicCall("SSR_DelUserTmpExt(int,string,int)",inplist);

        inplist.clear();

        inplist <<  dwEnrollNumber << fingerIndex << flag ;

        zk1->dynamicCall("StartEnrollEx(string,int,int)",inplist);

        zk1->dynamicCall("EnableDevice(int,bool)",1,true);
    }
    else{
        QMessageBox::critical(this,tr("دستگاه"),tr("خطا در اتصال به دستگاه 1"));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::onVerfy_1(QString EnrollNumber, int IsInValid, int AttState, int VerifyMethod, int Year, int Month, int Day, int Hour, int Minute, int Second, int WorkCode){
//    Q_UNUSED(IsInValid)
//    Q_UNUSED(AttState)
//    Q_UNUSED(VerifyMethod)
//    Q_UNUSED(Year)
//    Q_UNUSED(Month)
//    Q_UNUSED(Day)
//    Q_UNUSED(Hour)
//    Q_UNUSED(Minute)
//    Q_UNUSED(Second)
//    Q_UNUSED(WorkCode)
////    qDebug()<<"ID:     "<<EnrollNumber;
// //   qDebug()<<"dev:     "<< serialDevKomod_request;
//    if(/*!twoDevice &&*/ serialDevKomod_request){
//        if(dev2Timer){
//            dev2Timer = false;
//            QTimer::singleShot(2000, this, SLOT(dev2OnTimer()));
//            dev1Timer = false;
//            // zk1->dynamicCall("RegEvent(int, int)",1,2048);
//            QTimer::singleShot(2000, this, SLOT(dev1OnTimer()));
//            devSingleHotTimer->stop();
//            serialDevKomod_request = false;
//            emit userIDKomod(EnrollNumber.toInt());
//        }
//    }
//    else if(dev1Timer && !serialDevKomod_request){
//        dev1Timer = false;
//        // zk1->dynamicCall("RegEvent(int, int)",1,2048);
//        QTimer::singleShot(2000, this, SLOT(dev1OnTimer()));
//        emit userIDInOut(EnrollNumber.toInt());
//    }

    qDebug()<<EnrollNumber;
    QMessageBox::warning(nullptr,"user",EnrollNumber+'\n'+
                         QString::number(IsInValid)+'\n'+
                         QString::number(AttState)+'\n'+
                         QString::number(VerifyMethod)+'\n'+
                         QString::number(Year)+'\n'+
                         QString::number(Month)+'\n'+
                         QString::number(Day)+'\n'+
                         QString::number(Hour)+'\n'+
                         QString::number(Minute)+'\n'+
                         QString::number(Second)+'\n'+
                         QString::number(WorkCode));
}

void MainWindow::onVerfy_2(QString EnrollNumber, int IsInValid, int AttState, int VerifyMethod, int Year, int Month, int Day, int Hour, int Minute, int Second, int WorkCode)
{
    qDebug()<<EnrollNumber;
    QMessageBox::warning(nullptr,"user",EnrollNumber+'\n'+
                         QString::number(IsInValid)+'\n'+
                         QString::number(AttState)+'\n'+
                         QString::number(VerifyMethod)+'\n'+
                         QString::number(Year)+'\n'+
                         QString::number(Month)+'\n'+
                         QString::number(Day)+'\n'+
                         QString::number(Hour)+'\n'+
                         QString::number(Minute)+'\n'+
                         QString::number(Second)+'\n'+
                         QString::number(WorkCode));
}

void MainWindow::onRegisterFinger(QString EnrollNumber, int FingerIndex, int ActionResult, int TemplateLength)
{
    Q_UNUSED(FingerIndex)
    Q_UNUSED(ActionResult)
    Q_UNUSED(TemplateLength)

        // emit fingerRegister(EnrollNumber.toInt());
        QMessageBox::warning(nullptr,"user",EnrollNumber+'\n'+
                             QString::number(FingerIndex)+'\n'+
                             QString::number(ActionResult)+'\n'+
                             QString::number(TemplateLength));

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QVector<QVector<QString>> MainWindow::getUsersData(int sts)
{
    QVector<QVector<QString>> ans;
    if(sts == 2){
        QList<QVariant> inplist;
        QList<QVariant> inplist1;
        QList<QVariant> inplist2;
        QVariant dwMachineNumber(1);
        QVariant dwEnrollNumber("");
        QVariant Name("");
        QVariant cardID("");
        QVariant fingerIndx(6);
        QVariant Password("");
        QVariant Privilege(0);
        QVariant Enabled(false);
        QVariant sFPTmpData("");
        QVariant iFlag(0);
        QVariant iFPTmpLength(0);

        inplist << dwMachineNumber << dwEnrollNumber << Name << Password  << Privilege << Enabled ;

        inplist1<<cardID;

        inplist2 << dwMachineNumber << dwEnrollNumber << fingerIndx << iFlag  << sFPTmpData << iFPTmpLength ;

        if(zk1->dynamicCall("EnableDevice(int,bool)",dwMachineNumber,false) == true){

            zk1->dynamicCall("ReadAllUserID(int)",dwMachineNumber); //Read To Memory
            zk1->dynamicCall("ReadAllTemplate(int)",dwMachineNumber);





            while(zk1->dynamicCall("SSR_GetAllUserInfo(long, QString&,QString&, QString&, int&, bool&)",inplist) == true){
                zk1->dynamicCall("GetStrCardNumber(QString&)",inplist1);// Read Card ID
                inplist2[1] = inplist.at(1);

                zk1->dynamicCall("GetUserTmpExStr(int, int, int, int&, QString&, int&)",inplist2);


                QVector <QString> tmp;
                QString detect="";
                tmp.append(inplist.at(1).toString());

                if(inplist.at(3).toString().length() > 1)
                    detect += "رمز، ";
                if(inplist1.at(0).toString().length() > 1)
                    detect += "کارت، ";
                if(inplist2.at(4).toString().length() > 10 )
                    detect += "انگشت، ";
                qDebug()<<inplist2.at(4).toString()<<"@@@@@@@@@@@@@@@"<<inplist2.at(4).toString().length()<<"@@"<<inplist2.at(2).toString()<<"@@"<<inplist2.at(1).toString();

                tmp.append(detect.mid(0,detect.length() -2));

                ans.append(tmp);


            }


            zk1->dynamicCall("EnableDevice(int,bool)",dwMachineNumber,true);


        }
        else{
           QMessageBox::critical(this,tr("دستگاه"),tr("خطا در اتصال به دستگاه 1"));
        }

    }
    return ans;
}


bool MainWindow::synktwoDevice(QVector <QVector <QString>> inp)
{
    if(ui->checkBox->isChecked())   // twoDevice
    {
        QList<QVariant> inplist;
        QList<QVariant> inplist1;
        QList<QVariant> inplist2;
        QVariant dwMachineNumber(1);
        QVariant dwEnrollNumber("");
        QVariant Name("");
        QVariant cardID("");
        QVariant fingerIndx(6);
        QVariant Password("");
        QVariant Privilege(0);
        QVariant Enabled(false);
        QVariant sFPTmpData("");
        QVariant iFlag(0);
        QVariant iFPTmpLength(0);

        inplist << dwMachineNumber << dwEnrollNumber << Name << Password  << Privilege << Enabled ;

        inplist1<<cardID;

        inplist2 << dwMachineNumber << dwEnrollNumber << fingerIndx << iFlag  << sFPTmpData << iFPTmpLength ;

        QProgressDialog progress(tr("در حال همسان سازی اطلاعات"),tr("لطفا منتظر بمانید "),0,100);
        progress.setWindowModality(Qt::WindowModal);

        progress.setWindowTitle("نرم افزار");

        progress.setValue(0);

        progress.show();

        bool ok = true;


        if(zk1->dynamicCall("EnableDevice(int,bool)",dwMachineNumber,false) == false){
            QMessageBox::critical(this,tr("خطا در اتصال به دستگاه 1"),tr("دستگاه"));
            return false;
        }

        if(zk2->dynamicCall("EnableDevice(int,bool)",dwMachineNumber,false) == false){
            QMessageBox::critical(this,tr("خطا در اتصال به دستگاه 2"),tr("دستگاه"));
            return false;
        }

        int max = getDeviceStatus(2);
        int count = 0;
        QString error = tr("خطا در همسان سازی کاربران زیر:\n");

        QString msg = tr("تعداد کاربران همسان شده (از " )+ QString::number(max) + tr("  کاربر):  ");
        progress.setLabelText(msg+QString::number(count));
        progress.setValue(0);


        zk1->dynamicCall("ReadAllUserID(int)",dwMachineNumber); //Read To Memory
        zk1->dynamicCall("ReadAllTemplate(int)",dwMachineNumber);



        while(zk1->dynamicCall("SSR_GetAllUserInfo(long, QString&,QString&, QString&, int&, bool&)",inplist) == true){
            zk1->dynamicCall("GetStrCardNumber(QString&)",inplist1);// Read Card ID
            inplist2[1] = inplist.at(1);

            zk1->dynamicCall("GetUserTmpExStr(int, int, int, int&, QString&, int&)",inplist2) ;


            QList<QVariant> inplist3;
            QVariant dwMachineNumber1(1);
            QVariant dwEnrollNumber1(inplist.at(1));
            for(int i=0;i<inp.length();i++){
                if(inp.at(i).at(0) == inplist.at(1).toString()){
                    inplist[2] = inp.at(i).at(1);
                    inp.remove(i);
                }
            }
            QVariant Name1(inplist.at(2));
            QVariant Password1(inplist.at(3));
            QVariant Privilege1(inplist.at(4));
            QVariant Enabled1(inplist.at(5));

            inplist3 << dwMachineNumber1 << dwEnrollNumber1 << Name1 << Password1  << Privilege1 << Enabled1 ;


            QList<QVariant> inplist10;
            QVariant dwMachineNumber(1);
            QVariant sEnrollNumber(dwEnrollNumber1);
            QVariant iBackupNumber(12);
            inplist10 <<dwMachineNumber << sEnrollNumber << iBackupNumber;

            zk2->dynamicCall("SSR_DeleteEnrollData(int,QString,int)",inplist10 );


            zk2->dynamicCall("SetStrCardNumber(string)",inplist1);
            zk2->dynamicCall("SSR_SetUserInfo(int,int,string,string,int,bool)",inplist3);

            inplist3 << dwMachineNumber << inplist2.at(1) << fingerIndx;

            zk2->dynamicCall("SSR_DelUserTmpExt(int,string,int)",inplist3);

            inplist3.clear();
            inplist3 << inplist2.at(0) << inplist2.at(1) << inplist2.at(2) << inplist2.at(3) << inplist2.at(4);


            if(inplist2.at(4).toString().length() > 10){
                if(zk2->dynamicCall("SetUserTmpExStr(int,QString,int,int,QString)",inplist3) == false){

                    error += sEnrollNumber.toString() + ",";
                    ok = false;
                }
            }
            count ++;
            int val = (count / max ) * 100;
            if(val > 99)
                val = 99;
            progress.setValue(val);

        }

        zk1->dynamicCall("EnableDevice(int,bool)",dwMachineNumber,true);
        zk2->dynamicCall("EnableDevice(int,bool)",dwMachineNumber,true);

        progress.setValue(100);

        if(!ok){

            QMessageBox::critical(this,tr("دستگاه"), error.mid(0,error.length()-1));
            return false;
        }
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// conncet
void MainWindow::on_pushButton_clicked()
{
    initFingerDevice("192.168.1.201","192.168.1.202",4370,4370);
}

// conncet fast
void MainWindow::on_pushButton_2_clicked()
{
    zk1->setControl("zkemkeeper.ZKEM.1");
    zk2->setControl("zkemkeeper.ZKEM.1");

    if(zk1->dynamicCall("Connect_Net(string, int)","192.168.1.201",4370) == true)
    {
        connect(zk1,SIGNAL(OnAttTransactionEx(QString , int , int , int , int , int , int , int , int , int , int )),SLOT(onVerfy_1(QString , int , int , int , int , int , int , int , int , int , int )));
        connect(zk1,SIGNAL(OnEnrollFingerEx(QString , int , int , int )),SLOT(onRegisterFinger(QString , int , int , int)));
        zk1->dynamicCall("RegEvent(int, int)",1,65535);
        qDebug("connected 1");
    }
    else
        QMessageBox::critical(this,"خطا","خطا در اتصال به دستگاه 1");

    /////////////////////////////

    if (ui->checkBox->isChecked())
    {
        if(zk2->dynamicCall("Connect_Net(string, int)","192.168.1.202",4370) == true)
        {
            connect(zk2,SIGNAL(OnAttTransactionEx(QString , int , int , int , int , int , int , int , int , int , int )),SLOT(onVerfy_2(QString , int , int , int , int , int , int , int , int , int , int )));
            zk2->dynamicCall("RegEvent(int, int)",1,65535);
            qDebug("connected 2");
        }
        else
            QMessageBox::critical(this,"خطا","خطا در اتصال به دستگاه 2");
    }


}

// send
void MainWindow::on_pushButton_3_clicked()
{
    QString card = ui->lineEdit_5->text();
    // id - name - card - pass
    uploadUserToDevice(ui->lineEdit->text().toInt(),ui->lineEdit_2->text(),card.length()>1 ? card : "","");
}

// set finger
void MainWindow::on_pushButton_4_clicked()
{
    if(getDeviceStatus(10) > 0){
            setFingerprint(ui->lineEdit_3->text());
    }
    else
        QMessageBox::information(nullptr,tr("دستگاه"),tr("  ظرفیت دستگاه برای ثبت اثر انگشت جدید تکمیل است  "));
}

// Off
void MainWindow::on_pushButton_5_clicked()
{
    zk1->dynamicCall("PowerOffDevice(int)",1);
    zk2->dynamicCall("PowerOffDevice(int)",1);
}

// Info
void MainWindow::on_pushButton_6_clicked()
{
    QList<QVariant> inplist1;
    QList<QVariant> inplist2;
    QVariant dwMachineNumber(1);
    QVariant ans("");
    inplist1 << dwMachineNumber << ans;
    inplist2 << dwMachineNumber << ans;

    zk1->dynamicCall("GetFirmwareVersion(int,string&)",inplist1);
    zk1->dynamicCall("GetDeviceIP(int,string&)",inplist2);
    zk1->dynamicCall("Beep(int)",2000);

    qDebug()<<inplist1.at(1).toString();
    qDebug()<<inplist2.at(1).toString();

    /////////////////////////////////////////////

    QList<QVariant> inplist3;
    QList<QVariant> inplist4;
    QVariant ans2("");
    inplist3 << dwMachineNumber << ans2;
    inplist4 << dwMachineNumber << ans2;

    zk2->dynamicCall("GetFirmwareVersion(int,string&)",inplist3);
    zk2->dynamicCall("GetDeviceIP(int,string&)",inplist4);
    zk2->dynamicCall("Beep(int)",2000);

    qDebug()<<inplist3.at(1).toString();
    qDebug()<<inplist4.at(1).toString();
}

// copy
void MainWindow::on_pushButton_7_clicked()
{
    QVector <QVector<QString>> usr;
    for(int i=0;i<ui->table_device->rowCount();i++) {
        QVector<QString> tmp;
        tmp.append(ui->table_device->item(i,0)->text());
        tmp.append(ui->table_device->item(i,1)->text());
        usr.append(tmp);
    }
    if(usr.length()>0){
        if(synktwoDevice(usr))
            QMessageBox::information(nullptr, QObject::tr("دستگاه"),
                                     QObject::tr("  همسان سازی با موفقیت انجام شد.  ")
                                     , QMessageBox::Ok);
        else{
            QMessageBox::information(nullptr, QObject::tr("دستگاه"),
                                     QObject::tr("  خطا در همسان سازی  ")
                                     , QMessageBox::Ok);
        }

    }
    else{
        QMessageBox::information(nullptr, QObject::tr("دستگاه"),
                                 QObject::tr("  داده ای برای همسان سازی وجود ندارد  ")
                                 , QMessageBox::Ok);
    }
}

// Load
void MainWindow::on_pushButton_8_clicked()
{
    ui->table_device->setRowCount(0);
    QVector<QVector<QString>> inplist = getUsersData(2);

    for(int i=0; i<inplist.length(); i++)
    {
        ui->table_device->insertRow ( ui->table_device->rowCount() );

        int row = ui->table_device->rowCount()-1;


        ui->table_device->setItem   ( row, 0, new QTableWidgetItem(inplist.at(i).at(0)));

        QSqlQuery query ("select * from ManMember where MemberID = '"+inplist.at(i).at(0)+"'");

        if (query.next())
        {
            QString name = query.value(3).toString() + " " + query.value(4).toString(); // name family
            ui->table_device->setItem   ( row, 1, new QTableWidgetItem(name));
        }
        else{
            ui->table_device->setItem   ( row, 1, new QTableWidgetItem(" "));
        }

        ui->table_device->setItem   ( row, 2, new QTableWidgetItem(inplist.at(i).at(1)));

    }
}

// message
void MainWindow::on_pushButton_9_clicked()
{
    QList<QVariant> inplist1;
    QVariant dwMachineNumber(1);
    QVariant ID(1);
    QVariant Tag(253);
    QVariant ValidMinutes(1);
    QVariant StartTime("2025-08-12 12:25:00");
    QVariant Content("ضصضیضص");
    inplist1 << dwMachineNumber << ID << Tag << ValidMinutes << StartTime << Content;

    zk1->dynamicCall("SetSMS(int,int,int,int,string,string)",inplist1);
}

// show
void MainWindow::on_pushButton_10_clicked()
{
    QList<QVariant> inplist1;
    QVariant Row(5);
    QVariant Col(5);
    QVariant Text(QString(ui->lineEdit_6->text()));

    inplist1 << Row << Col << Text;

    zk1->dynamicCall("WriteLCD(int,int,string)",inplist1);
}

// clear
void MainWindow::on_pushButton_11_clicked()
{
    zk1->dynamicCall("ClearLCD()");
}

//show 2
void MainWindow::on_pushButton_12_clicked()
{
    QList<QVariant> inplist1;
    QVariant komod("5                ");
    QVariant name("name family      ");
    QVariant mandeh("23               ");
    QVariant etebar("30               ");
    QVariant data("in database      ");
    inplist1 << komod << name << mandeh << etebar << data;

    QList<QVariant> inplist2;
    QVariant one(33);
    QVariant two(2);
    QVariant three(3);
    QString text = "5                name family      23               30               in database      ";
    inplist2 << one << two << three << text;


    zk1->dynamicCall("WriteLcdEx(int,int,int,string)",inplist2);
}


// 1
void MainWindow::on_pushButton_13_clicked()
{
    QList<QVariant> inplist1;
    QVariant machine(1);
    QVariant status(ui->lineEdit_7->text().toInt());
    QVariant ans(0);

    inplist1 << machine << status << ans;

    zk1->dynamicCall("GetDeviceStatus(int,int,int&)",inplist1);

    QMessageBox::critical(this,inplist1[1].toString(),inplist1[2].toString());
}

// 2
void MainWindow::on_pushButton_14_clicked()
{
    QList<QVariant> inplist1;
    QVariant machine(1);
    QVariant ans("");

    inplist1 << machine << ans;

    zk1->dynamicCall("GetSDKVersion(int,string&)",inplist1);
    qDebug()<<inplist1[1];
}

// 3
void MainWindow::on_pushButton_15_clicked()
{
    QList<QVariant> inplist1;
    QVariant machine(ui->lineEdit_7->text().toInt());

    inplist1 << machine;

    zk1->dynamicCall("PlayVoiceByIndex(int)",inplist1);
}

// 4
void MainWindow::on_pushButton_16_clicked()
{
    QList<QVariant> inplist1;
    QVariant dwMachineNumber(1);
    QVariant ID(1);
    QVariant Tag(253);//public
    QVariant ValidMinutes(1);
    QVariant StartTime(QDate::currentDate().toString("yyyy-MM-dd") + " " + QTime::currentTime().toString("HH:mm:ss")); //"2025-08-12 11:57:00"
    QVariant Content(ui->lineEdit_6->text()); //"abcd2"

    inplist1 << dwMachineNumber << ID << Tag << ValidMinutes << StartTime << Content;

    zk1->dynamicCall("SetSMS(int,int,int,int,string,string)",inplist1);
}

// 5
void MainWindow::on_pushButton_17_clicked()
{
    QList<QVariant> inplist1;
    QVariant dwMachineNumber(1);

    QVariant Content(""); //"abcd2"

    inplist1 << dwMachineNumber << Content;

    zk1->dynamicCall("GetDeviceIP(int,string&)",inplist1);
    qDebug()<<inplist1[1];
}

// 6
void MainWindow::on_pushButton_18_clicked()
{

    // QList<QVariant> inplist1;
    // QVariant dwMachineNumber(1);
    // QVariant dwEnrollNumber("2");
    // QVariant dwFaceIndex(50); // ui->lineEdit_4->text().toInt()
    // QVariant TmpData("");
    // QVariant TmpLength(100);

    // inplist1 << dwMachineNumber << dwEnrollNumber << dwFaceIndex << TmpData << TmpLength;

    // zk1->dynamicCall("SetUserFaceStr(int,QString,int,QString&,int)", inplist1);
    // qDebug()<<inplist1[3];
    // qDebug()<<inplist1[4];


    QList<QVariant> inplist;
    QVariant dwMachineNumber(1);
    QVariant dwEnrollNumber("2");
    QVariant fingerIndex(111);
    QVariant flag(0);


    inplist << dwMachineNumber << dwEnrollNumber << fingerIndex ;


    // SSR_DelUserTmpExt(iMachineNumber, sUserID, iFingerIndex);
    // StartEnrollEx(sUserID, iFingerIndex, iFlag)
    //device 1
    if(zk1->dynamicCall("EnableDevice(int,bool)",1,false)== true){

        zk1->dynamicCall("SSR_DelUserTmpExt(int,string,int)",inplist);

        inplist.clear();

        inplist <<  dwEnrollNumber << fingerIndex << flag ;

        zk1->dynamicCall("StartEnrollEx(string,int,int)",inplist);

        zk1->dynamicCall("EnableDevice(int,bool)",1,true);
    }
    else{
        QMessageBox::critical(this,tr("دستگاه"),tr("خطا در اتصال به دستگاه 1"));
    }
}

// 7
void MainWindow::on_pushButton_19_clicked()
{
    zk1->dynamicCall("SetDeviceTime(int)", 1);
    zk2->dynamicCall("SetDeviceTime(int)", 1);
}

