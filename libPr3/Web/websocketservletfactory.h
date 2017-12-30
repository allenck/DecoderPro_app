#ifndef WEBSOCKETSERVERFACTORY_H
#define WEBSOCKETSERVERFACTORY_H

#include <QObject>

class WebSocketServletFactory : public QObject
{
 Q_OBJECT
public:
 explicit WebSocketServletFactory(QObject *parent = nullptr);
 /*public*/ virtual void _register(QString websocketPojo);

signals:

public slots:
};

#endif // WEBSOCKETSERVERFACTORY_H
