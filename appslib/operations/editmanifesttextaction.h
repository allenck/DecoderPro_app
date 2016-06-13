#ifndef EDITMANIFESTTEXTACTION_H
#define EDITMANIFESTTEXTACTION_H

#include "abstractaction.h"
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
  /*public*/ void actionPerformed(ActionEvent* e);
 private:
  EditManifestTextFrame* f; // = NULL
  void common();
 };
}
#endif // EDITMAINFESTTEXTACTION_H
