#ifndef DEFAULTLOGIXNGMANAGERTEST_H
#define DEFAULTLOGIXNGMANAGERTEST_H

#include <QObject>

class ConditionalNG;
class DefaultLogixNGManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit DefaultLogixNGManagerTest(QObject *parent = nullptr) : QObject(parent){}
    Q_INVOKABLE /*public*/  void setUp();
    Q_INVOKABLE /*public*/  void tearDown();
    /*public*/  void setupInitialConditionalNGTree(ConditionalNG* conditionalNG);

public slots:
    /*public*/  void testManager();
    /*public*/  void testValidSystemNameFormat();
    /*public*/  void testCreateNewLogixNG();
    /*public*/  void testSetupInitialConditionalNGTree();
    /*public*/  void testDeleteLogixNG() /*throws SocketAlreadyConnectedException, PropertyVetoException*/;

signals:

};

#endif // DEFAULTLOGIXNGMANAGERTEST_H