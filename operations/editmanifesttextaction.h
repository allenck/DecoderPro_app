#ifndef EDITMANIFESTTEXTACTION_H
#define EDITMANIFESTTEXTACTION_H

#include "abstractaction.h"
#include "editmanifesttextframe.h"
#include <QPointer>

namespace Operations
{
 class EditManifestTextFrame;
 class EditManifestTextAction : public AbstractAction
 {
  Q_OBJECT
 public:
  EditManifestTextAction(QObject* parent);
  /*public*/ EditManifestTextAction(QString s, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(JActionEvent * /*e*/)override;
 private:
  QPointer<EditManifestTextFrame> f; // = NULL
  void common();
 };
}
#endif // EDITMAINFESTTEXTACTION_H
