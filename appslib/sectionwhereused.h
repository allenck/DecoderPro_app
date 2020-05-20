#ifndef SECTIONWHEREUSED_H
#define SECTIONWHEREUSED_H

#include <QObject>

class NamedBean;
class JTextArea;
class SectionWhereUsed : public QObject
{
 Q_OBJECT
 explicit SectionWhereUsed(QObject *parent = nullptr);
public:
 static /*public*/ JTextArea* getWhereUsed(NamedBean* section);

signals:

public slots:
};

#endif // SECTIONWHEREUSED_H
