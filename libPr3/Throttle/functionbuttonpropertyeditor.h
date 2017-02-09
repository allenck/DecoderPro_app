#ifndef FUNCTIONBUTTONPROPERTYEDITOR_H
#define FUNCTIONBUTTONPROPERTYEDITOR_H
#include "jdialog.h"

class EditableResizableImagePanel;
class QCheckBox;
class JTextField;
class FunctionButton;
class FunctionButtonPropertyEditor : public JDialog
{
 Q_OBJECT
public:
 FunctionButtonPropertyEditor(QObject* parent = 0);
 /*public*/ void setFunctionButton(FunctionButton* button);

public slots:
 /*private*/ void saveProperties();
 /*private*/ void finishEdit();

private:
 /*private*/ FunctionButton* button;

 /*private*/ JTextField* textField;
 /*private*/ QCheckBox* lockableCheckBox;
 /*private*/ JTextField* idField;
 /*private*/ JTextField* fontField;
 /*private*/ QCheckBox* visibleCheckBox;
 /*private*/ EditableResizableImagePanel* _imageFilePath;
 /*private*/ EditableResizableImagePanel* _imagePressedFilePath;
 /*final*/ static int BUT_IMG_SIZE;// = 45;
 /*private*/ void initGUI();
 /*private*/ bool isDataValid();

};

#endif // FUNCTIONBUTTONPROPERTYEDITOR_H
