#ifndef SENSORTABLETABACTION_H
#define SENSORTABLETABACTION_H
#include "abstracttabletabaction.h"
#include "javaqt_global.h"

class LIBTABLESSHARED_EXPORT SensorTableTabAction : public AbstractTableTabAction
{
 Q_OBJECT
public:
    SensorTableTabAction(QObject* parent = 0);
    Q_INVOKABLE SensorTableTabAction(QString s, QObject* parent);
    ~SensorTableTabAction() {}
    Q_INVOKABLE SensorTableTabAction(const SensorTableTabAction& that) : AbstractTableTabAction(that.text(), that.parent()) {}
    /*public*/ QString getTableClass();

private:


protected:
    /*protected*/ Manager* getManager();
    /*protected*/ QString getClassName();
    /*protected*/ AbstractTableAction* getNewTableAction(QString choice) ;
    /*protected*/ QString helpTarget();
friend class TablesFrame;
};
Q_DECLARE_METATYPE(SensorTableTabAction)
#endif // SENSORTABLETABACTION_H
