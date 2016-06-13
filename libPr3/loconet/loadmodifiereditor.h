#ifndef LOADMODIFIEREDITOR_H
#define LOADMODIFIEREDITOR_H

#include "sdfmacroeditor.h"

class LoadModifierEditor : public SdfMacroEditor
{
 Q_OBJECT
public:
 //explicit LoadModifierEditor(QWidget *parent = 0);
 /*public*/ LoadModifierEditor(SdfMacro* inst, QWidget *parent = 0);

signals:

public slots:

};

#endif // LOADMODIFIEREDITOR_H
