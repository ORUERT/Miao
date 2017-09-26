#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    appAutoRun(1);
    setWindowIcon(QIcon("icon"));

//透明
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    this->showFullScreen();
//定时
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(close()));
    timer->start(10000);

}

void MainWindow::resizeEvent(QResizeEvent *event){
QMainWindow::resizeEvent(event);
    int screenWidth = this->width();
    int screenHeight = this->height();
    int labelWidth[3];
    QLabel * label[3];label[0] = ui->label;label[1] = ui->label_2;label[2] = ui->label_3;
    for(int i = 0 ; i < 3;  i ++){
        int k = 6;
        QFont * temp = new QFont("微软雅黑",k*10);
        temp->setLetterSpacing(QFont::AbsoluteSpacing,20);
        label[2-i]->setFont(*temp);//k=字号系数
        QPalette pa;
        pa.setColor(QPalette::WindowText,QColor(38,157,128));
        label[2-i]->setPalette(pa);
        label[2-i]->adjustSize();
        //label[2-i]->font().setLetterSpacing();
        qDebug("%d %d",fontMetrics ().width(label[i]->text()),i);
        labelWidth[2-i] =fontMetrics ().width(label[2-i]->text());
        label[2-i]->move(screenWidth*4/9-(labelWidth[2-i]/2)*k,screenHeight*5/8-fontMetrics ().height()*(i*k*3));//fontMetrics获取字体高度
    }

}

void MainWindow::appAutoRun(bool bAutoRun)
{
    QSettings *reg = new QSettings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",QSettings::NativeFormat);
    QString appName = "Miao";
    if (bAutoRun)
    {
        QString strAppPath=QCoreApplication::applicationFilePath();
        strAppPath.replace('/','\\');
        reg->setValue(appName,strAppPath);
    }
    else
    {
        reg->setValue(appName,"");
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
