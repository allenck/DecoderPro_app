#ifndef SIGNALHEADSIGNALMASTADDPANE_H
#define SIGNALHEADSIGNALMASTADDPANE_H
#include "signalmastaddpane.h"

class DefaultSignalAppearanceMap;
class SignalHeadSignalMast;
class JmriBeanComboBox;
class QCheckBox;
class QGroupBox;
class SignalHeadSignalMastAddPane : public SignalMastAddPane
{
 Q_OBJECT
public:
 SignalHeadSignalMastAddPane(QWidget* parent = nullptr);
 /*@Nonnull*/ /*public*/ QString getPaneName();
 /*public*/ void setAspectNames(/*@Nonnull*/
         SignalAppearanceMap* newMap, SignalSystem* sigSystem);
 /*public*/ bool canHandleMast(/*@Nonnull*/ SignalMast* mast);
 /*public*/ void setMast(SignalMast* mast);
 /*public*/ bool createMast(/*@Nonnull*/ QString sigsysname, /*@Nonnull*/ QString mastname, /*@Nonnull*/ QString username);

public slots:

private:
 static Logger* log;
 QGroupBox* signalHeadPanel;// = new JPanel();
     QList<JmriBeanComboBox*> headList;// = new ArrayList<>(5);
     QCheckBox* includeUsed;// = new JCheckBox(Bundle.getMessage("IncludeUsedHeads"));

     QCheckBox* allowUnLit;// = new JCheckBox();

     QMap<QString, QCheckBox*> disabledAspects;// = new LinkedHashMap<>(NOTIONAL_ASPECT_COUNT);
     QWidget* disabledAspectsPanel;// = new JPanel();

     SignalHeadSignalMast* currentMast = nullptr;
     QList<NamedBean*> alreadyUsed;// = new ArrayList<>();
     DefaultSignalAppearanceMap* map;
     void handleCreateException(QString sysName);

protected slots:
     /*protected*/ void refreshHeadComboBox();

};

//@ServiceProvider(service = SignalMastAddPane.SignalMastAddPaneProvider.class)
/*static*/ /*public*/ class SignalHeadSignalHeadSignalMastAddPaneProvider : public SignalMastAddPane::SignalMastAddPaneProvider {
    /** {@inheritDoc} */
    //@Override
    /*@Nonnull*/ /*public*/ QString getPaneName() {
        return tr("Signal Head Controlled Mast");
    }
    /** {@inheritDoc} */
    //@Override
    /*@Nonnull*/ /*public*/ SignalMastAddPane* getNewPane() {
        return new SignalHeadSignalMastAddPane();
    }
 friend class SignalMastAddPane::SignalMastAddPaneProvider;
};

#endif // SIGNALHEADSIGNALMASTADDPANE_H
