#ifndef MTCOMPARE_H
#define MTCOMPARE_H
class QVariantList;
class MtCompare;
class MtCompareHandler
{
public:
    MtCompareHandler();
    ~MtCompareHandler();
    virtual MtCompare * create(int code)=0;

};
class MtCompare
{
public:
    enum Result
    {
        Ready,
        NotReady,
        Other
    };
    static  MtCompare * tester(int byCode);
    virtual Result test(const QVariantList & which,const QVariantList & with)=0;

};

#endif // MTCOMPARE_H
