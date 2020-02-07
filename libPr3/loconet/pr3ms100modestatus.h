#ifndef PR3MS100MODESTATUS_H
#define PR3MS100MODESTATUS_H

#include <QObject>

class PR3MS100ModeStatus : public QObject
{
 Q_OBJECT
public:
 explicit PR3MS100ModeStatus(int a, int b, int c, QObject *parent = nullptr);
 /*public*/ int goodMsgCnt;
 /*public*/ int badMsgCnt;
 /*public*/ int ms100status;

signals:

public slots:
};

#endif // PR3MS100MODESTATUS_H
