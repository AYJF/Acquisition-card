#include "workerthread.h"

#include <QDebug>

WorkerThread::WorkerThread(BDaqAi *ptrAi)
{
    ai = ptrAi;
    isWorking = false;
}
void WorkerThread::run()
{
    SHORT raw[16]; // 16 is chCount
    double scaled[16];

    while(isWorking)
    {

//        qWarning()<<"hfhfwf";
//        ai->Read(0,rawData); // read data
//        qWarning()<<rawData;
//        emit toRawData(rawData);


        SHORT raw[16]; // 16 is chCount
           double scaled[16];

              ai->Read(0, 15, raw, scaled); // read data
              for ( int i = 0; i < 15; ++i )
              {
                 qWarning()<< i<< raw[i]<< scaled[i];
              }




        msleep(100);
    }

}
void WorkerThread::startWorkerThread()
{
    isWorking = true;
    this->start();
}
