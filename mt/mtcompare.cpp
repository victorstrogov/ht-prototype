#include "mtcompare.h"
#include <QList>
#include <QMutex>
static QMutex s_comparersLocker;
static QList<MtCompareHandler*> s_comparers;

 MtCompare * MtCompare::tester(int byCode)
{
    QMutexLocker ml(&s_comparersLocker);
    MtCompare * tester=0;
    foreach(MtCompareHandler * h,s_comparers)
    {

        if((tester=h->create(byCode)))
        {
            break;
        }
    }
    return tester;
}

MtCompareHandler::MtCompareHandler()
{
    QMutexLocker ml(&s_comparersLocker);
    s_comparers.push_back(this);
}

MtCompareHandler::~MtCompareHandler()
{
    QMutexLocker ml(&s_comparersLocker);
    s_comparers.removeAll(this);
}



