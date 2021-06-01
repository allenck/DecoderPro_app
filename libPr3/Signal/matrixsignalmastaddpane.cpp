#include "matrixsignalmastaddpane.h"
#include "loggerfactory.h"
#include <QLabel>
#include <QBoxLayout>
#include "defaultsignalappearancemap.h"
#include <QCheckBox>
#include "userpreferencesmanager.h"
#include <QScrollArea>
#include <QComboBox>
#include <QStringList>
#include <QMap>
#include "decimalformat.h"
#include "matrixsignalmast.h"
#include <QGroupBox>
#include <QScrollArea>
#include "flowlayout.h"
#include "beanselectcreatepanel.h"
#include "instancemanager.h"
#include <QGridLayout>
#include "turnout.h"
#include "jmrijframe.h"
#include "signalmastmanager.h"
#include "joptionpane.h"

/**
 * A pane for configuring MatrixSignalMast objects.
 *
 * @see jmri.jmrit.beantable.signalmast.SignalMastAddPane
 * @author Bob Jacobsen Copyright (C) 2018
 * @author Egbert Broerse Copyright (C) 2016
 * @since 4.11.2
 */
///*public*/ class MatrixSignalMastAddPane extends SignalMastAddPane {

/*public*/ MatrixSignalMastAddPane::MatrixSignalMastAddPane(QWidget* parent) : SignalMastAddPane(parent)
{
 resetPreviousState = new QCheckBox(tr("Reset previous Aspect"));
 prefs = static_cast<UserPreferencesManager*>(InstanceManager::getDefault("UserPreferencesManager"));
 matrixBitNumSelectionCombo = QString("jmri.jmrit.beantable.MatrixSignalMastAddPane" )+ ".matrixBitNumSelected";
 allowUnLit = new QCheckBox();
 matrixMastBitnumPanel = new QWidget();
 matrixMastPanel = new QWidget();
 matrixMastPanel->setLayout(new QVBoxLayout());
 matrixMastBitnumPanel = new QWidget();
 emptyChars = "000000"; // size of String = MAXMATRIXBITS; add 7th 0 in order to set > 6
 emptyBits = emptyChars.toLocal8Bit();
 bitNumLabel = new QLabel(tr("%1:").arg(tr("Number of logic outputs")));
 columnChoice = new QComboBox(/*choiceArray()*/);
 columnChoice->addItems(choiceArray());

 matrixAspect = QMap<QString, MatrixAspectPanel*>(/*NOTIONAL_ASPECT_COUNT*/); // LinkedHT type keeps things sorted // only used once, see updateMatrixAspectPanel()
 paddedNumber = new DecimalFormat("0000");

 _matrixUnLitPanel = new QGroupBox();
 matrixUnLitPanelLayout = new QVBoxLayout(_matrixUnLitPanel);
 setObjectName("MatrixSignalMastAddPane");

 /**
  * on = thrown, off = closed, no turnout states asked
  */
 turnoutBox1 = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), nullptr);
 turnoutBox1->setObjectName("turnoutBox1");
 turnoutBox2 = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), nullptr);
 turnoutBox2->setObjectName("turnoutBox2");
 turnoutBox3 = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), nullptr);
 turnoutBox3->setObjectName("turnoutBox3");
 turnoutBox4 = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), nullptr);
 turnoutBox4->setObjectName("turnoutBox4");
 turnoutBox5 = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), nullptr);
 turnoutBox5->setObjectName("turnoutBox5");
 turnoutBox6 = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), nullptr);
 turnoutBox6->setObjectName("turnoutBox6");
     // repeat in order to set MAXMATRIXBITS > 6

 unlitCheck1 = new QCheckBox();
 unlitCheck1->setObjectName("unlitCheck1");
 unlitCheck2 = new QCheckBox();
 unlitCheck2->setObjectName("unlitCheck2");
 unlitCheck3 = new QCheckBox();
 unlitCheck3->setObjectName("unlitCheck3");
 unlitCheck4 = new QCheckBox();
 unlitCheck4->setObjectName("unlitCheck4");
 unlitCheck5 = new QCheckBox();
 unlitCheck5->setObjectName("unlitCheck5");
 unlitCheck6 = new QCheckBox();
 unlitCheck6->setObjectName("unlitCheck6");

    //setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
 QVBoxLayout* thisLayout = new QVBoxLayout(this);
    // lit/unlit controls
    QWidget* p = new QWidget();
    //p ->setLayout(new BoxLayout(p, BoxLayout.X_AXIS));
    QVBoxLayout* pLayout = new QVBoxLayout(p);
    pLayout->addWidget(new QLabel(tr("This Mast can be unlit") + ": "));
    pLayout->addWidget(allowUnLit);
    //p ->setAlignmentX(Component.LEFT_ALIGNMENT);
    thisLayout->addWidget(p);

    thisLayout->addWidget(_matrixUnLitPanel);
    matrixUnLitPanel();

    matrixMastBitnumPanel = makeMatrixMastBitnumPanel(); // create panel
    thisLayout->addWidget(matrixMastBitnumPanel);
    if (prefs->getComboBoxLastSelection(matrixBitNumSelectionCombo) != nullptr) {
        columnChoice->setCurrentText(prefs->getComboBoxLastSelection(matrixBitNumSelectionCombo)); // setting for bitNum
    }
//    QGroupBox* scrollBorder = new QGroupBox();
//    scrollBorder->setLayout(new QVBoxLayout());
    matrixMastScroll = new QScrollArea(/*matrixMastPanel*/);
    matrixMastScroll->setWidget(matrixMastPanel);
    matrixMastScroll->setWidgetResizable(true);
    //matrixMastScroll ->setBorder(BorderFactory.createEmptyBorder());
//    scrollBorder->layout()->addWidget(matrixMastScroll);
    thisLayout->addWidget(/*scrollBorder*/matrixMastScroll);
    // repeat in order to set MAXMATRIXBITS > 6

}


/*private*/ QStringList MatrixSignalMastAddPane::choiceArray() {
    QVector<QString> numberOfOutputs = QVector<QString>(MAXMATRIXBITS);
    for (int i = 0; i < MAXMATRIXBITS; i++) {
        numberOfOutputs.replace(i,QString::number(i + 1));
    }
//    log->debug(tr("Created output combo box: %1", Arrays.toString(numberOfOutputs));
    return numberOfOutputs.toList();
}

/**
 * Set the maximum number of outputs for Matrix Signal Masts Used in
 * combobox and for loops
 */
/*public*/ /*static*/ /*final*/ int MatrixSignalMastAddPane::MAXMATRIXBITS = 6; // Don't set above 6
// 6 Seems the maximum to be able to show in a panel a coded and code below should be extended where marked

