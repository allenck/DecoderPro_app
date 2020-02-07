#ifndef PR2STATUS_H
#define PR2STATUS_H

#include <QObject>

class PR2Status : public QObject
{
 Q_OBJECT
public:
 explicit PR2Status(int serial, int status, int current, int hardware, int software, QObject *parent = nullptr);
 /*public*/ int serial, status, current, hardware, software;

signals:

public slots:
};

#endif // PR2STATUS_H
