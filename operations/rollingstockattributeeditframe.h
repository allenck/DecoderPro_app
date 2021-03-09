#ifndef ROLLINGSTOCKATTRIBUTEEDITFRAME_H
#define ROLLINGSTOCKATTRIBUTEEDITFRAME_H
#include "operationsframe.h"
#include "jlabel.h"
#include "jcombobox.h"
#include "jtextfield.h"
#include "control.h"
#include <QPushButton>

namespace Operations
{
    class RollingStockAttributeEditFrame : public OperationsFrame, public PropertyChangeListener
    {
      Q_OBJECT
      Q_INTERFACES(PropertyChangeListener)
    public:
        RollingStockAttributeEditFrame(QObject* parent = 0);
        // labels
        /*public*/ JLabel* textAttribute = new JLabel();
        JLabel* textSep = new JLabel();
        /*public*/ JLabel* quanity = new JLabel("0");

        // major buttons
        /*public*/ QPushButton* addButton = new QPushButton(tr("Add"));
        /*public*/ QPushButton* deleteButton = new QPushButton(tr("Delete"));
        /*public*/ QPushButton* replaceButton = new QPushButton(tr("Replace"));

        // combo box
        /*public*/ JComboBox/*<String>*/* comboBox;

        // text box
        /*public*/ JTextField* addTextBox = new JTextField(Control::max_len_string_attibute);
        // ROAD and OWNER are the only two attributes shared between Cars and Engines
        /*public*/ static /*final*/ QString ROAD;// = tr("Road");
        /*public*/ static /*final*/ QString OWNER;// = tr("Owner");
        // only here for name checking
        /*public*/ static /*final*/ QString TYPE;// = tr("Type");
        /*public*/ bool showQuanity = false;
        /*public*/ static /*final*/ QString DISPOSE;// = "dispose"; // NOI18N
        /*public*/ QString _attribute; // used to determine which attribute is being edited
        /*public*/ virtual void initComponents(QString attribute, QString name);
        /*public*/ void buttonActionPerformed(QWidget* ae) override;
        /*public*/ static /*final*/ QString FAILED;// = "failed";
        /*public*/ QString convertLength(QString addItem);
        /*public*/ void dispose() override;

     public slots:
        /*public*/ virtual void propertyChange(PropertyChangeEvent* e)override;

    private:
        static Logger* log;

     protected:
        /*protected*/ static bool showDialogBox;// = true;
        /*protected*/ virtual bool checkItemName(QString itemName, QString errorMessage);
        /*protected*/ virtual void deleteAttributeName(QString deleteItem);
        /*protected*/ virtual void addAttributeName(QString addItem);
        /*protected*/ virtual void replaceItem(QString oldItem, QString newItem) ;
        /*protected*/ virtual void loadCombobox();

    };
}
#endif // ROLLINGSTOCKATTRIBUTEEDITFRAME_H
