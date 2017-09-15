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
    Q_INVOKABLE TurnoutTableTabAction(QString s, QObject *parent);
    ~TurnoutTableTabAction() {}
    Q_INVOKABLE TurnoutTableTabAction(const TurnoutTableTabAction& that) : AbstractTableTabAction(that.text(), that.parent()) {}
    BeanTableFrame* currFrame();
    void setCurrFrame(BeanTableFrame *frame);
    static BeanTableFrame* frame;
    QWidget* getPane();

signals:

public slots:
private:
    void common();
protected:
    /*protected*/ Manager* getManager();
    /*protected*/ QString getClassName() ;
    /*protected*/ AbstractTableAction* getNewTableAction (QString choice);
    /*protected*/ QString helpTarget();

};
Q_DECLARE_METATYPE(TurnoutTableTabAction)
#endif // TURNOUTTABLETABACTION_H