/** {@inheritDoc} */
//@Override
/*@Nonnull*/ /*public*/ QString MatrixSignalMastAddPane::getPaneName() {
    return tr("Output Matrix Mast");
}

/** {@inheritDoc} */
//@Override
/*public*/ void MatrixSignalMastAddPane::setAspectNames(/*@Nonnull*/
        SignalAppearanceMap* newMap, SignalSystem* sigSystem) {
    log->debug("setAspectNames(...)");

    //unLitPanelBits = Arrays.copyOf(emptyBits, MAXMATRIXBITS);
    unLitPanelBits = QByteArray(emptyBits);
    unLitPanelBits.chop(MAXMATRIXBITS);
    map = (DefaultSignalAppearanceMap*)newMap;

    // set up rest of panel
    updateMatrixMastPanel(); // show only the correct amount of columns for existing matrixMast

    columnChoice->setCurrentIndex(bitNum - 1); // index of items in list starts counting at 0 while "1" is displayed
}

/** {@inheritDoc} */
//@Override
/*public*/ bool MatrixSignalMastAddPane::canHandleMast(/*@Nonnull*/ SignalMast* mast) {
    //return mast instanceof MatrixSignalMast;
 return qobject_cast<MatrixSignalMast*>(mast) != nullptr;
}

/** {@inheritDoc} */
//@Override
/*public*/ void MatrixSignalMastAddPane::setMast(SignalMast* mast)
{
 log->debug(tr("setMast(%1)").arg((mast==nullptr)?"null":mast->getDisplayName()));
 if (mast == nullptr) {
     currentMast = nullptr;
     return;
 }

 if ((qobject_cast<MatrixSignalMast*>(mast)==nullptr) ) {
     log->error(tr("mast was wrong type: %1 %2").arg(mast->getSystemName()).arg( mast->className()));
     return;
 }

 currentMast = (MatrixSignalMast*) mast;

 bitNum = currentMast->getBitNum(); // number of matrix columns = logic outputs = number of bits per Aspect
 updateMatrixMastPanel(); // show only the correct amount of columns for existing matrixMast
 // @see copyFromAnotherMatrixMastAspect(mast)
 if (map != nullptr)
 {
  QStringListIterator aspects = map->getAspects();
  // in matrixPanel LinkedHashtable, fill in mast settings per aspect
  while (aspects.hasNext())
  {
   QString key = aspects.next(); // for each aspect
   MatrixAspectPanel* matrixPanel = matrixAspect.value(key); // load aspectpanel from hashmap
   matrixPanel->setAspectDisabled(currentMast->isAspectDisabled(key)); // sets a disabled aspect
   if ( ! currentMast->isAspectDisabled(key))
   { // bits not saved in mast when disabled, so we should not load them back in
    QByteArray mastBits = currentMast->getBitsForAspect(key); // same as loading an existing MatrixMast
    QByteArray panelAspectBits;// = Arrays.copyOf(mastBits, MAXMATRIXBITS);
    panelAspectBits = QByteArray(mastBits);// store as [6] character array in panel
    panelAspectBits.chop(MAXMATRIXBITS);
    matrixPanel->updateAspectBits(panelAspectBits);
    matrixPanel->setAspectBoxes(panelAspectBits);
    // sets boxes 1 - MAXMATRIXBITS on aspect sub panel from values in hashmap QByteArray like: 1001
   }
  }
 }

 columnChoice->setCurrentIndex(bitNum - 1); // index of items in list starts counting at 0 while "1" is displayed
 columnChoice->setEnabled(false);
 // fill in the names of the outputs from mast:
 if ( currentMast->getOutputName(1)!=("")) {
     turnoutBox1->setDefaultNamedBean(InstanceManager::turnoutManagerInstance()->getTurnout(currentMast->getOutputName(1))); // load input into turnoutBox1
 }
 if (bitNum > 1 && (currentMast->getOutputName(2) != "")) {
     turnoutBox2->setDefaultNamedBean(InstanceManager::turnoutManagerInstance()->getTurnout(currentMast->getOutputName(2))); // load input into turnoutBox2
 }
 if (bitNum > 2 && (currentMast->getOutputName(3) != "")) {
     turnoutBox3->setDefaultNamedBean(InstanceManager::turnoutManagerInstance()->getTurnout(currentMast->getOutputName(3))); // load input into turnoutBox3
 }
 if (bitNum > 3 && (currentMast->getOutputName(4) != "")) {
     turnoutBox4->setDefaultNamedBean(InstanceManager::turnoutManagerInstance()->getTurnout(currentMast->getOutputName(4))); // load input into turnoutBox4
 }
 if (bitNum > 4 && (currentMast->getOutputName(5) != "")) {
     turnoutBox5->setDefaultNamedBean(InstanceManager::turnoutManagerInstance()->getTurnout(currentMast->getOutputName(5))); // load input into turnoutBox5
 }
 if (bitNum > 5 && (currentMast->getOutputName(6) == "")) {
     turnoutBox6->setDefaultNamedBean(InstanceManager::turnoutManagerInstance()->getTurnout(currentMast->getOutputName(6))); // load input into turnoutBox6
 }
 // repeat in order to set MAXMATRIXBITS > 6
 if (currentMast->resetPreviousStates()) {
     resetPreviousState->setChecked(true);
 }

 //unLitPanelBits = Arrays.copyOf(currentMast.getUnLitBits(), MAXMATRIXBITS); // store as MAXMATRIXBITS character array
 unLitPanelBits  = QByteArray(currentMast->getUnLitBits());
 unLitPanelBits.chop(MAXMATRIXBITS);
 unlitCheck1 ->setChecked(unLitPanelBits[0] == '1'); // set checkboxes
 if (bitNum > 1) {
     unlitCheck2 ->setChecked(unLitPanelBits[1] == '1');
 }
 if (bitNum > 2) {
     unlitCheck3 ->setChecked(unLitPanelBits[2] == '1');
 }
 if (bitNum > 3) {
     unlitCheck4 ->setChecked(unLitPanelBits[3] == '1');
 }
 if (bitNum > 4) {
     unlitCheck5 ->setChecked(unLitPanelBits[4] == '1');
 }
 if (bitNum > 5) {
     unlitCheck6 ->setChecked(unLitPanelBits[5] == '1');
 }
 // repeat in order to set MAXMATRIXBITS > 6

 allowUnLit ->setChecked(currentMast->allowUnLit());

 log->trace(tr("setMast %1 end").arg(mast->getDisplayName()));
}

