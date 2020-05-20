#ifndef WARRANTWHEREUSED_H
#define WARRANTWHEREUSED_H

#include <QObject>

class NamedBean;
class JTextArea;
class WarrantWhereUsed : public QObject
{
 Q_OBJECT
 explicit WarrantWhereUsed(QObject *parent = nullptr);
public:
 static /*public*/ JTextArea* getWhereUsed(NamedBean* warrant);

signals:

public slots:
};

#endif // WARRANTWHEREUSED_H
