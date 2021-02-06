#ifndef SHORTADDRVARIABLEVALUE_H
#define SHORTADDRVARIABLEVALUE_H
#include "decvariablevalue.h"
#include "cvvalue.h"

class LIBPR3SHARED_EXPORT ShortAddrVariableValue : public DecVariableValue
{
    Q_OBJECT
public:
   // explicit ShortAddrVariableValue(QObject *parent = 0);
    /*public*/ ShortAddrVariableValue(QString name, QString comment, QString cvName,
                                  bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
                                  QString cvNum, QString mask,
                                  QMap<QString, CvValue*>* v, JLabel *status, QString stdname, QObject *parent = 0);
    /*public*/ void setModifiedCV(QString cvNum);
    /*public*/ void writeChanges();
    /*public*/ void writeAll();
    // clean up connections when done
    /*public*/ void dispose();

signals:

public slots:
 private:
    /*private*/ void updateCvForAddrChange();
    int firstFreeSpace;// = 0;
    static /*final*/ const int maxCVs = 20;
    QVector<QString>* cvNumbers;// = new QVector<int*>(maxCVs,0);
    QVector<int>* newValues;// =  QVector<int*>(maxCVs,0);
 Logger* log;

};

#endif // SHORTADDRVARIABLEVALUE_H