/** {@inheritDoc} */
//@Override
/*public*/ bool MatrixSignalMastAddPane::createMast(/*@Nonnull*/ QString sigsysname, /*@Nonnull*/ QString mastname, /*@Nonnull*/ QString username) {
    log->debug(tr("createMast(%1,%2)").arg(sigsysname).arg(mastname));

    // check all boxes are filled
    if (       (              ( turnoutBox1 ->getDisplayName() == nullptr || turnoutBox1 ->getDisplayName().isEmpty() ) )
            || (bitNum > 1 && ( turnoutBox2 ->getDisplayName() == nullptr || turnoutBox2 ->getDisplayName().isEmpty() ) )
            || (bitNum > 2 && ( turnoutBox3 ->getDisplayName() == nullptr || turnoutBox3 ->getDisplayName().isEmpty() ) )
            || (bitNum > 3 && ( turnoutBox4 ->getDisplayName() == nullptr || turnoutBox4 ->getDisplayName().isEmpty() ) )
            || (bitNum > 4 && ( turnoutBox5 ->getDisplayName() == nullptr || turnoutBox5 ->getDisplayName().isEmpty() ) )
            || (bitNum > 5 && ( turnoutBox6 ->getDisplayName() == nullptr || turnoutBox6 ->getDisplayName().isEmpty() ) )
    ) {
        // add extra OR in order to set MAXMATRIXBITS > 6
        // error dialog
        JOptionPane::showMessageDialog(nullptr,
                tr("At least one of the Outputs has not been defined.\n Please set all Outputs for this mast %1 and press Create again.").arg( mastname),
                tr("Warning"),
                JOptionPane::ERROR_MESSAGE);
        log->warn("Empty output on panel");
        return false;
    }

    // check if bit sets are identical
    if (identicalBits()) {
        // error dialog
        JOptionPane::showMessageDialog(nullptr,
                tr("Matrix is incomplete or showing duplicates.\nHint: at least %1 outputs needed for %2 active Aspects.").arg((int) qSqrt(numberOfActiveAspects)).arg(numberOfActiveAspects),
                tr("Warning"),
                JOptionPane::ERROR_MESSAGE);
        log->warn("Identical bits on panel");
        return false;
    }

    if (currentMast == nullptr) {
        // Create was pressed for new mast:
        // create new MatrixMast with props from panel
        QString name = "IF$xsm:"
                + sigsysname
                + ":" + mastname.mid(11, mastname.length() - 15);
        name += QString("($") + (paddedNumber->format(MatrixSignalMast::getLastRef() + 1));
        name += QString(")") + "-" + QString::number(bitNum )+ "t"; // for the number of t = "turnout-outputs", add option for direct packets
        currentMast = new MatrixSignalMast(name);
        static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->Register(currentMast);
    }

    QString name = currentMast->getSystemName();

    currentMast ->setBitNum(bitNum); // store number of columns in aspect - outputs matrix in mast

    //store outputs from turnoutBoxes; method in line 976
    currentMast ->setOutput("output1", turnoutBox1 ->getDisplayName()); // store choice from turnoutBox1
    setMatrixReference(turnoutBox1, name + ":output1"); // write mast name to output1 bean comment
    if (bitNum > 1) {
        currentMast ->setOutput("output2", turnoutBox2 ->getDisplayName()); // store choice from turnoutBox2
        setMatrixReference(turnoutBox2, name + ":output2"); // write mast name to output2 bean comment
        if (bitNum > 2) {
            currentMast ->setOutput("output3", turnoutBox3 ->getDisplayName()); // store choice from turnoutBox3
            setMatrixReference(turnoutBox3, name + ":output3"); // write mast name to output3 bean comment
            if (bitNum > 3) {
                currentMast ->setOutput("output4", turnoutBox4 ->getDisplayName()); // store choice from turnoutBox4
                setMatrixReference(turnoutBox4, name + ":output4"); // write mast name to output4 bean comment
                if (bitNum > 4) {
                    currentMast ->setOutput("output5", turnoutBox5 ->getDisplayName()); // store choice from turnoutBox5
                    setMatrixReference(turnoutBox5, name + ":output5"); // write mast name to output5 bean comment
                    if (bitNum > 5) {
                        currentMast ->setOutput("output6", turnoutBox6 ->getDisplayName()); // store choice from turnoutBox6
                        setMatrixReference(turnoutBox6, name + ":output6"); // write mast name to output6 bean comment
                        // repeat in order to set MAXMATRIXBITS > 6
                    }
                }
            }
        }
    }

    for (QString aspect : matrixAspect.keys()) {
        // store matrix in mast per aspect, compare with line 991
        matrixMastPanel->layout()->addWidget(matrixAspect.value(aspect)->getPanel()); // read from aspect panel to mast
        if (matrixAspect.value(aspect)->isAspectDisabled()) {
            currentMast ->setAspectDisabled(aspect); // don't store bits when this aspect is disabled
        } else {
            currentMast ->setAspectEnabled(aspect);
            currentMast ->setBitsForAspect(aspect, matrixAspect.value(aspect)->trimAspectBits()); // return as QByteArray
        }
    }
    currentMast->resetPreviousStates(resetPreviousState ->isChecked()); // read from panel, not displayed?

    currentMast ->setAllowUnLit(allowUnLit ->isChecked());

    // copy bits from UnLitPanel var unLitPanelBits
    try {
        currentMast ->setUnLitBits(trimUnLitBits());
    } catch (Exception ex) {
        log->error("failed to read and copy unLitPanelBits");
    }

    if (username != "") {
        currentMast ->setUserName(username);
    }

    prefs ->setComboBoxLastSelection(matrixBitNumSelectionCombo,  columnChoice->currentText()); // store bitNum pref

    currentMast ->setAllowUnLit(allowUnLit ->isChecked());

    return true;
}

/**
 * Create bitNumPanel with drop down to set number of columns, separate from
 * the rest for redraw.
 * <p>
 * Auto refresh to show/hide input (turnout) selection boxes. Hide/show
 * checkboxes in matrix (per aspect).
 *
 * @return a JPanel with a comboBox to select number of outputs, set at
 *         current value
 */
QGroupBox* MatrixSignalMastAddPane::makeMatrixMastBitnumPanel() {
    QGroupBox* bitnumpanel = new QGroupBox();
    //itnumpanel ->setLayout(new FlowLayout(FlowLayout.LEADING));
    FlowLayout* bitnumpanelLayout = new FlowLayout(bitnumpanel);
    // select number of columns in logic matrix
    bitnumpanelLayout->addWidget(bitNumLabel);
    bitnumpanelLayout->addWidget(columnChoice); // drop down list 1 - 5
    if (bitNum < 1 || bitNum > MAXMATRIXBITS) {
        bitNum = 4; // default to 4 col for (first) new mast
    }
    columnChoice->setCurrentIndex(bitNum - 1);
//    columnChoice.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            QString newBitnumString = (String) columnChoice.getSelectedItem();
//            bitNumChanged(Integer.valueOf(newBitnumString));
//        }
//    });
    connect(columnChoice, SIGNAL(currentIndexChanged(int)), this, SLOT(bitNumChanged(int)));
    return bitnumpanel;
}

