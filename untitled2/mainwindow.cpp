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
    db.setHostName("169.254.166.101");//选择本地主机，127.0.1.1 或者localhost 或者192.168.100.113本机ip
    db.setDatabaseName(dsn);                            //设置数据源名称
    db.setUserName("sa");                               //登录用户
    db.setPassword("810549lqg");                           //密码
    if(!db.open())                                      //打开数据库
        qDebug()<<db.lastError().text();
    else
        qDebug()<<"database open success!";
    QSqlQuery query;

    query=QSqlQuery(db);
    QString mInsertStr = QString("INSERT INTO studentInfo(" "name, " "age)" "VALUES(" "'Lia', " "49);");
    query.prepare(mInsertStr); if(!query.exec()){
        qDebug()<<"good";
    }

//      query.prepare("INSERT INTO xx (xx,xx,xx,xx,xx,xx) VALUES (?,?,?,?,?,?)");
//      query.addBindValue(xx);
//      query.addBindValue(xx);
//      query.addBindValue(txx);
//      query.addBindValue(xx);
//      query.addBindValue(xx);
//      query.addBindValue(xx);
//      query.exec();

//    //删
//      QSqlQuery query;
//      query.prepare("DELETE FROM xx WHERE xx = ?");
//      query.addBindValue(xx);
//      query.exec();

//    //改
//    QSqlQuery query;
//      query.prepare("UPDATE xx SET xx = ?,xx = ?,xx = ?,xx = ?,xx = ? WHERE xx = ?");
//      query.addBindValue(xx);
//      query.addBindValue(xx);
//      query.addBindValue(xx);
//      query.addBindValue(xx);
//      query.addBindValue(xx);
//      query.addBindValue(xx);
//      query.exec());

//    //查
//    QSqlQuery query;
//    query.exec("SELECT * FROM xx");
//    while (query.next()){
//    query.value(0);
//    query.value(1);

//    //删除表
//    QSqlQuery query;
//    query.exec("DROP TABLE xx);

//    //创建表
//      QString sql;
//      sql = "CREATE TABLE xx (";
//      sql += "xx int NOT NULL PRIMARY KEY,";
//      sql += "xx varchar(64) DEFAULT NULL,";
//      sql += "xx int DEFAULT NULL,";
//      sql += "xx numeric(15,0) DEFAULT NULL,";
//      sql += "xx int DEFAULT NULL,";
//      sql += "xx int DEFAULT NULL)";
//      query.prepare(sql);
//      query.exec();

    ///
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

