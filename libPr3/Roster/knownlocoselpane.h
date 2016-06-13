#ifndef KNOWNLOCOSELPANE_H
#define KNOWNLOCOSELPANE_H
#include "locoselpane.h"
#include "logger.h"
#include "identifyloco.h"

class RosterEntry;
class DecoderFile;
class QVBoxLayout;
class RosterEntrySelectorPanel;
class QLabel;
class QComboBox;
class KnownLocoSelPane : public LocoSelPane
{
    Q_OBJECT
public:
    //explicit KnownLocoSelPane(QWidget *parent = 0);
    /*public*/ KnownLocoSelPane(QLabel* s, bool ident, QWidget *parent = 0);
    /*public*/ KnownLocoSelPane(bool ident, QWidget *parent= 0);

signals:

public slots:
    void On_idLoco();
    void On_go2_clicked();
private:
    bool mCanIdent;

    QComboBox* programmerBox;
    Logger* log;
    /*private*/ void addProgrammerBox();
    QLabel* mStatusLabel;// = NULL;
    /*private*/ void startIdentify();
    /*private*/ RosterEntrySelectorPanel* locoBox;// = NULL;
    QVBoxLayout* thisLayout;
protected:
    /*protected*/ void init();
    /*protected*/ void selectLoco(int dccAddress);
    /*protected*/ void openButton();
    /*protected*/ virtual void startProgrammer(DecoderFile* decoderFile, RosterEntry* r,
                                       QString programmerName);
friend class KLSPIdentifyLoco;
};
class KLSPIdentifyLoco : public IdentifyLoco
{
    Q_OBJECT
    /*private*/ KnownLocoSelPane* who;// = me;
    /*protected*/ void done(int dccAddress);
    /*protected*/ void message(QString m) ;
    KLSPIdentifyLoco(KnownLocoSelPane* who);
    /*public*/ void error();
    friend class KnownLocoSelPane;
};

#endif // KNOWNLOCOSELPANE_H
