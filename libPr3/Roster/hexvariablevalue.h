#ifndef HEXVARIABLEVALUE_H
#define HEXVARIABLEVALUE_H
#include "cvvalue.h"
#include "actionevent.h"
#include "decvariablevalue.h"

class LIBPR3SHARED_EXPORT HexVariableValue : public DecVariableValue
{
    Q_OBJECT
public:
    //explicit HexVariableValue(QObject *parent = 0);
    /*public*/ HexVariableValue(QString name, QString comment, QString cvName,
                            bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
                            QString cvNum, QString mask, int minVal, int maxVal,
                            QMap<QString, CvValue*>* v, JLabel *status, QString stdname, QObject *parent = 0);
//    void updatedTextField();
    /*public*/ void actionPerformed(JActionEvent* /*e*/);
    /*public*/ void setValue(int value);

signals:

public slots:
private:
 Logger* log;
};

#endif // HEXVARIABLEVALUE_H
