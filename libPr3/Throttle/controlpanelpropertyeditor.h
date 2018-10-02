#ifndef CONTROLPANELPROPERTYEDITOR_H
#define CONTROLPANELPROPERTYEDITOR_H
#include "jdialog.h"
#include "controlpanel.h"
#include <QRadioButton>
#include <QCheckBox>
#include "jtextfield.h"

class ControlPanelPropertyEditor : public JDialog
{
 Q_OBJECT
public:
 ControlPanelPropertyEditor(ControlPanel*);

private:
 /*private*/ ControlPanel* control;

 /*private*/ QRadioButton* displaySlider; // display slider from 0 to 100
 /*private*/ QRadioButton* displaySliderContinuous; // display slider from -100 to 0 to 100
 /*private*/ QRadioButton* displaySteps;
 /*private*/ QCheckBox* trackBox;
 /*private*/ JTextField* functionSwitchSlider;

 /*private*/ int _displaySlider;
 /*private*/ void initGUI();
 /*private*/ bool isDataValid();

private slots:
 void on_displaySlider_clicked();
 void on_displaySteps_clicked();
 void on_displaySliderContinuous_clicked();
 /*private*/ void saveProperties();
 /*private*/ void finishEdit();

};

#endif // CONTROLPANELPROPERTYEDITOR_H
