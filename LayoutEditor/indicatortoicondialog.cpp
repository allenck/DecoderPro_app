#include "indicatortoicondialog.h"
#include "loggerfactory.h"
#include "flowlayout.h"
#include "jpanel.h"
#include <QPushButton>
#include "indicatortoitempanel.h"
#include "itempalette.h"
#include "joptionpane.h"

/**
 *
 * @author Pete Cressman Copyright (c) 2010
 */
// /*public*/ class IndicatorTOIconDialog extends IconDialog {


    /*public*/ IndicatorTOIconDialog::IndicatorTOIconDialog(QString type, QString family, IndicatorTOItemPanel* parent, QString key,
            QMap<QString, NamedIcon*>* iconMap)
      : IconDialog(type, key, parent, iconMap) // temporarily use key for family to set JL
    {
        //super(type, key, parent, iconMap); // temporarily use key for family to set JL
        _family = family;
        _key = key;
        log->debug(tr("IndicatorTOIconDialog ctor done. type= \"%1\" family =\"%2\", key= \"%3\"").arg(type).arg(family).arg(key));
    }

    /**
     * Add/Delete icon family for types that may have more than 1 family.
     */
    //@Override
    /*protected*/ void IndicatorTOIconDialog::makeAddIconButtonPanel(JPanel* buttonPanel, QString addTip, QString deleteTip) {
        JPanel* panel1 = new JPanel();
        panel1->setLayout(new FlowLayout());
        QPushButton* addFamilyButton = new QPushButton(tr("Add Missing Status"));
//        addFamilyButton.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent a) {
        connect(addFamilyButton, &QPushButton::clicked, [=]{
                addFamilySet();
                dispose();
//            }
        });
        addFamilyButton->setToolTip(tr("Add back a previously deleted Track Status"));
        panel1->layout()->addWidget(addFamilyButton);

        QPushButton* deleteButton = new QPushButton(tr("Delete Status"));
//        deleteButton.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent a) {
        connect(deleteButton, &QPushButton::clicked, [=]{
                deleteFamilySet();
                dispose();
//            }
        });
        deleteButton->setToolTip(tr("Delete a Track Status you are not going to use"));
        panel1->layout()->addWidget(deleteButton);
        buttonPanel->layout()->addWidget(panel1);
    }

    /**
     * Action item for add new status set in makeAddIconButtonPanel.
     */
    /*private*/ void IndicatorTOIconDialog::addFamilySet() {
        log->debug(tr("addFamilySet: type= \"%1\", family= \"%2\" key= %3").arg(
                _type).arg(_family).arg(_key));
        setVisible(false);
        IndicatorTOItemPanel* parent = (IndicatorTOItemPanel*) _parent;
        if (parent->_iconGroupsMap->size() < IndicatorTOItemPanel::STATUS_KEYS.length()) {
            QSet<QString> keys = ItemPalette::getLevel4Family(_type, _family)->keys().toSet();
            QList<QString> options = QList<QString>();
            for (int i = 0; i < IndicatorTOItemPanel::STATUS_KEYS.length(); i++) {
                if (!keys.contains(IndicatorTOItemPanel::STATUS_KEYS[i])) {
                    options.append(IndicatorTOItemPanel::STATUS_KEYS[i]);
                }
            }
            QVariantList selections;// = options.toArray();
            foreach(QString s, options)
             selections.append(s);
            QString key =  JOptionPane::showInputDialog(_parent->_paletteFrame,
                    tr("The following status icons are missing. Choose what you want to add."), tr("Question"), JOptionPane::QUESTION_MESSAGE, QIcon(),
                    selections, selections[0]).toString();
            if (key != nullptr) {
                _key = key;
                createNewStatusSet();
//                new IndicatorTOIconDialog(_type, null, parent, _key, _iconMap);
            }
        } else {
            JOptionPane::showMessageDialog(_parent->_paletteFrame,
                    tr("The icon set includes all possible Track Status"),
                    tr("Message"), JOptionPane::INFORMATION_MESSAGE);
        }
    }

    /**
     * NOT add a new family. Create a status family when previous status was
     * deleted.
     */
    /*private*/ void IndicatorTOIconDialog::createNewStatusSet() {
        if (log->isDebugEnabled()) {
            log->debug(tr("createNewFamily: type= \"%1\", family \"%2\" key = \"%3\"").arg(
                    _type).arg(_family).arg(_key));
        }
        //check text
        QMap<QString, NamedIcon*>* iconMap = ItemPanel::makeNewIconMap("Turnout");
        ItemPalette::addLevel4FamilyMap(_type, _parent->_family, _key, iconMap);
        addFamilySet(_parent->_family, iconMap, _key);
        dispose();
    }

    /**
     * Action item for add delete status set in makeAddIconButtonPanel.
     */
    /*private*/ void IndicatorTOIconDialog::deleteFamilySet() {
        ItemPalette::removeLevel4IconMap(_type, _parent->_family, _key);
        _family = nullptr;
        _parent->updateFamiliesPanel();
    }

    /**
     * Action item for makeDoneButtonPanel.
     */
    //@Override
    /*protected*/ bool IndicatorTOIconDialog::doDoneAction() {
        //check text
        QString subFamily = _key;  // actually the key to status icon
        if (_family != "" && _family == (subFamily)) {
            ItemPalette::removeLevel4IconMap(_type, _parent->_family, subFamily);
        }
        return addFamilySet(_parent->_family, _iconMap, subFamily);
    }

    /*private*/ bool IndicatorTOIconDialog::addFamilySet(QString family, QMap<QString, NamedIcon*>* iconMap, QString subFamily) {
        if (log->isDebugEnabled()) {
            log->debug(tr("addFamilySet _type= \"%1\", family= \"%2\", key=\"%3\", _iconMap.size= %4").arg(
                    _type).arg(family).arg(_key).arg(iconMap->size()));
        }
        IndicatorTOItemPanel* parent = (IndicatorTOItemPanel*) _parent;
        parent->updateIconGroupsMap(subFamily, iconMap);
        parent->updateFamiliesPanel();
        parent->_family = family;
        return true;
    }

    /*private*/ /*final*/ /*static*/ Logger* IndicatorTOIconDialog::log = LoggerFactory::getLogger("IndicatorTOIconDialog");
