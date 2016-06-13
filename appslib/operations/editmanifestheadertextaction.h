#ifndef EDITMANIFESTHEADERTEXTACTION_H
#define EDITMANIFESTHEADERTEXTACTION_H

#include "abstractaction.h"
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
  /*public*/ void actionPerformed(ActionEvent* e);

 private:
  EditManifestHeaderTextFrame* f;// = null;

 };
}
#endif // EDITMANIFESTHEADERTEXTACTION_H
