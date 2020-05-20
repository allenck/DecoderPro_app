#ifndef SIGNALMASTWHEREUSED_H
#define SIGNALMASTWHEREUSED_H

#include <QObject>

class JTextArea;
class NamedBean;
class SignalMastWhereUsed : public QObject
{
 Q_OBJECT
 explicit SignalMastWhereUsed(QObject *parent = nullptr);
public:
 static /*public*/ JTextArea* getWhereUsed(NamedBean* signalMast);

signals:

public slots:
};

#endif // SIGNALMASTWHEREUSED_H
