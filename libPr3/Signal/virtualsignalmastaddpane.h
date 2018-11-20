#ifndef VIRTUALSIGNALMASTADDPANE_H
#define VIRTUALSIGNALMASTADDPANE_H
#include "signalmastaddpane.h"
#include "decimalformat.h"

class DecimalFormat;
class VirtualSignalMast;
class QCheckBox;
class VirtualSignalMastAddPane : public SignalMastAddPane
{
public:
 VirtualSignalMastAddPane(QWidget* parent = nullptr);
 /*@Nonnull*/ /*public*/ QString getPaneName();
 /*public*/ void setAspectNames(/*@Nonnull*/
         SignalAppearanceMap* map, SignalSystem* sigSystem);
 /*public*/ bool canHandleMast(/*@Nonnull*/ SignalMast* mast);
 /*public*/ void setMast(SignalMast* mast);
 /*public*/ bool createMast(/*@Nonnull*/
         QString sigsysname, /*@Nonnull*/
                 QString mastname, /*@Nonnull*/
                         QString username);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("VirtualSignalMastAddPane");
 QCheckBox* allowUnLit;// = new JCheckBox();
 QMap<QString, QCheckBox*> disabledAspects;// = new LinkedHashMap<>(NOTIONAL_ASPECT_COUNT);
 QWidget* disabledAspectsPanel;// = new JPanel();

 VirtualSignalMast* currentMast;// = null;
 DecimalFormat* paddedNumber;// = new DecimalFormat("0000");


};
/*static*/ /*public*/ class VirtualSignalMastAddPaneProvider : public SignalMastAddPane::SignalMastAddPaneProvider
{
public:

    /*@Nonnull*/ /*public*/ QString getPaneName() ;
    /*@Nonnull*/ /*public*/ SignalMastAddPane* getNewPane();
};

#endif // VIRTUALSIGNALMASTADDPANE_H