/*public*/ void MatrixSignalMastAddPane::onColumnChoice(/*ActionEvent e*/) {
    QString newBitnumString = columnChoice->currentText();
    bitNumChanged((newBitnumString).toInt());
}


/**
 * @return QByteArray of length bitNum copied from unLitPanelBits
 */
/*protected*/ QByteArray MatrixSignalMastAddPane::trimUnLitBits() {
 QByteArray copy;
    if (!unLitPanelBits.isNull()) {
        //return Arrays.copyOf(unLitPanelBits, bitNum);
     // return unLitPanelBits.chopped(bitNum); // Qt 5.10
     copy = QByteArray(unLitPanelBits);
    } else {
        //return Arrays.copyOf(emptyBits, bitNum);
     copy = QByteArray(emptyBits);
    }
    copy.chop(bitNum);
    return copy;
}

/**
 * Build lower half of Add Signal Mast panel, specifically for Matrix Mast.
 * <p>
 * Called when Mast Type drop down changes.
 */
void MatrixSignalMastAddPane::updateMatrixMastPanel()
{
 matrixAspect = QMap<QString, MatrixAspectPanel*>(/*NOTIONAL_ASPECT_COUNT*/);

 // nothing to if no map yet
 if (map == nullptr) return;

 QStringListIterator aspects = map->getAspects();
 while (aspects.hasNext())
 {
  QString aspect = aspects.next();
  MatrixAspectPanel* aspectpanel = new MatrixAspectPanel(aspect, this);
  aspectpanel->setObjectName("MatrixAspectPanel");
  matrixAspect.insert(aspect, aspectpanel); // store in LinkedHashMap
  // values are filled in later
 }

 //matrixMastPanel.removeAll();
 QObjectList ol = matrixMastPanel->layout()->children();
 foreach (QObject* obj, ol) {
  if(qobject_cast<QWidget*>(obj)!= nullptr){
   matrixMastPanel->layout()->removeWidget(qobject_cast<QWidget*>(obj));
   log->debug(tr("remove %1").arg(obj->objectName()));
   delete qobject_cast<QWidget*>(obj);
  }
  if(qobject_cast<QLayout*>(obj)!= nullptr)
   delete obj;
 }
// delete matrixMastPanel->layout();
// matrixMastPanel->setLayout(new QVBoxLayout());

 // sub panels (so we can hide all turnouts with Output Type drop down box later)
 QWidget* turnoutpanel = new QWidget();
 turnoutpanel->setObjectName("turnoutpanel");
 QVBoxLayout* turnoutpanelLayout = new QVBoxLayout(turnoutpanel);

 // binary matrix outputs follow:
 QGroupBox* output1panel = new QGroupBox();
 output1panel->setObjectName("output1panel");
 QVBoxLayout* output1panelLayout = new QVBoxLayout(output1panel);
 output1panelLayout->addWidget(turnoutBox1);
//    TitledBorder border1 = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black));
//    border1 ->setTitle(tr("MatrixOutputLabel", 1));
//    output1panel ->setBorder(border1);
 output1panel->setTitle(tr("Output %1 ").arg(1));
 turnoutpanelLayout->addWidget(output1panel);

 QGroupBox* output2panel = new QGroupBox();
 output2panel->setObjectName("output2panel");
 QVBoxLayout* output2panelLayout = new QVBoxLayout(output2panel);
 output2panelLayout->addWidget(turnoutBox2);
 output2panel->setTitle(tr("Output %1 ").arg(2));
 turnoutpanelLayout->addWidget(output2panel);

 QGroupBox* output3panel = new QGroupBox();
 output3panel->setObjectName("output3panel");
 QVBoxLayout* output3panelLayout = new QVBoxLayout(output3panel);
 output3panelLayout->addWidget(turnoutBox3);
 output3panel->setTitle(tr("Output %1 ").arg(3));
 turnoutpanelLayout->addWidget(output3panel);

 QGroupBox* output4panel = new QGroupBox();
 output4panel->setObjectName("output4panel");
 QVBoxLayout* output4panelLayout = new QVBoxLayout(output4panel);
 output4panelLayout->addWidget(turnoutBox4);
 output4panel->setTitle(tr("Output %1 ").arg(4));
 turnoutpanelLayout->addWidget(output4panel);

 QGroupBox* output5panel = new QGroupBox();
 output5panel->setObjectName("output5panel");
 QVBoxLayout* output5panelLayout = new QVBoxLayout(output5panel);
 output5panelLayout->addWidget(turnoutBox5);
 output5panel->setTitle(tr("Output %1 ").arg(5));
 turnoutpanelLayout->addWidget(output5panel);

 QGroupBox* output6panel = new QGroupBox();
 output6panel->setObjectName("output6panel");
 QVBoxLayout* output6panelLayout = new QVBoxLayout(output6panel);
 output6panelLayout->addWidget(turnoutBox6);
 output6panel->setTitle(tr("Output %1 ").arg(6));
 turnoutpanelLayout->addWidget(output6panel);

 // repeat in order to set MAXMATRIXBITS > 6
 // output1panel always on
 output2panel->setVisible(bitNum > 1);
 output3panel->setVisible(bitNum > 2);
 output4panel->setVisible(bitNum > 3);
 output5panel->setVisible(bitNum > 4);
 output6panel->setVisible(bitNum > 5);
 // repeat in order to set MAXMATRIXBITS > 6

 matrixMastPanel->layout()->addWidget(turnoutpanel);

 unlitCheck2 ->setVisible(bitNum > 1);
 unlitCheck3 ->setVisible(bitNum > 2);
 unlitCheck4 ->setVisible(bitNum > 3);
 unlitCheck5 ->setVisible(bitNum > 4);
 unlitCheck6 ->setVisible(bitNum > 5);
 // repeat in order to set MAXMATRIXBITS > 6

 QWidget* matrixHeader = new QWidget();
 matrixHeader->setObjectName("matrixHeader");
 QHBoxLayout* matrixHeaderLayout = new QHBoxLayout(matrixHeader);
 QLabel* matrixHeaderLabel = new QLabel(tr("For each enabled Aspect, check a unique combination of Outputs 1 to %1:").arg(bitNum));/*, JLabel.CENTER)*/;
 matrixHeaderLayout->addWidget(matrixHeaderLabel, 0, Qt::AlignCenter);
 matrixHeaderLabel->setToolTip(tr("Box checked = On = Closed; unchecked = Off = Thrown"));
 matrixMastPanel->layout()->addWidget(matrixHeader);

 for (QString aspect : matrixAspect.keys()) {
     matrixMastPanel->layout()->addWidget(matrixAspect.value(aspect)->getPanel()); // load Aspect sub panels to matrixMastPanel from hashmap
     // build aspect sub panels
 }
 if ((matrixAspect.size() & 1) == 1) {
     // spacer before "Reset previous aspect"
     matrixMastPanel->layout()->addWidget(new QLabel());
 }

 matrixMastPanel->layout()->addWidget(resetPreviousState); // checkbox

 resetPreviousState ->setToolTip(tr("Select to reset the previous Aspect command to Dark before setting the new Aspect."));
 // copy option matrixMast bitstrings = settings
 QWidget* matrixCopyPanel = new JPanel();
 matrixCopyPanel ->setLayout(new FlowLayout(/*FlowLayout.LEADING)*/));
 matrixCopyPanel->layout()->addWidget(new QLabel(tr("Copy Aspect Matrix from Mast") + ":"));
 matrixCopyPanel->layout()->addWidget(copyFromMastSelection());
 matrixMastPanel->layout()->addWidget(matrixCopyPanel);

// ??    matrixMastPanel ->setLayout(new jmri.util.javaworld.GridLayout2(0, 1)); // 0 means enough
 matrixMastPanel->update();
}

 /**
 * When the user changes the number of columns in matrix from the drop down:
 * store the new value.
 *
 * @param newColNum int with the new value = the number of columns in the
 *                  Matrix Table
 */
