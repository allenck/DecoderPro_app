#ifndef STOREXMLUSERACTION_H
#define STOREXMLUSERACTION_H
#include "storexmlconfigaction.h"

class StoreXmlUserAction : public StoreXmlConfigAction
{
    Q_OBJECT
public:
    explicit StoreXmlUserAction(QObject *parent = 0);
    /*public*/ StoreXmlUserAction(QString s, QObject *parent = 0);

signals:

public slots:
    /*public*/ void actionPerformed(/*ActionEvent e*/);
private:
 Logger* log;

};

#endif // STOREXMLUSERACTION_H
