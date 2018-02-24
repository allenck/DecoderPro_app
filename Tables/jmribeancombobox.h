#ifndef JMRIBEANCOMBOBOX_H
#define JMRIBEANCOMBOBOX_H

#include <QComboBox>
#include "logger.h"
#include "libtables_global.h"

class Manager;
class NamedBean;
class PropertyChangeEvent;
class LIBTABLESSHARED_EXPORT JmriBeanComboBox : public QComboBox
{
    Q_OBJECT
public:
    //explicit JmriBeanComboBox(QObject *parent = 0);
    /*public*/ JmriBeanComboBox(Manager* manager, QWidget *parent = 0);
    /*public*/ JmriBeanComboBox(Manager* manager, NamedBean* nBean, int displayOrder, QWidget *parent = 0);
    /*public*/ void refreshCombo();
    void updateComboBox(QString select);
    /*public*/ QString getSelectedUserName();
    /*public*/ QString getSelectedSystemName();
    /*public*/ QString getSelectedDisplayName();
    /*public*/ void setFirstItemBlank(bool blank);
    /*public*/ NamedBean* getSelectedBean();
    /*public*/ void setSelectedBean(NamedBean* nBean);
    /*public*/ void excludeItems(QList<NamedBean*>* exclude);
#if 0
    /**
    * constant used to format the entries in the combo box using the displayname
    */
    /*public*/ /*final*/ const static int DISPLAYNAME = 0x00;
    /**
    * Constant used to format the entries in the combo box using the username
    * if the username value is blank for a bean then the system name is used
    */
    /*public*/ /*final*/ const static int USERNAME = 0x01;

    /**
    * constant used to format the entries in the combo box using the systemname
    */
    /*public*/ /*final*/ const static int SYSTEMNAME = 0x02;

    /**
    * constant used to format the entries in the combo box with the username
    * followed by the systemname
    */
    /*public*/ /*final*/ const static int USERNAMESYSTEMNAME = 0x03;

    /**
    * constant used to format the entries in the combo box with the systemname
    * followed by the userame
    */
    /*public*/ /*final*/ const static int SYSTEMNAMEUSERNAME = 0x04;
#endif
    /*public*/ void dispose();
//    /*public*/ /*interface*/ class KeySelectionManager {
//            /** Given <code>aKey</code> and the model, returns the row
//             *  that should become selected. Return -1 if no match was
//             *  found.
//             *
//             * @param  aKey  a char value, usually indicating a keyboard key that
//             *               was pressed
//             * @param aModel a ComboBoxModel -- the component's data model, containing
//             *               the list of selectable items
//             * @return an int equal to the selected row, where 0 is the
//             *         first item and -1 is none.
//             */
//            virtual int selectionForKey(char aKey, /*ComboBoxModel*/QComboBox* aModel) = 0;
//        };
//    /*static*/ class beanSelectionManager : public KeySelectionManager {
//    public:
//        beanSelectionManager()
//        {
//        lastKeyTime = 0;
//        pattern = "";
//        }
//        long lastKeyTime ;
//        QString pattern;
//        /*public*/ int selectionForKey(char aKey, /*ComboBoxModel*/QComboBox* model) {
//            // Find index of selected item
//            int selIx = 01;
//            QString sel = model->currentText();
//            if (sel != "") {
//                for (int i=0; i<model->count(); i++) {
//                    if (sel==(model->itemText(i))) {
//                        selIx = i;
//                        break;
//                    }
//                }
//            }

//            // Get the current time
//            long curTime = System.currentTimeMillis();

//            // If last key was typed less than 300 ms ago, append to current pattern
//            if (curTime - lastKeyTime < 300) {
//                pattern += ("" + aKey).toLowerCase();
//            } else {
//                pattern = ("" + aKey).toLowerCase();
//            }

//            // Save current time
//            lastKeyTime = curTime;

//            // Search forward from current selection
//            for (int i=selIx+1; i<model.getSize(); i++) {
//                QString s = model.getElementAt(i).toString().toLowerCase();
//                if (s.startsWith(pattern)) {
//                    return i;
//                }
//            }

//            // Search from top to current selection
//            for (int i=0; i<selIx ; i++) {
//                if (model.getElementAt(i) != NULL) {
//                    QString s = model.getElementAt(i).toString().toLowerCase();
//                    if (s.startsWith(pattern)) {
//                        return i;
//                    }
//                }
//            }
//            return -1;
//        }
//    };
    /*public*/ void setSelectedBeanByName(QString inBeanName);
    /*public*/ enum DisplayOptions {
           /**
            * Format the entries in the combo box using the display name.
            */
           DISPLAYNAME = 1,
           /**
            * Format the entries in the combo box using the username. If the
            * username value is blank for a bean then the system name is used.
            */
           USERNAME = 2,
           /**
            * Format the entries in the combo box using the system name.
            */
           SYSTEMNAME = 3,
           /**
            * Format the entries in the combo box with the username followed by the
            * system name.
            */
           USERNAMESYSTEMNAME =4,
           /**
            * Format the entries in the combo box with the system name followed by
            * the username.
            */
           SYSTEMNAMEUSERNAME = 5
    };

signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);

private:

    QString _lastSelected;// = "";
    int _displayOrder;
    bool _firstBlank;// = false;

    Manager* _manager;

    QHash<QString, NamedBean*>* displayToBean;// = new QHash<QString, NamedBean*>();
    QList<NamedBean*>* exclude;// = new QList<NamedBean*>();
    Logger* log;

};

#endif // JMRIBEANCOMBOBOX_H
