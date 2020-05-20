#ifndef LIGHTWHEREUSED_H
#define LIGHTWHEREUSED_H

#include <QObject>

class NamedBean;
class JTextArea;
class LightWhereUsed : public QObject
{
 Q_OBJECT
 explicit LightWhereUsed(QObject *parent = nullptr);
public:
 static /*public*/ JTextArea *getWhereUsed(NamedBean* light);

signals:

public slots:
};

#endif // LIGHTWHEREUSED_H
