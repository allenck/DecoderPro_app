#ifndef LEMEMORYICONXML_H
#define LEMEMORYICONXML_H
#include "memoryiconxml.h"

class MemoryIcon;
class LEMemoryIconXml : public MemoryIconXml
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit LEMemoryIconXml(QObject *parent = 0);
 ~LEMemoryIconXml() {}
 LEMemoryIconXml(const LEMemoryIconXml&) :MemoryIconXml() {}
signals:

public slots:
private:
};
Q_DECLARE_METATYPE(LEMemoryIconXml)
#endif // MEMORYICONXML_H
