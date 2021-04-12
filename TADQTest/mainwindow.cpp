#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QString>
#include <QList>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);





    device = NULL;
    dio = NULL;
    ai = NULL;
    portType = NULL;
    m_channelNumberMax = 0;

    errorCode = Success;
    index =0;
    deviceNumber = -2;

    m_deviceCount = 0;
    for (int i = 0; i < 256; i++)
    {
        m_deviceNumList[i] = -1;
    }

    m_thread = new WorkerThread(ai);

    QObject::connect(m_thread,SIGNAL(toRawData(double)),this,SLOT(showRawData(double)));

    CreateDeviceList();
    ConfigurateDevice();

    ui->comboBox->addItems(m_deviceList);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::CreateDeviceList()
{

    errorCode = Success;
    index = 0;

    do
    {
        bool isSupportedDi = false;
        if (device != NULL)
        {
            device->Close();
            device = NULL;
        }
        errorCode = AdxDeviceGetLinkageInfo(-1, index++, &deviceNumber, description, NULL);
        if (errorCode == Success)
        {
            errorCode = BDaqDevice::Open(deviceNumber, ModeRead, device);
            if (BioFailed(errorCode))
            {
                continue;
            }
            // Get counter module.
            errorCode = device->GetModule(0, dio);
            if (BioFailed(errorCode))
            {

                continue;
            }
            // is device supported Do
            int portCount = 0;
            errorCode = dio->Property.Get(CFG_FeaturePortsCount, portCount);
            if (BioFailed(errorCode))
            {
                HandleError(errorCode);
                continue;
            }
            portType = new byte[portCount];
            errorCode = dio->Property.Get(CFG_FeaturePortsType, portCount, portType);
            if (BioFailed(errorCode))
            {
                HandleError(errorCode);
                continue;
            }

            for (int i = 0; i < portCount; i++)
            {
                if (portType[i] != 0)
                {
                    isSupportedDi = true;
            ;
                }
            }
            delete []portType;
            portType = NULL;

            if (true == isSupportedDi)
            {
                m_deviceNumList[m_deviceCount++] = deviceNumber;
                // initialize comboxDevice which lists the devices.
                m_deviceList.append(QString::fromStdWString(description));

            }
        }
    } while (deviceNumber != -1);

//    if ( -1 == deviceNumber)
//    {
//        int ret = QMessageBox::critical(this, tr("My Application"),
//                                       tr("No device to support the currently demonstrated function!")
//                                        , QMessageBox::Ok);
//    }

}
//This function is used to handle the errorCode information
void MainWindow::HandleError(ErrorCode errorCode)
{
    TCHAR	errorNumber[32]	=	{0};
    wsprintf(errorNumber,(L"%X"), errorCode);
    QString str = "Sorry ! There's some error happened, the error code is: ";
    str +=QString::fromStdWString(errorNumber);

    int ret = QMessageBox::critical(this, tr("My Application"),
                                   str, QMessageBox::Ok);



}

void MainWindow::ConfigurateDevice()
{


    if ( device != NULL)
    {
        device->Close();
        device = NULL;
    }

    errorCode = BDaqDevice::Open(0, ModeWriteWithReset, device);
    if (BioFailed(errorCode))
    {
        HandleError(errorCode);
    }
    errorCode = device->GetModule(0, ai);
    if (BioFailed(errorCode))
    {
        HandleError(errorCode);

    }

    errorCode = device->Property.Get(CFG_Description, 128, description);
    if (BioFailed(errorCode))
    {
        HandleError(errorCode);

    }


    //get channel max number.
    m_channelNumberMax = 0;
    errorCode = ai->Property.Get(CFG_FeatureChannelNumberMax, m_channelNumberMax);
    if (BioFailed(errorCode))
    {
        HandleError(errorCode);

    }
    //set value range for every channel.
qWarning()<<"Maximo numero de ch"<<m_channelNumberMax;
    LONG * chVrg = (LONG*)_alloca( sizeof(LONG) * m_channelNumberMax);
    for ( int i = 0; i < m_channelNumberMax+1; ++i )
    {
       chVrg[i] = 3;
    }

    errorCode = ai->Property.Set(CFG_VrgTypeOfChannels, m_channelNumberMax + 1, chVrg);
    if (BioFailed(errorCode))
    {
        HandleError(errorCode);
    }


}
void MainWindow::showRawData(double rawData)
{
    qWarning()<<rawData<<" V ";
}


void MainWindow::on_pushButton_clicked()
{
    m_thread->startWorkerThread();
}
