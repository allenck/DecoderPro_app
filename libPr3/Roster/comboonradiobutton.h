#ifndef COMBOONRADIOBUTTON_H
#define COMBOONRADIOBUTTON_H
#include "comboradiobuttons.h"

class LIBPR3SHARED_EXPORT ComboOnRadioButton : public ComboRadioButtons
{
    Q_OBJECT
public:
    //explicit ComboOnRadioButton(QWidget *parent = 0);
    ComboOnRadioButton(QComboBox* box, EnumVariableValue* var, QWidget *parent = 0);
    void addToPanel(QRadioButton* b, int i);

signals:

public slots:

};

#endif // COMBOONRADIOBUTTON_H
