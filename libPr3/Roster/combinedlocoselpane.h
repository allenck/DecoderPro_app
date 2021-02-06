#ifndef COMBINEDLOCOSELPANE_H
#define COMBINEDLOCOSELPANE_H
#include "locoselpane.h"
#include "identifyloco.h"
#include "identifydecoder.h"
#include "libPr3_global.h"
#include "progmodeselector.h"

class RosterEntry;
class DecoderFile;
class QLabel;
class QPushButton;
class JToggleButton;
class QComboBox;
class GlobalRosterEntryComboBox;
class LIBPR3SHARED_EXPORT CombinedLocoSelPane : public LocoSelPane
{
    Q_OBJECT
public:
    explicit CombinedLocoSelPane(QWidget *parent = 0);
    /*public*/ CombinedLocoSelPane(QLabel* s, ProgModeSelector* selector, QWidget *parent = 0);
    /*public*/ void init();

signals:

public slots:
    void On_decoderBoxIndexChanged(int);
//    void startIdentifyDecoder();
    void On_locoBoxPropertyChange();
    void On_idloco_clicked();
    void On_go2_clicked();
    /*public*/ void propertyChange(PropertyChangeEvent* ev);

private:
    /*private*/ QComboBox* decoderBox;// = null;       // private because children will override this
    /**
     * Reference to an external (not in this pane) JLabel that should
     * be updated with status information as identification happens.
     */
    QLabel* _statusLabel;// = null;
    JToggleButton* addDecoderIdentButton();
    virtual void setDecoderSelectionFromLoco(QString loco);
    virtual bool isDecoderSelected();
   Logger* log;
   virtual void updateForDecoderTypeID(QList<DecoderFile *> pList);
   virtual void updateForDecoderMfgID(QString pMfg, int pMfgID, int pModelID);
   virtual void updateForDecoderNotID(int pMfgID, int pModelID);
   ProgModeSelector* selector;

protected:
   /*protected*/ GlobalRosterEntryComboBox* locoBox ;//= new GlobalRosterEntryComboBox();
   /*protected*/ QComboBox* programmerBox;// = null;
   /*protected*/ JToggleButton* iddecoder;
   /*protected*/ JToggleButton* idloco;
   /*protected*/ QPushButton* go2;
   /*protected*/ virtual QWidget* layoutDecoderSelection();
   /*protected*/ void common();
   /*protected*/  virtual QString selectedDecoderType();
   /*protected*/ virtual QWidget* layoutRosterSelection();
   /*protected*/ virtual QWidget* createProgrammerSelection();
   /*protected*/ void selectLoco(int dccAddress);
   /*protected*/ void selectDecoder(int mfgID, int modelID, int productID);
   /*protected*/ void openButton();
   /*protected*/ void openKnownLoco();
   /*protected*/ void openNewLoco();
   /*protected*/ virtual void startProgrammer(DecoderFile* decoderFile, RosterEntry* r, QString progName);

protected slots:
   /*protected*/ void startIdentifyDecoder();
   /*protected*/ void startIdentifyLoco();

 friend class CombinedLocoSelTreePane;
 friend class CLSIdentifyLoco;
 friend class CLSIdentifyDecoder;
};

class CLSIdentifyLoco : public IdentifyLoco
{
    Q_OBJECT
 /*private*/ CombinedLocoSelPane* who;
public:
 CLSIdentifyLoco(Programmer* programmer, CombinedLocoSelPane* who);
 QObject* self() {return (QObject*)this;}
 protected:
 /*protected*/ void done(int dccAddress);
 /*protected*/ void message(QString m);
 /*protected*/ void error();
};


class CLSIdentifyDecoder : public IdentifyDecoder
{
    Q_OBJECT
    /*private*/ CombinedLocoSelPane* who;
public:
    CLSIdentifyDecoder(Programmer* p, CombinedLocoSelPane* who);
    QObject* self() {return (QObject*)this;}
protected:
    /*protected*/ void done(int mfg, int model, int productID);
    /*protected*/ void message(QString m) ;
    /*protected*/ void error();
};

#endif // COMBINEDLOCOSELPANE_H
