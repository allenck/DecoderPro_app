#ifndef SIGNALHEADWHEREUSED_H
#define SIGNALHEADWHEREUSED_H

#include <QObject>

class JTextArea;
class NamedBean;
class SignalHeadWhereUsed : public QObject
{
 Q_OBJECT
 explicit SignalHeadWhereUsed(QObject *parent = nullptr);
public:
 static /*public*/ JTextArea* getWhereUsed(NamedBean* signalHead);

signals:

public slots:
};

#endif // SIGNALHEADWHEREUSED_H
