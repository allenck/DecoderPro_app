#ifndef MATRIXSIGNALMASTADDPANE_H
#define MATRIXSIGNALMASTADDPANE_H
#include "signalmastaddpane.h"

class JTextField;
class BeanSelectCreatePanel;
class Turnout;
class QVBoxLayout;
class QGroupBox;
class DecimalFormat;
class QLabel;
class QComboBox;
class QScrollArea;
class QCheckBox;
class UserPreferencesManager;
class MatrixSignalMast;
class MatrixAspectPanel;
class DefaultSignalAppearanceMap;
class MatrixSignalMastAddPane : public SignalMastAddPane
{
 Q_OBJECT
public:
 MatrixSignalMastAddPane(QWidget *parent = nullptr);
 /*public*/ static /*final*/ int MAXMATRIXBITS;// = 6; // Don't set above 6
 /*@Nonnull*/ /*public*/ QString getPaneName();
 /*public*/ void setAspectNames(/*@Nonnull*/
         SignalAppearanceMap* newMap, SignalSystem* sigSystem);
 /*public*/ bool canHandleMast(/*@Nonnull*/ SignalMast* mast);
 /*public*/ void setMast(SignalMast* mast);
 /*public*/ void setUnLitBit(int column, bool state);
 /*public*/ bool createMast(/*@Nonnull*/ QString sigsysname, /*@Nonnull*/ QString mastname, /*@Nonnull*/ QString username);

public slots:
 void onColumnChoice();
 //void onMastSelect(QString text);


private:
 static Logger* log;
 QString sigsysname;
 DefaultSignalAppearanceMap* map;

 MatrixSignalMast* currentMast;

 QCheckBox* resetPreviousState;// = new JCheckBox(tr("ResetPrevious"));

 UserPreferencesManager* prefs;// = jmri.InstanceManager.getDefault(jmri.UserPreferencesManager.class);

 QString matrixBitNumSelectionCombo;// = this.getClass().getName() + ".matrixBitNumSelected";

 QCheckBox* allowUnLit;// = new JCheckBox();

 QScrollArea* matrixMastScroll;
 QWidget* matrixMastBitnumPanel;// = new JPanel();
 QWidget* matrixMastPanel;// = new JPanel();
 QByteArray bitString;
 QByteArray unLitPanelBits;
 int numberOfActiveAspects;

 QString emptyChars;// = "000000"; // size of String = MAXMATRIXBITS; add 7th 0 in order to set > 6
 QByteArray emptyBits ;//= emptyChars.toCharArray();
 QLabel* bitNumLabel;// = new JLabel(tr("MakeLabel", tr("MatrixBitsLabel")));
 QComboBox* columnChoice;// = new JComboBox<>(choiceArray());

 QMap<QString, MatrixAspectPanel*> matrixAspect;// = new LinkedHashMap<>(NOTIONAL_ASPECT_COUNT); // LinkedHT type keeps things sorted // only used once, see updateMatrixAspectPanel()

 DecimalFormat* paddedNumber;// = new DecimalFormat("0000");

 QGroupBox* _matrixUnLitPanel;// = new JPanel();
 QVBoxLayout* matrixUnLitPanelLayout;
 QCheckBox* unlitCheck1;// = new JCheckBox();
 QCheckBox* unlitCheck2;// = new JCheckBox();
 QCheckBox* unlitCheck3;// = new JCheckBox();
 QCheckBox* unlitCheck4;// = new JCheckBox();
 QCheckBox* unlitCheck5;// = new JCheckBox();
 QCheckBox* unlitCheck6;// = new JCheckBox();
 // repeat in order to set MAXMATRIXBITS > 6
 QGroupBox* makeMatrixMastBitnumPanel();
 /*private*/ QStringList choiceArray();
 void matrixUnLitPanel();
 void setMatrixReference(BeanSelectCreatePanel* bp, QString functionName);
 /*private*/ bool identicalBits();
 QString stringValueOf(QByteArray);

