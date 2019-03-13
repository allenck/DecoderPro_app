#ifndef LAYOUTTRACKDRAWINGOPTIONSDIALOG_H
#define LAYOUTTRACKDRAWINGOPTIONSDIALOG_H
#include "jdialog.h"
#include <QSpinBox>
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>

class LayoutTrackDrawingOptions;
class LayoutEditor;
class LayoutTrackDrawingOptionsDialog : public JDialog
{
 Q_OBJECT
public:
 /*public*/ LayoutTrackDrawingOptionsDialog(LayoutEditor* layoutEditor, bool modal,
         LayoutTrackDrawingOptions* ltdOptions);


private:
 static Logger* log;
 /*===========================*\
 |* local (private) variables *|
 \*===========================*/

 // Variables declaration - do not modify
 /*private*/ QPushButton* applyButton;
 /*private*/ QLabel* ballastWidthLabel;
 /*private*/ QLabel* blockLineDashPercentageX10Label;
 /*private*/ QLabel* blockLineWidthLabel;
 /*private*/ QPushButton* cancelButton;
 /*private*/ QWidget* jPanelButtons;
 /*private*/ QPushButton* mainBallastColorButton;
 /*private*/ QSpinBox* mainBallastWidthSpinner;
 /*private*/ QSpinBox* mainBlockLineDashPercentageX10Spinner;
 /*private*/ QSpinBox* mainBlockLineWidthSpinner;
 /*private*/ QPushButton* mainRailColorButton;
 /*private*/ QSpinBox* mainRailCountSpinner;
 /*private*/ QSpinBox* mainRailGapSpinner;
 /*private*/ QSpinBox* mainRailWidthSpinner;
 /*private*/ QPushButton* mainTieColorButton;
 /*private*/ QSpinBox* mainTieGapSpinner;
 /*private*/ QSpinBox* mainTieLengthSpinner;
 /*private*/ QSpinBox* mainTieWidthSpinner;
 /*private*/ QLabel* mainlineLabel;
 /*private*/ QPushButton* okButton;
 /*private*/ QLabel* optionLabel;
 /*private*/ QGroupBox* optionsPanel;
 /*private*/ QComboBox* presetsComboBox;
 /*private*/ QLabel* presetsLabel;
 /*private*/ QLabel* railCountLabel;
 /*private*/ QLabel* railGapLabel;
 /*private*/ QLabel* railWidthLabel;
 /*private*/ QPushButton* sideBallastColorButton;
 /*private*/ QSpinBox* sideBallastWidthSpinner;
 /*private*/ QSpinBox* sideBlockLineDashPercentageX10Spinner;
 /*private*/ QSpinBox* sideBlockLineWidthSpinner;
 /*private*/ QPushButton* sideRailColorButton;
 /*private*/ QSpinBox* sideRailCountSpinner;
 /*private*/ QSpinBox* sideRailGapSpinner;
 /*private*/ QSpinBox* sideRailWidthSpinner;
 /*private*/ QPushButton* sideTieColorButton;
 /*private*/ QSpinBox* sideTieGapSpinner;
 /*private*/ QSpinBox* sideTieLengthSpinner;
 /*private*/ QSpinBox* sideTieWidthSpinner;
 /*private*/ QLabel* sidelineLabel;
 /*private*/ QLabel* tieGapLabel;
 /*private*/ QLabel* tieLengthLabel;
 /*private*/ QLabel* tieWidthLabel;
 /*private*/ QLabel* tieColorLabel;
 /*private*/ QLabel* ballastColorLabel;
 /*private*/ QLabel* railColorLabel;
 // End of variables declaration

 /*private*/ /*final*/ LayoutEditor* layoutEditor;
 /*private*/ /*transient*/ /*final*/ LayoutTrackDrawingOptions* leLTDOptions;
 /*private*/ /*transient*/ LayoutTrackDrawingOptions* ltdOptions = nullptr;

 /*private*/ QString classicPresetName;// = tr("ClassicPresetName");
 /*private*/ QString draftingPresetName;// = tr("DraftingPresetName");
 /*private*/ QString realisticPresetName;// = tr("RealisticPresetName");
 /*private*/ QString realisticOhPresetName;// = tr("RealisticOhPresetName");
 /*private*/ QString british70sPresetName;// = tr("British70sPresetName");
 /*private*/ QString csdazd71PresetName;// = tr("CsdAzd71PresetName");
 /*private*/ QString customPresetName;// = tr("CustomPresetName");
 /*private*/ /*transient*/ /*final*/ QList<LayoutTrackDrawingOptions*> ltdoList;// = new ArrayList<>();

 // used to prevent xxx->setValue's in setupControls from creating custom preset
 /*private*/ bool copyToCustom = true;

 /*private*/ void initComponents();
 /*private*/ void setupControls();
 /*private*/ void makeCustomPreset();
 /*private*/ void definePresets();

private slots:
 /*private*/ void okButtonActionPerformed(/*ActionEvent evt*/);
 /*private*/ void presetsComboBoxActionPerformed(QString);

 /*private*/ void cancelButtonActionPerformed(/*ActionEvent evt*/);
 /*private*/ void sideTieGapSpinnerStateChanged(int value);
 /*private*/ void mainTieGapSpinnerStateChanged(int value);
 /*private*/ void sideTieWidthSpinnerStateChanged(int value);
 /*private*/ void mainTieWidthSpinnerStateChanged(int value);
 /*private*/ void sideTieLengthSpinnerStateChanged(int value);
 /*private*/ void mainTieLengthSpinnerStateChanged(int value);
 /*private*/ void sideBallastWidthSpinnerStateChanged(int value);
 /*private*/ void mainBallastWidthSpinnerStateChanged(int value);
 /*private*/ void sideBlockLineWidthSpinnerStateChanged(int value);
 /*private*/ void mainBlockLineWidthSpinnerStateChanged(int value);
 /*private*/ void mainRailGapSpinnerStateChanged(int value);
 /*private*/ void sideRailGapSpinnerStateChanged(int value) ;
 /*private*/ void sideRailWidthSpinnerStateChanged(int value);
 /*private*/ void mainRailWidthSpinnerStateChanged(int value);
 /*private*/ void sideRailCountSpinnerStateChanged(int value);
 /*private*/ void mainRailCountSpinnerStateChanged(int value);
 /*private*/ void applyButtonActionPerformed(/*ActionEvent evt*/);
 /*private*/ void mainRailColorButtonActionPerformed(/*ActionEvent evt*/);
 /*private*/ void sideRailColorButtonActionPerformed(/*ActionEvent evt*/);
 /*private*/ void mainBallastColorButtonActionPerformed(/*ActionEvent evt*/);
 /*private*/ void sideBallastColorButtonActionPerformed(/*ActionEvent evt*/);
 /*private*/ void mainTieColorButtonActionPerformed(/*ActionEvent evt*/);
 /*private*/ void sideTieColorButtonActionPerformed(/*ActionEvent evt*/);
 /*private*/ void mainBlockLineDashPercentageX10SpinnerStateChanged(int value);
 /*private*/ void sideBlockLineDashPercentageX10SpinnerStateChanged(int value);


};

#endif // LAYOUTTRACKDRAWINGOPTIONSDIALOG_H
