#ifndef FOURBYTEMACROEDITOR_H
#define FOURBYTEMACROEDITOR_H

#include "sdfmacroeditor.h"

class FourByteMacroEditor : public SdfMacroEditor
{
 Q_OBJECT
public:
 //explicit FourByteMacroEditor(QWidget *parent = 0);
 /*public*/ FourByteMacroEditor(SdfMacro* inst, QWidget *parent = 0);

signals:

public slots:

};

#endif // FOURBYTEMACROEDITOR_H