void MatrixSignalMastAddPane::bitNumChanged(int newColNum) {
    if (newColNum < 1 || newColNum > MAXMATRIXBITS || newColNum == bitNum) {
        return;
    }
    bitNum = newColNum;
    // hide/show output choices per Aspect

    updateMatrixMastPanel();

    update();
    QWidget* _window = window();
    if (_window != nullptr && qobject_cast<JmriJFrame*>(_window)) {
        ((JmriJFrame*) _window) ->resize(((JmriJFrame*) _window)->sizeHint());
        ((JmriJFrame*) _window)->pack();
    }
    repaint();

}


/**
 * Write matrix mast name + output no. to output bean comment.
 *
 * @param bp           the bean panel containing the Turnout (output)
 * @param functionName Description of turnout function on mast
 */
void MatrixSignalMastAddPane::setMatrixReference(BeanSelectCreatePanel* bp, QString functionName) {
    //System.out.println("box: " + bp ->getDisplayName()); // debug
    //System.out.println("name: " + functionName); // debug
    bp ->setReference(functionName);
}

void MatrixSignalMastAddPane::copyFromAnotherMatrixMastAspect(QString strMast) {
    MatrixSignalMast* mast = (MatrixSignalMast*) static_cast<SignalMastManager*>( InstanceManager::getDefault("SignalMastManager"))->getNamedBean(strMast);
    if (mast == nullptr) {
        log->error(tr("Cannot copy from mast %1 which doesn't exist").arg(strMast));
        return;
    }
    if (bitNum != mast->getBitNum()) {
        int i = JOptionPane::showConfirmDialog(nullptr, tr("The chosen original has %1 instead of %2 columns.\nContinue?").arg(mast->getBitNum()).arg(bitNum),
                tr("Number of Columns mismatch"),
                JOptionPane::YES_NO_OPTION);
        if (i != 0) {
            return;
        }
    }
    // cf. line 405 loading an existing mast for edit
    for (QString key : matrixAspect.keys()) {
        // select the correct checkboxes
        MatrixAspectPanel* matrixPanel = matrixAspect.value(key); // load aspectpanel from hashmap
        matrixPanel ->setAspectDisabled(mast->isAspectDisabled(key)); // sets a disabled aspect
        if (!mast->isAspectDisabled(key)) {
            QByteArray mastBits = mast->getBitsForAspect(key); // same as loading an existing MatrixMast
            QByteArray panelAspectBits;//= Arrays.copyOf(mastBits, MAXMATRIXBITS); // store as 6 character array in panel
            panelAspectBits= QByteArray(mastBits);
            panelAspectBits.chop(MAXMATRIXBITS);
            matrixPanel->updateAspectBits(panelAspectBits);
            matrixPanel ->setAspectBoxes(panelAspectBits);
            // sets boxes 1 - MAXMATRIXBITS on aspect sub panel from values in hashmap QByteArray like: 1001
        }
    }
}

/**
 * Call for sub panel per aspect from hashmap matrixAspect with check boxes
 * to set properties.
 * <p>
 * Invoked when updating MatrixMastPanel
 *
 * @see #updateMatrixMastPanel()
 */
void MatrixSignalMastAddPane::updateMatrixAspectPanel() {
    QStringListIterator aspects = map->getAspects();
    while (aspects.hasNext()) {
        QString aspect = aspects.next();
        MatrixAspectPanel* aspectpanel = new MatrixAspectPanel(aspect, bitString,this); // build 1 line, picking up bitString
        matrixAspect.insert(aspect, aspectpanel); // store that line
    }
    // refresh aspects list
    // TODO sort matrixAspect HashTable, which at this point is not sorted
    //matrixMastPanel.removeAll();
    QObjectList ol = matrixMastPanel->layout()->children();
    for (QString aspect : matrixAspect.keys()) {
        matrixMastPanel->layout()->addWidget(matrixAspect.value(aspect)->getPanel());
        // Matrix checkbox states are set by getPanel()
    }

// ??    matrixMastPanel ->setLayout(new jmri.util.javaworld.GridLayout2(0, 1)); // 0 means enough
    matrixMastPanel->update();
}


/**
 * JPanel to set outputs for an unlit (Dark) Matrix Signal Mast.
 */
