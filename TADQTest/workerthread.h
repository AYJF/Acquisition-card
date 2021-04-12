#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>

#include "BDaqCL.h"
using namespace Automation::BDaq;

class WorkerThread : public QThread
{
    Q_OBJECT

public:
    WorkerThread(BDaqAi *ptrAi);
    void startWorkerThread();
    void stopThread(){
        isWorking = false;
    }

signals:
    void toRawData(double );



protected:
    void run();

private:
    bool isWorking;
    double rawData;
    BDaqAi * ai;

};

#endif // WORKERTHREAD_H
