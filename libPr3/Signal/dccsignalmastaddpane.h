#ifndef DCCSIGNALMASTADDPANE_H
#define DCCSIGNALMASTADDPANE_H
#include "signalmastaddpane.h"

class QVBoxLayout;
class CommandStation;
class DccSignalMast;
class DCCAspectPanel;
class QCheckBox;
class JTextField;
class QComboBox;
class QLabel;
class QGroupBox;
class QScrollArea;
class DccSignalMastAddPane : public SignalMastAddPane
{
 Q_OBJECT
public:
 DccSignalMastAddPane(QWidget* parent = nullptr);
 /*@Nonnull*/ /*public*/ QString getPaneName();
 /*public*/ void setAspectNames(/*@Nonnull*/ SignalAppearanceMap* map,
                            /*@Nonnull*/ SignalSystem* sigSystem);
 /*public*/ bool canHandleMast(/*@Nonnull*/ SignalMast* mast);
 /*public*/ void setMast(SignalMast* mast);
 /*public*/ bool createMast(/*@Nonnull*/
         QString sigsysname, /*@Nonnull*/
                 QString mastname, /*@Nonnull*/
                         QString username);


private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("DccSignalMastAddPane");
 QScrollArea* dccMastScroll;
 QGroupBox* dccMastPanel;// = new JPanel();
 QLabel* systemPrefixBoxLabel;// = new JLabel(Bundle.getMessage("MakeLabel", Bundle.getMessage("DCCSystem")));
 QComboBox* systemPrefixBox;// = new JComboBox<>();
 QLabel* dccAspectAddressLabel;// = new JLabel(Bundle.getMessage("MakeLabel", Bundle.getMessage("DCCMastAddress")));
 JTextField* dccAspectAddressField;// = new JTextField(5);

 QCheckBox* allowUnLit;// = new JCheckBox();
 JTextField* unLitAspectField;// = new JTextField(5);

 QMap<QString, DCCAspectPanel*> dccAspect;// = new LinkedHashMap<>(NOTIONAL_ASPECT_COUNT);

 DccSignalMast* currentMast = nullptr;
 SignalSystem* sigsys;
 QVBoxLayout* dccMastPanelLayout;
 static bool validateAspectId(/*@Nonnull*/ QString strAspect);
 /*private*/ bool validateDCCAddress();
 /*@Nonnull*/ QComboBox* copyFromMastSelection();
 void copyFromAnotherDCCMastAspect(/*@Nonnull*/ QString strMast);

private slots:
 void onMastSelect(QObject*);

protected:
 /*protected*/ bool usableCommandStation(CommandStation* cs);
 /*protected*/ /*@Nonnull*/ QString getNamePrefix();
 /*protected*/ DccSignalMast* constructMast(/*@Nonnull*/ QString name);

};

/*static*/ class DCCAspectPanel : public QObject
{
 Q_OBJECT
    QString aspect = "";
    QCheckBox* disabledCheck;// = new JCheckBox(Bundle.getMessage("DisableAspect"));
    QLabel* aspectLabel;// = new JLabel(Bundle.getMessage("DCCMastSetAspectId") + ":");
    JTextField* aspectId;// = new JTextField(5);
public:
    DCCAspectPanel(QString aspect);

public slots:
    void onDisabledCheck();
private:
    void setAspectDisabled(bool boo);
    bool isAspectDisabled();
    int getAspectId();
    void setAspectId(int i);
    void setAspectId(QString s);
    QGroupBox* panel = nullptr;

    QWidget* getPanel();
    friend class DccSignalMastAddPane;
};
//@ServiceProvider(service = SignalMastAddPane.SignalMastAddPaneProvider.class)
/*static*/ /*public*/ class DccSignalMastAddPaneProvider : public SignalMastAddPaneProvider
{
  Q_OBJECT
  Q_INTERFACES(SignalMastAddPaneProvider)
public:
  DccSignalMastAddPaneProvider() {}
    /** {@inheritDoc} */
    //@Override
    /*@Nonnull*/ /*public*/ QString getPaneName() {
        return tr("DCC Mast");
    }
    /** {@inheritDoc} */
    //@Override
    /*@Nonnull*/ /*public*/ SignalMastAddPane* getNewPane() {
        return new DccSignalMastAddPane();
    }
};

#endif // DCCSIGNALMASTADDPANE_H
