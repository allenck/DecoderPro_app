#ifndef NAMEDBEANUSERNAMECOMPARATORTESTACTION_H
#define NAMEDBEANUSERNAMECOMPARATORTESTACTION_H
#include "abstractaction.h"


class Logger;
class NamedBeanUserNameComparatorTestAction : public AbstractAction
{
    Q_OBJECT
public:
    NamedBeanUserNameComparatorTestAction(QObject *parent);
public slots:
    void actionPerformed();
private:
    static Logger* log;
};

#endif // NAMEDBEANUSERNAMECOMPARATORTESTACTION_H
