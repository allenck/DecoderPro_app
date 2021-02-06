#ifndef ABSTRACTVALUE_H
#define ABSTRACTVALUE_H

#include <QObject>
#include "propertychangesupport.h"
#include <QColor>
#include <QString>
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT AbstractValue : public QObject
{
    Q_OBJECT
public:
    explicit AbstractValue(QObject *parent = 0);
    /*abstract*/ virtual void setColor(QColor c) {Q_UNUSED(c)}

    /** Defines state when nothing is known about the real value */
    /*public*/ static /*final*/ const int UNKNOWN  =   0;

    /** Defines state where value has been edited, no longer same as in decoder or file */
    /*public*/ static /*final*/ const int EDITED  =   4;

    /** Defines state where value has been read from (hence same as) decoder, but perhaps
        not same as in file */
    /*public*/ static /*final*/ const int READ     =  16;

    /** Defines state where value has been written to (hence same as) decoder, but perhaps
        not same as in file */
    /*public*/ static /*final*/ const int STORED   =  64;

    /** Defines state where value was read from a config file, but might not be
        the same as the decoder */
    /*public*/ static /*final*/ const int FROMFILE = 256;

    /** Defines state where value was read from a config file, and is
    the same as the decoder */
    /*public*/ static /*final*/ const int SAME = 512;

    /** Defines state where value was read from a config file, and is
    the not the same as the decoder */
    /*public*/ static /*final*/ const int DIFF = 1024;

    /** Define color to denote UNKNOWN state.  null means to use default for the component */
    static /*final*/ QColor COLOR_UNKNOWN;//  = QColor(Qt::red);

    /** Define color to denote EDITED state.  null means to use default for the component */
    static /*final*/ QColor COLOR_EDITED;//  = QColor(255,170,0);

    /** Define color to denote READ state.  null means to use default for the component */
    static /*final*/ QColor COLOR_READ;//     = null;

    /** Define color to denote STORED state.  null means to use default for the component */
    static /*final*/ QColor COLOR_STORED;//   = null;

    /** Define color to denote FROMFILE state.  null means to use default for the component */
    static /*final*/ QColor COLOR_FROMFILE;// = Color.yellow;

    /** Define color to denote SAME state.  null means to use default for the component */
    static /*final*/ QColor COLOR_SAME;//     = null;

    /** Define color to denote DIFF state.  null means to use default for the component */
    static /*final*/ QColor COLOR_DIFF;// = Color.red.brighter();

    /*public*/ virtual void setToRead(bool state);
    /*public*/ virtual bool isToRead();
    /*public*/ virtual void setToWrite(bool state);
    /*public*/ virtual bool isToWrite();

    /*public*/ static QString stateNameFromValue(int val);
    /*public*/ void setAvailable(bool available);
    /*public*/ bool getAvailable();

    /*public*/ void addPropertyChangeListener(PropertyChangeListener* p);
    /*public*/ void removePropertyChangeListener(PropertyChangeListener* p);
signals:

public slots:
private:
    PropertyChangeSupport* prop;// = new PropertyChangeSupport(this);
    /*private*/ bool _toWrite = false;
    /*private*/ bool available = true;
    /*private*/ bool _toRead = false;
 friend class CvValue;
 friend class VariableValue;
 friend class EnumVariableValue;
 friend class CompositeVariableValue;
 friend class DecVariableValue;
 friend class HexVariableValue;
 friend class LongAddrVariableValue;
 friend class SpeedTableVarValue;
 friend class SplitVariableValue;
 friend class ConstantValue;
 friend class PaneProgPane;
 friend class ResetTableModel;
 friend class DccAddressPanel;
 friend class VariableTableModel;
 friend class AbstractQualifier;
 friend class IVarComboBox;
 friend class ComboRadioButtons;
 friend class IndexedVarSlider;
 friend class VarTextField;
 friend class DecVarSlider;
 friend class PaneProgFrame;
 friend class PaneProgDp3Action;
 friend class DecVarTextField;
 friend class LAVarTextField;
 friend class SPVarTextField;
};

#endif // ABSTRACTVALUE_H
