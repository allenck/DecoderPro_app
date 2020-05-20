#ifndef MEMORYWHEREUSED_H
#define MEMORYWHEREUSED_H

#include <QObject>

class NamedBean;
class JTextArea;
class MemoryWhereUsed : public QObject
{
 Q_OBJECT
 explicit MemoryWhereUsed(QObject *parent = nullptr);
public:
 static /*public*/ JTextArea* getWhereUsed(NamedBean* memory);

signals:

public slots:
};

#endif // MEMORYWHEREUSED_H
