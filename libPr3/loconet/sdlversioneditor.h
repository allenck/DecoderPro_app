#ifndef SDLVERSIONEDITOR_H
#define SDLVERSIONEDITOR_H
#include "sdfmacroeditor.h"

class SdlVersionEditor : public SdfMacroEditor
{
 Q_OBJECT
public:
 //explicit SdlVersionEditor(QWidget *parent = 0);
 /*public*/ SdlVersionEditor(SdfMacro* inst, QWidget *parent = 0);

signals:

public slots:

};

#endif // SDLVERSIONEDITOR_H
