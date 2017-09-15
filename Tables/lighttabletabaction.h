#ifndef LIGHTTABLETABACTION_H
#define LIGHTTABLETABACTION_H
#include "abstracttabletabaction.h"

class LightTableTabAction : public AbstractTableTabAction
{
 Q_OBJECT
public:
    Q_INVOKABLE /*public*/ LightTableTabAction(QString s, QObject* parent);
    /*public*/ LightTableTabAction(QObject* parent = 0) ;
    ~LightTableTabAction() {}
    LightTableTabAction(const LightTableTabAction& that) : AbstractTableTabAction(that.text(), that.parent()) {}
    BeanTableFrame* currFrame();
    void setCurrFrame(BeanTableFrame *frame);
    QWidget* getPanel();

private:
    BeanTableFrame *frame;

protected:
    /*protected*/ Manager* getManager();
    /*protected*/ QString getClassName();
    /*protected*/ AbstractTableAction* getNewTableAction(QString choice);
    /*protected*/ QString helpTarget();
};
Q_DECLARE_METATYPE(LightTableTabAction)
#endif // LIGHTTABLETABACTION_H
