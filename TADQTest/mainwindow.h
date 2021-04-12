#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "workerthread.h"

#include "BDaqCL.h"

using namespace Automation::BDaq;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void CreateDeviceList();
    void ConfigurateDevice();

public Q_SLOTS:
    void showRawData(double rawData);


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;


    ErrorCode errorCode = Success;
    BDaqDevice *device;
    BDaqDio *dio;
    BDaqAi *ai;
    byte *portType ;
    WCHAR description[256];
    long deviceNumber;
    long index;
    long m_channelNumberMax;
    long m_vrgTypes[128];

    void HandleError(ErrorCode errorCode);

    int m_deviceNumList[256] ;
    QList<QString> m_deviceList;
    int m_deviceCount;

    WorkerThread *m_thread;

};

#endif // MAINWINDOW_H
