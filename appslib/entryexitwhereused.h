#ifndef ENTRYEXITWHEREUSED_H
#define ENTRYEXITWHEREUSED_H

#include <QObject>

class NamedBean;
class JTextArea;
class EntryExitWhereUsed : public QObject
{
 Q_OBJECT
public:
 static /*public*/ JTextArea* getWhereUsed(NamedBean* entryexit);

signals:

public slots:
private:
 explicit EntryExitWhereUsed(QObject *parent = nullptr);

};

#endif // ENTRYEXITWHEREUSED_H
