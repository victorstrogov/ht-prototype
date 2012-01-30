#ifndef SGAPRED_H
#define SGAPRED_H
#include "mtdatamanipulation.h"
#include "mttemplate.h"
#include <QtCore/QDate>
namespace SgaPred
{



class SgaInfo:public MtTemplateHolder
{

public:
    SgaInfo();

    const int number() const;
    void setNumber(int nubmer);

    const QDate & date() const;
    void setDate(const QDate & date);

    const QTime & timeStart() const;
    void setTimeStart(const QTime & time);

    const QTime & timeEnd() const;
    void setTimeEnd(const QTime & time);


private:

    int m_number;
    QDate m_date;
    QTime m_timeStart;
    QTime m_timeEnd;


};

class Loader:public MtTemplateSerialization
{
    Q_OBJECT
public:
    const SgaInfo & sga();
    void setSga(const SgaInfo & sga);
};
}

#endif // SGAPRED_H
