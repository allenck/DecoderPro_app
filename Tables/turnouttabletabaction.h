#ifndef TURNOUTTABLETABACTION_H
#define TURNOUTTABLETABACTION_H
#include "abstracttabletabaction.h"
#include "libtables_global.h"

class Manager;
class LIBTABLESSHARED_EXPORT TurnoutTableTabAction : public AbstractTableTabAction
{
    Q_OBJECT
public:
    explicit TurnoutTableTabAction(QObject *parent = 0);
    /*public*/ TurnoutTableTabAction(QString s, QObject *parent);
    ~TurnoutTableTabAction() {}
    TurnoutTableTabAction(const TurnoutTableTabAction& that) : AbstractTableTabAction(that.text(), that.parent()) {}
    BeanTableFrame* currFrame();
    void setCurrFrame(BeanTableFrame *frame);

signals:

public slots:
private:
    void common();
    static BeanTableFrame* frame;
protected:
    /*protected*/ Manager* getManager();
    /*protected*/ QString getClassName() ;
    /*protected*/ AbstractTableAction* getNewTableAction (QString choice);
    /*protected*/ QString helpTarget();

};

#endif // TURNOUTTABLETABACTION_H
