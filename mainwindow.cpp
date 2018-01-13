#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setEnabled(false);
    this->setWindowTitle("数字轮询");
    fileMake();
    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timerSlot()));
    b = true;
    FILE *fp = fopen("number.txt","r");
    if(fp < 0)  return;
    char buff[100];
    fgets(buff,sizeof(buff),fp);
    QString str;
    str.sprintf("%s",buff);
    fclose(fp);
    str.trimmed();
    int index = str.indexOf("=");
    qDebug() << index;
    qDebug() << str;
    str.remove(0,index+2);
    str = str.left(str.length() - 1);
    qDebug() << str;
    m_nTime = str.toInt();
    qDebug() << m_nTime;
    timer->start(m_nTime*1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//文件读取
void MainWindow::fileMake()
{
    FILE *fp = fopen("number.txt","r");
    if(fp < 0)
    {
        return;
    }
    char buff[100];
    memset(buff,0,sizeof(buff));
    fgets(buff,sizeof(buff),fp);
    QString qstrBuff;
    while(fgets(buff,sizeof(buff),fp) != NULL)
    {
        qstrBuff.append(buff);
    }
    fileList = fileList2 = qstrBuff;

}
//按钮开始
void MainWindow::on_btn_clicked()
{
}
//定时器槽函数
void MainWindow::timerSlot()
{
    int i = fileList.indexOf("*");
    QString str = fileList.mid(0,i);
    fileList.remove(0,i+1);

    ui->lineEdit->setText(str);
    if(fileList.size() == 0)
    {
         fileList = fileList2;
    }
}