void MatrixSignalMastAddPane::matrixUnLitPanel() {
    if (bitNum < 1 || bitNum > MAXMATRIXBITS) {
        bitNum = 4; // default to 4 col for (first) new mast
    }

    QWidget* matrixUnLitDetails = new QWidget();
    //matrixUnLitDetails ->setLayout(new jmri.util.javaworld.GridLayout2(1, 1)); // stretch to full width
    QGridLayout* matrixUnLitDetailsLayout = new QGridLayout(matrixUnLitDetails);

    matrixUnLitDetailsLayout->addWidget(unlitCheck1,0,0);
    matrixUnLitDetailsLayout->addWidget(unlitCheck2,0,1);
    matrixUnLitDetailsLayout->addWidget(unlitCheck3,0,2);
    matrixUnLitDetailsLayout->addWidget(unlitCheck4,0,3);
    matrixUnLitDetailsLayout->addWidget(unlitCheck5,0,4);
    matrixUnLitDetailsLayout->addWidget(unlitCheck6,0,5);
    // repeat in order to set MAXMATRIXBITS > 6

    matrixUnLitPanelLayout->addWidget(matrixUnLitDetails);

//    TitledBorder border = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black));
//    border ->setTitle(tr("MatrixUnLitDetails"));
   // matrixUnLitPanel ->setBorder(border);
    _matrixUnLitPanel->setTitle("Outputs for Unlit");
    _matrixUnLitPanel ->setToolTip(tr("When active, set identical to a Dark/Unlit aspect below"));
    QSignalMapper* mapper = new QSignalMapper(this);

//    unlitCheck1.addActionListener(new ActionListener() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            setUnLitBit(1, unlitCheck1 ->isChecked());
//        }
//    });
    unlitCheck1->setProperty("id",1);
    mapper->setMapping(unlitCheck1,unlitCheck1);
    connect(unlitCheck1, SIGNAL(toggled(bool)), mapper, SLOT(map()));
//    unlitCheck2.addActionListener(new ActionListener() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            setUnLitBit(2, unlitCheck2 ->isChecked());
//        }
//    });
    unlitCheck2->setProperty("id",2);
    mapper->setMapping(unlitCheck2,unlitCheck2);
    connect(unlitCheck2, SIGNAL(toggled(bool)), mapper, SLOT(map()));
//    unlitCheck3.addActionListener(new ActionListener() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            setUnLitBit(3, unlitCheck3 ->isChecked());
//        }
//    });
    unlitCheck3->setProperty("id",3);
    mapper->setMapping(unlitCheck3,unlitCheck3);
    connect(unlitCheck3, SIGNAL(toggled(bool)), mapper, SLOT(map()));
//    unlitCheck4.addActionListener(new ActionListener() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            setUnLitBit(4, unlitCheck4 ->isChecked());
//        }
//    });
    unlitCheck4->setProperty("id",4);
    mapper->setMapping(unlitCheck4,unlitCheck4);
    connect(unlitCheck4, SIGNAL(toggled(bool)), mapper, SLOT(map()));
//    unlitCheck5.addActionListener(new ActionListener() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            setUnLitBit(5, unlitCheck5 ->isChecked());
//        }
//    });
    unlitCheck5->setProperty("id",5);
    mapper->setMapping(unlitCheck5,unlitCheck5);
    connect(unlitCheck5, SIGNAL(toggled(bool)), mapper, SLOT(map()));
//    unlitCheck6.addActionListener(new ActionListener() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            setUnLitBit(6, unlitCheck6 ->isChecked());
//        }
//    });
    unlitCheck6->setProperty("id",6);
    mapper->setMapping(unlitCheck6,unlitCheck6);
    connect(unlitCheck6, SIGNAL(toggled(bool)), mapper, SLOT(map()));
    // repeat in order to set MAXMATRIXBITS > 6
  connect(mapper, SIGNAL(mapped(QObject*)), this, SLOT(onUnlitCheck(QObject*)));
}

void MatrixSignalMastAddPane::onUnlitCheck(QObject * obj)
{
 Q_ASSERT(qobject_cast<QCheckBox*>(obj)!=nullptr);
 QCheckBox* box = qobject_cast<QCheckBox*>(obj);
 setUnLitBit(box->property("id").toInt(), box->isChecked());
}

QComboBox* MatrixSignalMastAddPane::copyFromMastSelection() {
    QComboBox* mastSelect = new QComboBox();
    QStringList names = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getSystemNameList();

    for (QString name : names) {
        // only accept MatrixSignalMast masts
        if (static_cast<MatrixSignalMast*>(static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getNamedBean(name))!= nullptr) {
            SignalMast* m = (SignalMast*) static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getNamedBean(name);
            if (m!=nullptr) {
                mastSelect->addItem(m->getDisplayName());
            } else {
                log->error(tr("Can't copy from mast %1 as it doesn't exist").arg(name));
            }
        }
    }
    if (mastSelect->count() == 0) {
        mastSelect ->setEnabled(false);
    } else {
        mastSelect->insertItem(0, "");
        //mastSelect ->setCheckedIndex(0);
        mastSelect->setCurrentIndex(0);
//        mastSelect.addActionListener(new ActionListener() {
//            @SuppressWarnings("unchecked") // e.getSource() cast from mastSelect source
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                JComboBox<String> eb = (JComboBox<String>) e.getSource();
//                String sourceMast = (String) eb.getSelectedItem();
//                if (sourceMast != null && !sourceMast == "")) {
//                    copyFromAnotherMatrixMastAspect(sourceMast);
//                }
//            }
//        });
        connect(mastSelect, SIGNAL(currentTextChanged(QString)), this, SLOT(copyFromAnotherMatrixMastAspect(QString)));
    }

    return mastSelect;
}

/**
 * Update the on/off positions for the unLitPanelBits QByteArray.
 * <p>
 * Invoked from bit checkboxes 1 to MAXMATRIXBITS on unLitPanel.
 *
 * @param column int as index for an output (between 1 and 6)
 * @param state  bool for the output On (Closed) or Off (Thrown)
 */
/*public*/ void MatrixSignalMastAddPane::setUnLitBit(int column, bool state) {
    if (state == true) {
        unLitPanelBits[column - 1] = '1';
    }
    if (state == false) {
        unLitPanelBits[column - 1] = '0';
    }
}

/**
 * Check all aspects for duplicate bit combos.
 *
 * @return true if at least 1 duplicate row of bits is found
 */
/*private*/ bool MatrixSignalMastAddPane::identicalBits() {
 bool identical = false;
 numberOfActiveAspects = 0;
 QSet<QString> seenBits =  QSet<QString>(); // a fast access, no duplicates Collection of bit combinations
 for (QString aspect : matrixAspect.keys())
 {
  // check per aspect
  if (matrixAspect.value(aspect)->isAspectDisabled())
  {
   continue; // skip disabled aspects
  }
  else if (seenBits.contains(stringValueOf(matrixAspect.value(aspect)->trimAspectBits())))
  {
   identical = true;
   log->debug(tr("-found duplicate %1").arg( stringValueOf(matrixAspect.value(aspect)->trimAspectBits())));
   // break; // don't break, so we can count number of enabled aspects for this mast
  }
  else
  {
   seenBits.insert(stringValueOf(matrixAspect.value(aspect)->trimAspectBits())); // convert back from QByteArray to String
//            log->debug(tr("-added new %1; seenBits = %2").arg( stringValueOf(matrixAspect.value(aspect)->trimAspectBits()), seenBits.toString());
  }
  ++numberOfActiveAspects;
 }
 return identical;
}

QString MatrixSignalMastAddPane::stringValueOf(QByteArray ba)
{
 return QTextCodec::codecForMib(1015)->toUnicode(ba);
}

