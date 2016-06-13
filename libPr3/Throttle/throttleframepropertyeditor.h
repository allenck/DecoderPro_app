#ifndef THROTTLEFRAMEPROPERTYEDITOR_H
#define THROTTLEFRAMEPROPERTYEDITOR_H
#include "jdialog.h"

class ThrottleWindow;
class JTextField;
class QListWidget;
class QCheckBox;

class ThrottleFramePropertyEditor : public JDialog
{
    Q_OBJECT
public:
    explicit ThrottleFramePropertyEditor(QWidget *parent = 0);
    /*public*/ void setThrottleFrame(ThrottleWindow* f);

signals:

public slots:
private:
    /*private*/ ThrottleWindow* frame;

    /*private*/ JTextField* titleField;

    /*private*/ QListWidget* titleType;

    /*private*/ QCheckBox* borderOff;

    /*private*/ QStringList titleTextTypes;// = {"address", "text", "textAddress", "addressText", "rosterID"};
    /*private*/ QStringList titleTextTypeNames;// = {
//    		Bundle.getMessage("SelectTitleTypeADDRESS"),
//    		Bundle.getMessage("SelectTitleTypeTEXT"),
//    		Bundle.getMessage("SelectTitleTypeTEXTADDRESS"),
//    		Bundle.getMessage("SelectTitleTypeADDRESSTEXT"),
//    		Bundle.getMessage("SelectTitleTypeROSTERID")
    /*private*/ void initGUI();
    /*private*/ bool isDataValid();

private slots:
    void saveProperties();
    /*private*/ void finishEdit();

protected:
protected slots:
    /*protected*/ void titleFieldChanged();

};

#endif // THROTTLEFRAMEPROPERTYEDITOR_H
