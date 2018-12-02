#ifndef SIMPLETIMEBASEXML_H
#define SIMPLETIMEBASEXML_H
#include "abstractxmladapter.h"
#include "liblayouteditor_global.h"

class Timebase;
class LIBLAYOUTEDITORSHARED_EXPORT SimpleTimebaseXml : public AbstractXmlAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SimpleTimebaseXml(QObject *parent = 0);
    ~SimpleTimebaseXml();
 SimpleTimebaseXml(const SimpleTimebaseXml&) : AbstractXmlAdapter() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    /*public*/ int loadOrder();
    // Conversion format for dates created by Java Date.toString().
    // The Locale needs to be always US, irrelevant from computer's and program's settings!
    static /*final*/ QString format;// = new SimpleDateFormat("EEE MMM dd HH:mm:ss zzz yyyy", Locale.US);

signals:

public slots:

private:
 Logger* log;
 /*private*/ QString removeTimeZone(QString time);

};
Q_DECLARE_METATYPE(SimpleTimebaseXml)
#endif // SIMPLETIMEBASEXML_H
