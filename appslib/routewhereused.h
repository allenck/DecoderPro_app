#ifndef ROUTEWHEREUSED_H
#define ROUTEWHEREUSED_H

#include <QObject>

class NamedBean;
class JTextArea;
class RouteWhereUsed : public QObject
{
 Q_OBJECT
 explicit RouteWhereUsed(QObject *parent = nullptr);
public:
 static /*public*/ JTextArea* getWhereUsed(NamedBean* route);

signals:

public slots:
};

#endif // ROUTEWHEREUSED_H
