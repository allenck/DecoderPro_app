#ifndef SWINGCONFIGURATORINTERFACETEST_H
#define SWINGCONFIGURATORINTERFACETEST_H

#include <QObject>

class SwingConfiguratorInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit SwingConfiguratorInterfaceTest(QObject *parent = nullptr);
    Q_INVOKABLE /*public*/ void setUp();
    Q_INVOKABLE /*public*/ void tearDown();

public slots:
    /*public*/ void testSwingTools();



signals:

};

#endif // SWINGCONFIGURATORINTERFACETEST_H
