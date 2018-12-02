#ifndef TURNOUTSIGNALMASTADDPANE_H
#define TURNOUTSIGNALMASTADDPANE_H
#include "signalmastaddpane.h"
#include "decimalformat.h"

class QGroupBox;
class QComboBox;
class QLabel;
class BeanSelectCreatePanel;
class Turnout;
class TurnoutSignalMast;
class TurnoutAspectPanel;
class QCheckBox;
class QScrollArea;
class TurnoutSignalMastAddPane : public SignalMastAddPane
{
public:
 TurnoutSignalMastAddPane(QWidget *parent = nullptr);
 /*@Nonnull*/ /*public*/ QString getPaneName();
 /*public*/ void setAspectNames(/*@Nonnull*/
         SignalAppearanceMap* map, SignalSystem* sigSystem);
 /*public*/ bool canHandleMast(/*@Nonnull*/ SignalMast* mast);
 /*public*/ void setMast(SignalMast* mast);
 /*public*/ bool createMast(/*@Nonnull*/ QString sigsysname, /*@Nonnull */QString mastname, /*@Nonnull*/ QString username);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("TurnoutSignalMastAddPane");
 QWidget* turnoutMastPanel;// = new JPanel();
 QScrollArea* turnoutMastScroll;
 QCheckBox* resetPreviousState;// = new JCheckBox(Bundle.getMessage("ResetPrevious"));

 QCheckBox* allowUnLit;// = new JCheckBox();
 QMap<QString, TurnoutAspectPanel*> turnoutAspect;// = new LinkedHashMap<>(NOTIONAL_ASPECT_COUNT); // only used once, see updateTurnoutAspectPanel()
 QWidget* disabledAspectsPanel;// = new JPanel();

 TurnoutSignalMast* currentMast;// = null;

 QString stateThrown;// = InstanceManager.turnoutManagerInstance().getThrownText();
 QString stateClosed;// = InstanceManager.turnoutManagerInstance().getClosedText();
 QStringList turnoutStates;// = new String[]{stateClosed, stateThrown};
 QList<int> turnoutStateValues;// = new int[]{Turnout.CLOSED, Turnout.THROWN};
 BeanSelectCreatePanel* turnoutUnLitBox;// = new BeanSelectCreatePanel<>(InstanceManager.turnoutManagerInstance(), null);
 QComboBox* turnoutUnLitState;// = new JComboBox<>(turnoutStates);
 DecimalFormat* paddedNumber;// = new DecimalFormat("0000");

 friend class TurnoutAspectPanel;
};

/**
 * JPanel to define properties of an Aspect for a Turnout Signal Mast.
 * <p>
 * Invoked from the AddSignalMastPanel class when a Turnout Signal Mast is
 * selected.
 */
class TurnoutAspectPanel : public QObject
{
Q_OBJECT

    BeanSelectCreatePanel* beanBox;// = new BeanSelectCreatePanel<>(InstanceManager.turnoutManagerInstance(), null);
    QCheckBox* disabledCheck;// = new JCheckBox(Bundle.getMessage("DisableAspect"));
    QLabel* turnoutStateLabel;// = new JLabel(Bundle.getMessage("SetState"));
    QComboBox* turnoutState;// = new JComboBox<>(turnoutStates);

    QString aspect;// = "";
    void common();
    TurnoutSignalMastAddPane* pane;
public:
    TurnoutAspectPanel(QString aspect, TurnoutSignalMastAddPane* pane);
    TurnoutAspectPanel(QString turnoutName, int, TurnoutSignalMastAddPane* pane);

private:
    void setReference(QString reference);
    int getTurnoutState();
    void setSelectedTurnout(QString name);
    void setTurnoutState(int state);
    bool isAspectDisabled();
    QString getTurnoutName();
    NamedBean* getTurnout();
    QGroupBox* panel = nullptr;
    QGroupBox* getPanel();
private slots:
    void setAspectDisabled(bool boo);
friend class TurnoutSignalMastAddPane;
};

/*static*/ /*public*/ class TurnoutSignalMastAddPaneProvider : public SignalMastAddPane::SignalMastAddPaneProvider
{
 Q_OBJECT
public:
    /*@Nonnull*/ /*public*/ QString getPaneName();
    /*@Nonnull*/ /*public*/ SignalMastAddPane* getNewPane();
};

#endif // TURNOUTSIGNALMASTADDPANE_H