/**
 * JPanel to define properties of an Aspect for a Matrix Signal Mast.
 * <p>
 * Invoked from the AddSignalMastPanel class when a Matrix Signal Mast is
 * selected.
 *
 * @author Egbert Broerse
 */
//class MatrixAspectPanel {

//    JCheckBox disabledCheck = new JCheckBox(tr("DisableAspect"));
//    JCheckBox bitCheck1 = new JCheckBox();
//    JCheckBox bitCheck2 = new JCheckBox();
//    JCheckBox bitCheck3 = new JCheckBox();
//    JCheckBox bitCheck4 = new JCheckBox();
//    JCheckBox bitCheck5 = new JCheckBox();
//    JCheckBox bitCheck6 = new JCheckBox();
//    // repeat in order to set MAXMATRIXBITS > 6
//    JTextField aspectBitsField = new JTextField(MAXMATRIXBITS); // for debug
//    String aspect = "";
//    String emptyChars = "000000"; // size of String = MAXMATRIXBITS; add 0 in order to set > 6
//    QByteArray emptyBits = emptyChars.toCharArray();
//    QByteArray aspectBits = emptyBits;

 /**
  * Build new aspect matrix panel called when Add Signal Mast Pane is
  * built
  *
  * @param aspect String like "Clear"
  */
 MatrixAspectPanel::MatrixAspectPanel(QString aspect, MatrixSignalMastAddPane* addPane)
 {
  common();
  this->addPane = addPane;
     this->aspect = aspect;
 }

 /**
  * Rebuild an aspect matrix panel using QByteArray previously entered called
  * from line 1870 when number of columns is changed (new mast creeation
  * only)
  *
  * @param aspect    String like "Clear"
  * @param panelBits QByteArray of up to 5 1's and 0's
  */
 MatrixAspectPanel::MatrixAspectPanel(QString aspect, QByteArray panelBits, MatrixSignalMastAddPane* addPane) {
 common();
  this->addPane = addPane;

     if (panelBits.isNull() || panelBits.length() == 0) {
         return;
     }
     this->aspect = aspect;
     // aspectBits is QByteArray of length(bitNum) describing state of on/off checkboxes
     // i.e. "0101" provided as QByteArray array
     // easy to manipulate by index
     // copy to checkbox states:
     aspectBits = panelBits;

     setAspectBoxes(aspectBits);

 }

 void MatrixAspectPanel::common()
 {
  disabledCheck = new QCheckBox(tr("Disable Aspect"));
  bitCheck1 = new QCheckBox();
  bitCheck2 = new QCheckBox();
  bitCheck3 = new QCheckBox();
  bitCheck4 = new QCheckBox();
  bitCheck5 = new QCheckBox();
  bitCheck6 = new QCheckBox();
  // repeat in order to set MAXMATRIXBITS > 6
  aspectBitsField = new JTextField(MatrixSignalMastAddPane::MAXMATRIXBITS); // for debug
  aspect = "";
  emptyChars = "000000"; // size of String = MAXMATRIXBITS; add 0 in order to set > 6
  emptyBits;// = emptyChars.toCharArray();
  aspectBits;// = emptyBits;
  panel = nullptr;
 }

 void MatrixAspectPanel::updateAspectBits(QByteArray newBits) {
     aspectBits = newBits;
 }

 bool MatrixAspectPanel::isAspectDisabled() {
     return disabledCheck->isChecked();
 }

 /**
  * Set an Aspect Panels elements inactive.
  * <p>
  * Invoked from Disabled (aspect) checkbox and from Edit mast pane.
  *
  * @param boo true (On) or false (Off)
  */
 void MatrixAspectPanel::setAspectDisabled(bool boo) {
     disabledCheck ->setChecked(boo);
     if (boo) { // disable all (output bit) checkboxes on this aspect panel
         // aspectBitsField always Disabled
         bitCheck1->setEnabled(false);
         if (addPane->bitNum > 1) {
             bitCheck2->setEnabled(false);
         }
         if (addPane->bitNum > 2) {
             bitCheck3 ->setEnabled(false);
         }
         if (addPane->bitNum > 3) {
             bitCheck4 ->setEnabled(false);
         }
         if (addPane->bitNum > 4) {
             bitCheck5 ->setEnabled(false);
         }
         if (addPane->bitNum > 5) {
             bitCheck6 ->setEnabled(false);
         }
         // repeat in order to set MAXMATRIXBITS > 6
     } else { // enable all (output bit) checkboxes on this aspect panel
         // aspectBitsField always Disabled
         bitCheck1 ->setEnabled(true);
         if (addPane->bitNum > 1) {
             bitCheck2 ->setEnabled(true);
         }
         if (addPane->bitNum > 2) {
             bitCheck3 ->setEnabled(true);
         }
         if (addPane->bitNum > 3) {
             bitCheck4 ->setEnabled(true);
         }
         if (addPane->bitNum > 4) {
             bitCheck5 ->setEnabled(true);
         }
         if (addPane->bitNum > 5) {
             bitCheck6 ->setEnabled(true);
         }
         // repeat in order to set MAXMATRIXBITS > 6
     }
 }

 /**
  * Update the on/off positions for an Aspect in the aspectBits QByteArray.
  * <p>
  * Invoked from bit checkboxes 1 to MAXMATRIXBITS on aspectPanels.
  *
  * @param column int of the output (between 1 and MAXMATRIXBITS)
  * @param state  bool for the output On (Closed) or Off (Thrown)
  * @see #aspectBits
  */
 /*public*/ void MatrixAspectPanel::setBit(int column, bool state) {
     if (state == true) {
         aspectBits[column - 1] = '1';
     }
     if (state == false) {
         aspectBits[column - 1] = '0';
     }
     //QString value = String.valueOf(aspectBits); // convert back from QByteArray to String
     QString value = QTextCodec::codecForMib(1015)->toUnicode(aspectBits);
     aspectBitsField->setText(value);
 }

 /**
  * Send the on/off positions for an Aspect to mast.
  *
  * @return A QByteArray of '1' and '0' elements with a length between 1 and
  *         5 corresponding with the number of outputs for this mast
  * @see jmri.implementation.MatrixSignalMast
  */
 QByteArray MatrixAspectPanel::trimAspectBits()
 {
  try
  {
         //return aspectBits;
         //return Arrays.copyOf(aspectBits, bitNum); // copy to new QByteArray of length bitNum
   QByteArray rslt = QByteArray(aspectBits);
   rslt.chop(addPane->bitNum);
   return rslt;
  } catch (Exception ex) {
      addPane->log->error("failed to read and copy aspectBits");
      return nullptr;
  }
 }

 /**
  * Activate the corresponding checkboxes on a MatrixApectPanel.
  *
  * @param aspectBits A QByteArray of '1' and '0' elements with a length
  *                   between 1 and 5 corresponding with the number of
  *                   outputs for this mast
  */
 /*private*/ void MatrixAspectPanel::setAspectBoxes(QByteArray aspectBits) {
     bitCheck1 ->setChecked(aspectBits[0] == '1');
     if (addPane->bitNum > 1) {
         bitCheck2 ->setChecked(aspectBits[1] == '1');
     }
     if (addPane->bitNum > 2) {
         bitCheck3 ->setChecked(aspectBits[2] == '1');
     }
     if (addPane->bitNum > 3) {
         bitCheck4 ->setChecked(aspectBits[3] == '1');
     }
     if (addPane->bitNum > 4) {
         bitCheck5 ->setChecked(aspectBits[4] == '1');
     }
     if (addPane->bitNum > 5) {
         bitCheck6 ->setChecked(aspectBits[5] == '1');
     }
     // repeat in order to set MAXMATRIXBITS > 6
     //QString value = String.valueOf(aspectBits); // convert back from QByteArray to String
     QString value = QTextCodec::codecForMib(1015)->toUnicode(aspectBits);
     aspectBitsField->setText(value);
 }


 /**
  * Build a JPanel for an Aspect Matrix row.
  *
  * @return JPanel to be displayed on the Add/Edit Signal Mast panel
  */
 QGroupBox* MatrixAspectPanel::getPanel()
 {
 if (panel == nullptr) {
     panel = new QGroupBox();
     panel->setObjectName("panel_"+aspect);
     //panel ->setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
     QVBoxLayout* panelLayout = new QVBoxLayout(panel);

     QWidget* matrixDetails = new QWidget();
     QHBoxLayout* matrixDetailsLayout = new QHBoxLayout(matrixDetails);
     matrixDetailsLayout->addWidget(disabledCheck);
     matrixDetailsLayout->addWidget(bitCheck1);
     matrixDetailsLayout->addWidget(bitCheck2);
     matrixDetailsLayout->addWidget(bitCheck3);
     matrixDetailsLayout->addWidget(bitCheck4);
     matrixDetailsLayout->addWidget(bitCheck5);
     matrixDetailsLayout->addWidget(bitCheck6);
     // repeat in order to set MAXMATRIXBITS > 6
     // ToDo refresh aspectSetting, can be in OKPressed() to store/warn for duplicates (with button 'Ignore')
     // hide if id > bitNum (var in panel)
     bitCheck2->setVisible(addPane->bitNum > 1);
     bitCheck3->setVisible(addPane->bitNum > 2);
     bitCheck4->setVisible(addPane->bitNum > 3);
     bitCheck5->setVisible(addPane->bitNum > 4);
     bitCheck6->setVisible(addPane->bitNum > 5);
     // repeat in order to set MAXMATRIXBITS > 6
     matrixDetailsLayout->addWidget(aspectBitsField);
     aspectBitsField ->setEnabled(false); // not editable, just for debugging
     aspectBitsField->setVisible(false); // set to true to check/debug

     panelLayout->addWidget(matrixDetails);
//            TitledBorder border = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black));
//            border ->setTitle(aspect);
     panel->setTitle(aspect);
     //panel ->setBorder(border);

//            disabledCheck.addActionListener(new ActionListener() {
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    setAspectDisabled(disabledCheck ->isChecked());
//                }
//            });
     connect(disabledCheck, SIGNAL(toggled(bool)),this, SLOT(setAspectDisabled(bool)));

     QSignalMapper* mapper = new QSignalMapper(this);
//            bitCheck1.addActionListener(new ActionListener() {
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    setBit(1, bitCheck1 ->isChecked());
//                }
//            });
     bitCheck1->setProperty("id",1);
     mapper->setMapping(bitCheck1,bitCheck1);
     connect(bitCheck1, SIGNAL(toggled(bool)), mapper, SLOT(map()));
//            bitCheck2.addActionListener(new ActionListener() {
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    setBit(2, bitCheck2 ->isChecked());
//                }
//            });
     bitCheck2->setProperty("id",2);
     mapper->setMapping(bitCheck2,bitCheck2);
     connect(bitCheck2, SIGNAL(toggled(bool)), mapper, SLOT(map()));
//            bitCheck3.addActionListener(new ActionListener() {
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    setBit(3, bitCheck3 ->isChecked());
//                }
//            });
     bitCheck3->setProperty("id",3);
     mapper->setMapping(bitCheck3,bitCheck3);
     connect(bitCheck3, SIGNAL(toggled(bool)), mapper, SLOT(map()));
//            bitCheck4.addActionListener(new ActionListener() {
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    setBit(4, bitCheck4 ->isChecked());
//                }
//            });
     bitCheck4->setProperty("id",4);
     mapper->setMapping(bitCheck4,bitCheck4);
     connect(bitCheck4, SIGNAL(toggled(bool)), mapper, SLOT(map()));
//            bitCheck5.addActionListener(new ActionListener() {
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    setBit(5, bitCheck5 ->isChecked());
//                }
//            });
     bitCheck5->setProperty("id",5);
     mapper->setMapping(bitCheck5,bitCheck5);
     connect(bitCheck5, SIGNAL(toggled(bool)), mapper, SLOT(map()));
//            bitCheck6.addActionListener(new ActionListener() {
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    setBit(6, bitCheck6 ->isChecked());
//                }
//            });
     bitCheck6->setProperty("id",6);
     mapper->setMapping(bitCheck6,bitCheck6);
     connect(bitCheck6, SIGNAL(toggled(bool)), mapper, SLOT(map()));
     connect(mapper, SIGNAL(mapped(QObject*)), this, SLOT(onBitCheck(QObject*)));
     // repeat in order to set MAXMATRIXBITS > 6
 }
 return panel;
}

void MatrixAspectPanel::onBitCheck(QObject *obj)
{
 Q_ASSERT(qobject_cast<QCheckBox*>(obj));
 QCheckBox* box = qobject_cast<QCheckBox*>(obj);
 setBit(box->property("id").toInt(), box->isChecked());
}

//@ServiceProvider(service = SignalMastAddPane.SignalMastAddPaneProvider.class)
//static /*public*/ class SignalMastAddPaneProvider extends SignalMastAddPane.SignalMastAddPaneProvider {
//    /** {@inheritDoc} */
//    @Override
//    @Nonnull /*public*/ String getPaneName() {
//        return tr("MatrixCtlMast");
//    }
//    /** {@inheritDoc} */
//    @Override
//    @Nonnull /*public*/ SignalMastAddPane getNewPane() {
//        return new MatrixSignalMastAddPane();
//    }
//}

/*private*/ /*final*/ /*static*/ Logger* MatrixSignalMastAddPane::log = LoggerFactory::getLogger("MatrixSignalMastAddPane");
