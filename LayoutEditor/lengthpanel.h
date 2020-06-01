#ifndef LENGTHPANEL_H
#define LENGTHPANEL_H
#include "jpanel.h"

class OBlock;
class JTextField;
class JToggleButton;
class LengthPanel : public JPanel
{
 Q_OBJECT
public:
 LengthPanel(OBlock* block, QString label, QObject* parent = nullptr);

private:
 /*private*/ OBlock* _block;
 /*private*/ float _length;
 /*private*/ JTextField* _lengthField;
 /*private*/ JToggleButton* _units;

protected:
 /*protected*/ void changeUnits();
 /*protected*/ void setLength(float len);
 /*protected*/ float getLength();
 /*protected*/ bool isChanged(float len);

 friend class EditCircuitFrame;
 friend class EditCircuitPaths;
 friend class EditSignalFrame;
};

#endif // LENGTHPANEL_H
