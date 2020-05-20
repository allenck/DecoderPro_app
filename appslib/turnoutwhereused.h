#ifndef TURNOUTWHEREUSED_H
#define TURNOUTWHEREUSED_H

#include <QObject>

class NamedBean;
class JTextArea;
class TurnoutWhereUsed : public QObject
{
 Q_OBJECT
 explicit TurnoutWhereUsed(QObject *parent = nullptr);
public:
 static /*public*/ JTextArea* getWhereUsed(NamedBean *turnout);

signals:

public slots:
};

#endif // TURNOUTWHEREUSED_H
