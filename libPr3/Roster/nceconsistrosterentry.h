#ifndef NCECONSISTROSTERENTRY_H
#define NCECONSISTROSTERENTRY_H

#include <QObject>
#include "logger.h"
#include <QtXml>

class QDomDocument;
class QDomElement;
class NceConsistRosterEntry : public QObject
{
    Q_OBJECT
public:
    explicit NceConsistRosterEntry(QObject *parent = 0);
    /*public*/ NceConsistRosterEntry(NceConsistRosterEntry* pEntry, QString pID, QObject *parent= 0);
    /*public*/ void setId(QString s);
    /*public*/ QString getId();
    /*public*/ void   setConsistNumber(QString s);
    /*public*/ QString getConsistNumber();
    /*public*/ void   setRoadName(QString s);
    /*public*/ QString getRoadName();
    /*public*/ void   setRoadNumber(QString s);
    /*public*/ QString getRoadNumber();
    /*public*/ void   setModel(QString s);
    /*public*/ QString getModel();
    /*public*/ void   setLoco1DccAddress(QString s);
    /*public*/ QString getLoco1DccAddress();
    /*public*/ void   setLoco1LongAddress(bool b);
    /*public*/ bool isLoco1LongAddress();
    /*public*/ void   setLoco1Direction(QString s);
    /*public*/ QString getLoco1Direction();
    /*public*/ void   setLoco2DccAddress(QString s);
    /*public*/ QString getLoco2DccAddress();
    /*public*/ void   setLoco2LongAddress(bool b);
    /*public*/ bool isLoco2LongAddress();
    /*public*/ void   setLoco2Direction(QString s);
    /*public*/ QString getLoco2Direction();
    /*public*/ void   setLoco3DccAddress(QString s);
    /*public*/ QString getLoco3DccAddress() ;
    /*public*/ void   setLoco3LongAddress(bool b) ;
    /*public*/ bool isLoco3LongAddress();
    /*public*/ void   setLoco3Direction(QString s);
    /*public*/ QString getLoco3Direction();
    /*public*/ void   setLoco4DccAddress(QString s);
    /*public*/ QString getLoco4DccAddress();
    /*public*/ void   setLoco4LongAddress(bool b) ;
    /*public*/ bool isLoco4LongAddress();
    /*public*/ void   setLoco4Direction(QString s);
    /*public*/ QString getLoco4Direction();
    /*public*/ void   setLoco5DccAddress(QString s) ;
    /*public*/ QString getLoco5DccAddress();
    /*public*/ void   setLoco5LongAddress(bool b);
    /*public*/ bool isLoco5LongAddress();
    /*public*/ void   setLoco5Direction(QString s);
    /*public*/ QString getLoco5Direction() ;
    /*public*/ void   setLoco6DccAddress(QString s);
    /*public*/ QString getLoco6DccAddress();
    /*public*/ void   setLoco6LongAddress(bool b);
    /*public*/ bool isLoco6LongAddress();
    /*public*/ void   setLoco6Direction(QString s);
    /*public*/ QString getLoco6Direction();
    /*public*/ void   setComment(QString s);
    /*public*/ QString getComment();
    /*public*/ NceConsistRosterEntry(QDomElement e);
    QDomElement store(QDomDocument doc);
    /*public*/ QString titleString();
    /*public*/ QString toString() ;
//    /*public*/ void printEntry(Writer* w);
//    /*public*/ QVector<QString> wrapComment(QString comment, int textSpace);
signals:

public slots:
private:
    void init();
    Logger* log;
protected:
    // members to remember all the info
    /*protected*/ QString _fileName;//null;

    /*protected*/ QString _id;//"";
    /*protected*/ QString _consistNumber;//"";
    /*protected*/ QString _roadName;//"";
    /*protected*/ QString _roadNumber;//"";
    /*protected*/ QString _model;//"";
    /*protected*/ QString _loco1DccAddress;//"";
    /*protected*/ bool _isLoco1LongAddress;//true;
    /*protected*/ QString _loco1Direction;//"";
    /*protected*/ QString _loco2DccAddress;//"";
    /*protected*/ bool _isLoco2LongAddress;//true;
    /*protected*/ QString _loco2Direction;//"";
    /*protected*/ QString _loco3DccAddress;//"";
    /*protected*/ bool _isLoco3LongAddress;//true;
    /*protected*/ QString _loco3Direction;//"";
    /*protected*/ QString _loco4DccAddress;//"";
    /*protected*/ bool _isLoco4LongAddress;//true;
    /*protected*/ QString _loco4Direction;//"";
    /*protected*/ QString _loco5DccAddress;//"";
    /*protected*/ bool _isLoco5LongAddress;//true;
    /*protected*/ QString _loco5Direction;//"";
    /*protected*/ QString _loco6DccAddress;//"";
    /*protected*/ bool _isLoco6LongAddress;//true;
    /*protected*/ QString _loco6Direction;//"";

    /*protected*/ QString _comment;//"";


};

#endif // NCECONSISTROSTERENTRY_H
