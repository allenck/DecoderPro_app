#ifndef DCCLOCOADDRESSSELECTOR_H
#define DCCLOCOADDRESSSELECTOR_H

#include <QWidget>
#include <QComboBox>
#include "jtextfield.h"
#include "logger.h"
#include "libPr3_global.h"

class DccLocoAddress;
class LIBPR3SHARED_EXPORT DccLocoAddressSelector : public QWidget
{
    Q_OBJECT
public:
    explicit /*public*/ DccLocoAddressSelector( QWidget *parent = 0);
    DccLocoAddressSelector(QComboBox* box, JTextField* text, QWidget *parent = 0);
    /*public*/ DccLocoAddressSelector(QStringList protocols, QWidget* parent = 0);
    /*public*/ void setLocked(bool l);
    /*public*/ bool getLocked(bool l);
    /*public*/ DccLocoAddress* getAddress();
    /*public*/ void setAddress(DccLocoAddress* a);
//    /*public*/ void setVariableSize(bool s) ;
//    /*public*/ void reset() {
    /*public*/ void setEnabled(bool e);
    /*public*/ void setEnabledProtocol(bool e);
    /*public*/ void setVariableSize(bool s);
    /*public*/ void reset();
    /*public*/ QWidget* getCombinedJPanel();
    /*public*/ JTextField* getTextField();
    /*public*/ QComboBox* getSelector();

signals:

public slots:
private:
    QComboBox* box;// = NULL;
    JTextField* text;// = new JTextField();
    void configureBox(QStringList protocols);
    /*private*/ bool locked;// = true;

    /*private*/ bool boxUsed;// = false;
    /*private*/ bool textUsed;// = false;
    /*private*/ bool panelUsed;// = false;
    void init();
    bool varFontSize;// = false;
    Logger* log;
    /*private*/ static /*final*/ QString LONGEST_STRING;// = "MMMM";
    /*private*/ void changeFontSizes();
    void reportError(QString msg);

};

#endif // DCCLOCOADDRESSSELECTOR_H
