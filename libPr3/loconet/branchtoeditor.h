#ifndef BRANCHTOEDITOR_H
#define BRANCHTOEDITOR_H
#include "sdfmacroeditor.h"

class SdfMacro;
class BranchToEditor : public SdfMacroEditor
{
 Q_OBJECT
public:
 //explicit BranchToEditor(QWidget *parent = 0);
 /*public*/ BranchToEditor(SdfMacro* inst, QWidget *parent = 0);

signals:

public slots:

};

#endif // BRANCHTOEDITOR_H
