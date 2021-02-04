#ifndef COMBOOFFRADIOBUTTON_H
#define COMBOOFFRADIOBUTTON_H
#include "comboradiobuttons.h"

class LIBPR3SHARED_EXPORT ComboOffRadioButton : public ComboRadioButtons
{
    Q_OBJECT
public:
    //explicit ComboOffRadioButton(QWidget *parent = 0);
    ComboOffRadioButton(QComboBox* box, EnumVariableValue* var, QWidget *parent = 0);
    void addToPanel(QRadioButton* b, int i);

signals:

public slots:

};

#endif // COMBOOFFRADIOBUTTON_H
