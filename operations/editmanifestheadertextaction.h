#ifndef EDITMANIFESTHEADERTEXTACTION_H
#define EDITMANIFESTHEADERTEXTACTION_H

#include "abstractaction.h"
#include "editmanifestheadertextframe.h"
#include <QPointer>

namespace Operations
{
 class EditManifestHeaderTextFrame;
 class EditManifestHeaderTextAction : public AbstractAction
 {
  Q_OBJECT
 public:
  EditManifestHeaderTextAction(QObject* parent);
  /*public*/ EditManifestHeaderTextAction(QString s, QObject* parent);

 public slots:
  /*public*/ void actionPerformed(JActionEvent* /*e*/);

 private:
  QPointer<EditManifestHeaderTextFrame> f;// = null;

 };
}
#endif // EDITMANIFESTHEADERTEXTACTION_H
