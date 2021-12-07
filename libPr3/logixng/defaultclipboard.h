#ifndef DEFAULTCLIPBOARD_H
#define DEFAULTCLIPBOARD_H
#include "abstractbase.h"
#include "clipboard.h"
#include "clipboardmany.h"

class DefaultClipboard : public AbstractBase, public Clipboard
{
  Q_OBJECT
  Q_INTERFACES(Clipboard)
 public:
  DefaultClipboard(QObject* parent = nullptr);

 private:
  /*private*/ ClipboardMany* _clipboardItems = new ClipboardMany("", nullptr);

};

#endif // DEFAULTCLIPBOARD_H
