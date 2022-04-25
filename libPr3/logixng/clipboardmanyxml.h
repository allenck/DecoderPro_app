#ifndef CLIPBOARDMANYXML_H
#define CLIPBOARDMANYXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ClipboardMany;
class ClipboardManyXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  explicit ClipboardManyXml(QObject *parent = nullptr);
  ~ClipboardManyXml() {}
  ClipboardManyXml(const ClipboardManyXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode)override;
  /*public*/  ClipboardMany* loadItem(QDomElement shared);

};
Q_DECLARE_METATYPE(ClipboardManyXml)
#endif // CLIPBOARDMANYXML_H
