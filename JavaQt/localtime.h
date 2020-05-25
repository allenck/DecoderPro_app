#ifndef LOCALTIME_H
#define LOCALTIME_H

#include <QObject>

class LocalTime : public QObject
{
 Q_OBJECT
public:
 explicit LocalTime(QObject *parent = nullptr);

signals:

public slots:
};

#endif // LOCALTIME_H