#ifndef MATRIXSIGNALMASTXML_H
#define MATRIXSIGNALMASTXML_H
#include "abstractnamedbeanmanagerconfigxml.h"

class MatrixSignalMastXml : public AbstractNamedBeanManagerConfigXML
{
 Q_OBJECT
public:
 Q_INVOKABLE MatrixSignalMastXml(QObject* parent = nullptr);
 ~MatrixSignalMastXml() {}
 MatrixSignalMastXml(const MatrixSignalMastXml&) : AbstractNamedBeanManagerConfigXML() {}
 /*public*/ QDomElement store(QObject* o); // from mast p to XML
 /*public*/ bool load(QDomElement shared, QDomElement perNode) throw (Exception);
 /*public*/ void load(QDomElement, QObject*) throw (Exception);

private:
 static Logger* log;
};
Q_DECLARE_METATYPE(MatrixSignalMastXml)
#endif // MATRIXSIGNALMASTXML_H
