#ifndef VIRTUALSIGNALMASTADDPANE_H
#define VIRTUALSIGNALMASTADDPANE_H
#include "signalmastaddpane.h"
#include "decimalformat.h"

class DecimalFormat;
class VirtualSignalMast;
class QCheckBox;
class VirtualSignalMastAddPane : public SignalMastAddPane
{
 Q_OBJECT
public:
 VirtualSignalMastAddPane(QWidget* parent = nullptr);
 /*@Nonnull*/ /*public*/ QString getPaneName() override;
 /*public*/ void setAspectNames(/*@Nonnull*/
         SignalAppearanceMap* map, SignalSystem* sigSystem) override;
 /*public*/ bool canHandleMast(/*@Nonnull*/ SignalMast* mast) override;
 /*public*/ void setMast(SignalMast* mast) override;
 /*public*/ bool createMast(/*@Nonnull*/
         QString sigsysname, /*@Nonnull*/
                 QString mastname, /*@Nonnull*/
                         QString username) override;

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("VirtualSignalMastAddPane");
 QCheckBox* allowUnLit;// = new JCheckBox();
 QMap<QString, QCheckBox*> disabledAspects;// = new LinkedHashMap<>(NOTIONAL_ASPECT_COUNT);
 QWidget* disabledAspectsPanel;// = new JPanel();

 VirtualSignalMast* currentMast;// = null;
 DecimalFormat* paddedNumber;// = new DecimalFormat("0000");


};

/*static*/ /*public*/ class VirtualSignalMastAddPaneProvider :  public SignalMastAddPaneProvider
{
  Q_OBJECT
  Q_INTERFACES(SignalMastAddPaneProvider)
public:

    /*@Nonnull*/ /*public*/ QString getPaneName()  override;
    /*@Nonnull*/ /*public*/ SignalMastAddPane* getNewPane() override;
};

#endif // VIRTUALSIGNALMASTADDPANE_H
