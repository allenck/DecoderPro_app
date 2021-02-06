#ifndef DECVARIABLEVALUE_H
#define DECVARIABLEVALUE_H
#include "variablevalue.h"
#include "cvvalue.h"
#include <QList>
#include "actionevent.h"
#include "jtextfield.h"

class DecVarSlider;
class LIBPR3SHARED_EXPORT DecVariableValue : public VariableValue
{
    Q_OBJECT
public:
    //explicit DecVariableValue(QObject *parent = 0);
    /*public*/ DecVariableValue(QString name, QString comment, QString cvName,
                            bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
                            QString cvNum, QString mask, int minVal, int maxVal,
                            QMap<QString, CvValue*>* v, JLabel *status, QString stdname, QObject *parent = 0);
    /*public*/ void setToolTipText(QString t);
    /*public*/ QVector<CvValue*> usesCVs() override;
    /*public*/ QVariant rangeVal() override;
    void updatedTextField();
    /*public*/ QString getValueString() override;
    // to complete this class, fill in the routines to handle "Value" parameter
    // and to read/write/hear parameter changes.
    /*public*/ void setIntValue(int i) override;
    /*public*/ int getIntValue() override;
    /*public*/ QVariant getValueObject() override;
    /*public*/ QWidget* getCommonRep() override;
    /*public*/ void setAvailable(bool a);
    /*public*/ QWidget* getNewRep(QString format) override;
    /*public*/ void setValue(int value);
    /*public*/ void setCvState(int state) override;
    /*public*/ bool isChanged() override;
    /*public*/ void readChanges() override;
    /*public*/ void writeChanges() override;
    /*public*/ void readAll() override;
    /*public*/ void writeAll() override;
    /*public*/ void dispose() override;

signals:

public slots:
    void value_changed();
    /*public*/ void propertyChange(PropertyChangeEvent* e) override;
    /*public*/ void actionPerformed();
    /*public*/ void focusGained(/*FocusEvent*/QEvent* e = 0);
    /*public*/ void focusLost(/*FocusEvent*/QEvent* e = 0);

private:
    int _maxVal;
    int _minVal;
    QString oldContents;// = "";
    QList<QWidget*>* reps;// = new QList<QWidget*>();
    QList<DecVarSlider*>* sliders;// = new QList<DecVarSlider>();
    QColor _defaultColor;
    QColor currColor;
    QColor getDefaultColor();
    QColor getColor();
    void setColor(QColor c);
    // stored value, read-only Value
    JTextField* _value;// = NULL;
    Logger* log;
    void enterField();
    void exitField();
    int fieldLength();

 friend class HexVariableValue;
 friend class DecVarSlider;
 friend class DecVarTextField;
};

/*public*/ class DecVarTextField : public JTextField {
Q_OBJECT
  DecVariableValue* _var;
 public:
    DecVarTextField(Document* doc, QString text, int col, DecVariableValue* var);

 public slots:
    void thisActionPerformed(/*java.awt.event.ActionEvent e*/);
    void originalPropertyChanged(PropertyChangeEvent* e);
};
#endif // DECVARIABLEVALUE_H
