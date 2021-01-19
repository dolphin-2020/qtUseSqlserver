#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QDebug>
#include<QtSql>
#include<QtNetwork>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString ipAddr;
        QList<QHostAddress> list = QNetworkInterface::allAddresses();
        foreach (QHostAddress address, list) {
            if (address.protocol() == QAbstractSocket::IPv4Protocol) {
                ipAddr = address.toString();
                break;
            }
        }
        qDebug()<<ipAddr;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");   //数据库驱动类型为SQL Server
    qDebug()<<"ODBC driver?"<<db.isValid();
    QString dsn = QString::fromLocal8Bit("dolphin");      //数据源名称
    db.setHostName("192.168.100.113");//选择本地主机，127.0.1.1 或者localhost 或者192.168.100.113本机ip
    db.setDatabaseName(dsn);                            //设置数据源名称
    db.setUserName("sa");                               //登录用户
    db.setPassword("810549lqg");                           //密码
    if(!db.open())                                      //打开数据库
        qDebug()<<db.lastError().text();
    else
        qDebug()<<"database open success!";
    QSqlQuery query;
    query.exec("select * from studentInfo");
    while(query.next())
    {
        QSqlRecord rec=query.record();
        for(int i=0;i<rec.count();++i)
        {
            qDebug()<<query.value(i).toString();
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

