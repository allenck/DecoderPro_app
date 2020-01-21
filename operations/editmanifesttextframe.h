#ifndef EDITMANIFESTTEXTFRAME_H
#define EDITMANIFESTTEXTFRAME_H

#include "operationsframe.h"
namespace Operations
{
 class EditManifestTextFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  EditManifestTextFrame(QWidget* parent = 0);
  /*public*/ void initComponents();
  /*public*/ QString getClassName();

 public slots:

 };
}
#endif // EDITMANIFESTTEXTFRAME_H
