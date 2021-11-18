#include "jtextpane.h"

JTextPane::JTextPane(QWidget *parent) : JEditorPane(parent)
{

}

/*public*/ void JTextPane::setEditable(bool b)
{
 setReadOnly(!b);
}
