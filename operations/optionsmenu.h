#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H
#include "logger.h"
#include <QMenu>
#include "actionevent.h"

class LayoutEditor;
class QRadioButton;
class QSpinBox;
class QComboBox;
class QCheckBox;
class JmriJFrame;
class DispatcherFrame;
class OptionsMenu : public QMenu
{
 Q_OBJECT
public:
 OptionsMenu(DispatcherFrame* f, QWidget*parent = 0);
 /*public*/ void initializeMenu();

private slots:
 /*public*/ void useRosterEntry_actionPerformed(QObject *e);
 /*public*/ void cancelOptions();
 /*public*/ void applyOptions();

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("OptionsMenu");
 // Option menu items
 /*private*/ QAction* autoDispatchItem;// = null;
 /*private*/ QAction* autoTurnoutsItem ;//= null;
 // options window items
 JmriJFrame* optionsFrame = nullptr;
 QWidget* optionsPane = nullptr;
 QCheckBox* useConnectivityCheckBox;// = new JCheckBox(tr("UseConnectivity"));
 QComboBox* layoutEditorBox;// = new JComboBox<String>();
 QList<LayoutEditor*>* layoutEditorList;// = new ArrayList<LayoutEditor>();
 QCheckBox* autoAllocateCheckBox;// = new JCheckBox(tr("AutoAllocateBox"));
 QCheckBox* autoTurnoutsCheckBox;// = new JCheckBox(tr("AutoTurnoutsBox"));
 QRadioButton* trainsFromRoster;// = new JRadioButton(tr("TrainsFromRoster"));
 QRadioButton* trainsFromTrains;// = new JRadioButton(tr("TrainsFromTrains"));
 QRadioButton* trainsFromUser;// = new JRadioButton(tr("TrainsFromUser"));
 QComboBox* signalTypeBox;
 QCheckBox* detectionCheckBox;// = new JCheckBox(tr("DetectionBox"));
 QCheckBox* shortNameCheckBox;// = new JCheckBox(tr("ShortNameBox"));
 QCheckBox* nameInBlockCheckBox;// = new JCheckBox(tr("NameInBlockBox"));
 QCheckBox* rosterInBlockCheckBox;// = new JCheckBox(tr("RosterInBlockBox"));
 QCheckBox* extraColorForAllocatedCheckBox;// = new JCheckBox(tr("ExtraColorForAllocatedBox"));
 QCheckBox* nameInAllocatedBlockCheckBox;// = new JCheckBox(tr("NameInAllocatedBlockBox"));
 QCheckBox* supportVSDecoderCheckBox;// = new JCheckBox(tr("SupportVSDecoder"));
 QComboBox* layoutScaleBox;// = new JComboBox<String>();
 QRadioButton* scaleFeet;// = new JRadioButton(tr("ScaleFeet"));
 QRadioButton* scaleMeters;// = new JRadioButton(tr("ScaleMeters"));
 QCheckBox* openDispatcherWithPanel;// = new JCheckBox(tr("OpenDispatcherWithPanelBox"));
 QSpinBox* minThrottleIntervalSpinner;// = new JSpinner(new SpinnerNumberModel(100, 20, 1000, 1));
 QSpinBox* fullRampTimeSpinner;// = new JSpinner(new SpinnerNumberModel(5000, 1000, 20000, 1));
 QCheckBox* trustKnownTurnoutsCheckBox;// = new JCheckBox(tr("trustKnownTurnouts"));

 QStringList signalTypes;// = {tr("SignalType1"), tr("SignalType2")};
 /*private*/ bool initializeLayoutEditorCombo();

private slots:
 /*private*/ void optionWindowRequested();
 /*private*/ void handleAutoDispatch();
 /*private*/ void handleAutoTurnouts();
 /*private*/ void saveRequested();
 /*private*/ void initializeScaleCombo();

protected:
 /*protected*/ DispatcherFrame* dispatcher = nullptr;

};

#endif // OPTIONSMENU_H
