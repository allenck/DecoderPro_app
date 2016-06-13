#ifndef INITIATESOUNDEDITOR_H
#define INITIATESOUNDEDITOR_H
#include "sdfmacroeditor.h"

class QComboBox;
class QCheckBox;
class InitiateSoundEditor : public SdfMacroEditor
{
 Q_OBJECT
public:
 //explicit InitiateSoundEditor(QWidget *parent = 0);
 /*public*/ InitiateSoundEditor(SdfMacro* inst, QWidget *parent = 0);
 /*public*/ void update();

signals:

public slots:
 void on_action(int = 0);

private:
 QCheckBox* zap;// = new QCheckBox("Zap");
 QCheckBox* run;// = new QCheckBox("Run while triggered");
 QCheckBox* noprempt;// = new QCheckBox("No preemptive trigger");
 QCheckBox* nottrig;// = new QCheckBox("Not triggered");
 QComboBox* box;

};

#endif // INITIATESOUNDEDITOR_H
