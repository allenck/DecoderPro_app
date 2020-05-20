#ifndef BLOCKWHEREUSED_H
#define BLOCKWHEREUSED_H

#include <QObject>

class NamedBean;
class JTextArea;
class BlockWhereUsed : public QObject
{
 Q_OBJECT
 explicit BlockWhereUsed(QObject *parent = nullptr);
public:
 static /*public*/ JTextArea* getWhereUsed(NamedBean* block);

signals:

public slots:
};

#endif // BLOCKWHEREUSED_H
