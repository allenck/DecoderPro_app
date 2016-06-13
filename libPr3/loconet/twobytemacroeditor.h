#ifndef TWOBYTEMACROEDITOR_H
#define TWOBYTEMACROEDITOR_H
#include "sdfmacroeditor.h"

class TwoByteMacroEditor : public SdfMacroEditor
{
 Q_OBJECT
public:
 //explicit TwoByteMacroEditor(QWidget *parent = 0);
 /*public*/ TwoByteMacroEditor(SdfMacro* inst, QWidget *parent = 0);

signals:

public slots:

};

#endif // TWOBYTEMACROEDITOR_H
