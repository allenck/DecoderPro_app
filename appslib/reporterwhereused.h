#ifndef REPORTERWHEREUSED_H
#define REPORTERWHEREUSED_H

#include <QObject>

class NamedBean;
class JTextArea;
class ReporterWhereUsed : public QObject
{
 Q_OBJECT
 explicit ReporterWhereUsed(QObject *parent = nullptr);
public:
 static /*public*/ JTextArea* getWhereUsed(NamedBean* reporter);

signals:

public slots:
};

#endif // REPORTERWHEREUSED_H
