#ifndef SYMBOLTABLETEST_H
#define SYMBOLTABLETEST_H

#include <QObject>

class SymbolTableTest : public QObject
{
    Q_OBJECT
public:
    explicit SymbolTableTest(QObject *parent = nullptr) {}
    Q_INVOKABLE /*public*/  void setUp();
    Q_INVOKABLE /*public*/  void tearDown();

public slots:
    /*public*/  void testValidateName();

signals:

};

#endif // SYMBOLTABLETEST_H
