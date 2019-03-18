#ifndef ZEROCONFCLIENT_H
#define ZEROCONFCLIENT_H

#include <QObject>

class ZeroConfClient : public QObject
{
 Q_OBJECT
public:
 explicit ZeroConfClient(QObject *parent = nullptr);

signals:

public slots:
};

#endif // ZEROCONFCLIENT_H