 /**
  * on = thrown, off = closed, no turnout states asked
  */
 BeanSelectCreatePanel* turnoutBox1;// = new BeanSelectCreatePanel<>(InstanceManager.turnoutManagerInstance(), null);
 BeanSelectCreatePanel* turnoutBox2;// = new BeanSelectCreatePanel<>(InstanceManager.turnoutManagerInstance(), null);
 BeanSelectCreatePanel* turnoutBox3;// = new BeanSelectCreatePanel<>(InstanceManager.turnoutManagerInstance(), null);
 BeanSelectCreatePanel* turnoutBox4;// = new BeanSelectCreatePanel<>(InstanceManager.turnoutManagerInstance(), null);
 BeanSelectCreatePanel* turnoutBox5;// = new BeanSelectCreatePanel<>(InstanceManager.turnoutManagerInstance(), null);
 BeanSelectCreatePanel* turnoutBox6;// = new BeanSelectCreatePanel<>(InstanceManager.turnoutManagerInstance(), null);
 // repeat in order to set MAXMATRIXBITS > 6

 /**
  * The number of columns in logic matrix
  */
 int bitNum;
 void updateMatrixMastPanel();
 QComboBox* copyFromMastSelection();
 void updateMatrixAspectPanel();

private slots:
 void copyFromAnotherMatrixMastAspect(QString strMast);
 void onUnlitCheck(QObject*);
 void bitNumChanged(int newColNum);

protected:
 /*protected*/ QByteArray trimUnLitBits();
 friend class MatrixAspectPanel;
};

//@ServiceProvider(service = SignalMastAddPane.SignalMastAddPaneProvider.class)
/*static*/ /*public*/ class MatrixSignalMastAddPaneProvider : public SignalMastAddPaneProvider {
 Q_OBJECT
public:
    /** {@inheritDoc} */
    //@Override
    /*@Nonnull*/ /*public*/ QString getPaneName() {
        return tr("Output Matrix Mast");
    }
    /** {@inheritDoc} */
    //@Override
    /*@Nonnull*/ /*public*/ SignalMastAddPane* getNewPane() {
        return new MatrixSignalMastAddPane();
    }
};

/**
 * JPanel to define properties of an Aspect for a Matrix Signal Mast.
 * <p>
 * Invoked from the AddSignalMastPanel class when a Matrix Signal Mast is
 * selected.
 *
 * @author Egbert Broerse
 */
class MatrixAspectPanel : public QObject
{

 Q_OBJECT

    QCheckBox* disabledCheck;// = new JCheckBox(tr("DisableAspect"));
    QCheckBox* bitCheck1;// = new JCheckBox();
    QCheckBox* bitCheck2;// = new JCheckBox();
    QCheckBox* bitCheck3;// = new JCheckBox();
    QCheckBox* bitCheck4;// = new JCheckBox();
    QCheckBox* bitCheck5;// = new JCheckBox();
    QCheckBox* bitCheck6;// = new JCheckBox();
    // repeat in order to set MAXMATRIXBITS > 6
    JTextField* aspectBitsField;// = new JTextField(MAXMATRIXBITS); // for debug
    QString aspect = "";
    QString emptyChars;// = "000000"; // size of String = MAXMATRIXBITS; add 0 in order to set > 6
    QByteArray emptyBits;// = emptyChars.toCharArray();
    QByteArray aspectBits;// = emptyBits;
    MatrixSignalMastAddPane* addPane;
    QGroupBox* panel = nullptr;

public:
    /**
     * Build new aspect matrix panel called when Add Signal Mast Pane is
     * built
     *
     * @param aspect String like "Clear"
     */
    MatrixAspectPanel(QString aspect, MatrixSignalMastAddPane* addPane);
    MatrixAspectPanel(QString aspect, QByteArray panelBits, MatrixSignalMastAddPane*
                      addPane) ;
    /*public*/ void setBit(int column, bool state);

private:
    void common();
    void updateAspectBits(QByteArray newBits) ;
    bool isAspectDisabled();
    QByteArray trimAspectBits();
    /*private*/ void setAspectBoxes(QByteArray aspectBits);
    QGroupBox* getPanel();

private slots:
    void setAspectDisabled(bool boo);
    void onBitCheck(QObject* obj);

    friend class MatrixSignalMastAddPane;
};
#endif // MATRIXSIGNALMASTADDPANE_H
