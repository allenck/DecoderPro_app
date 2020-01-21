#ifndef EDITMANIFESTHEADERTEXTFRAME_H
#define EDITMANIFESTHEADERTEXTFRAME_H

#include "operationsframe.h"

namespace Operations
{
 class EditManifestHeaderTextFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  EditManifestHeaderTextFrame(QWidget* parent = 0);
  /*public*/ void initComponents();
  /*public*/ QString getClassName();

 };
}
#endif // EDITMANIFESTHEADERTEXTFRAME_H
