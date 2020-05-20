#ifndef OBLOCKWHEREUSED_H
#define OBLOCKWHEREUSED_H

#include <QObject>

class NamedBean;
class JTextArea;
class OBlockWhereUsed : public QObject
{
 Q_OBJECT
 explicit OBlockWhereUsed(QObject *parent = nullptr);
public:
 static /*public*/ JTextArea* getWhereUsed(NamedBean* oblock);

signals:

public slots:
};

#endif // OBLOCKWHEREUSED_H
