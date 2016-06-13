#ifndef SIGLET_H
#define SIGLET_H
#include "abstractautomaton.h"

class NamedBean;
class Siglet : public AbstractAutomaton
{
    Q_OBJECT
public:
    //explicit Siglet(QObject *parent = 0);
    /*public*/ QVector<NamedBean*> inputs;      // /*public*/ for Jython subclass access
    /*public*/ QVector<NamedBean*> outputs;     // /*public*/ for Jython subclass access
    /*public*/
    Siglet(QObject *parent = 0);
    Siglet(QString name, QObject* parent = 0);
    /*public*/ virtual void defineIO();
    /*public*/ virtual void setOutput();

signals:

public slots:
private:
protected:
    /*protected*/ void init();
    /*protected*/ bool handle();

};

#endif // SIGLET_H
