#include "editframe.h"
#include "oblock.h"
#include "instancemanager.h"
#include "oblockmanager.h"
#include "borderfactory.h"
#include "placewindow.h"
#include "circuitbuilder.h"
#include <QPushButton>
#include "joptionpane.h"
#include <QScrollArea>

EditFrame::EditFrame()
{

}

/**
 * Abstract class for the editing frames of CircuitBulder
 *
 * @author Pete Cressman Copyright: Copyright (c) 2019
 */
// /*public*/ abstract class EditFrame extends jmri.util.JmriJFrame {


    /*static*/ int EditFrame::STRUT_SIZE = 10;
    /*static*/ QPoint EditFrame::_loc = QPoint(-1, -1);
    /*static*/ QSize EditFrame::_dim =QSize();

    /*public*/ EditFrame::EditFrame(QString title, CircuitBuilder* parent, OBlock* block)
      : JmriJFrame(false, false)
    {
     //super(false, false);
        _parent = parent;
        if (block != nullptr) {
            setTitle(title + " " + block->getDisplayName());//  java.text.MessageFormat.format(title, block.getDisplayName()));
            _homeBlock = block;
        } else {
            setTitle(tr("Add New Detector Circuit"));
            _homeBlock = new OBlock(((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getAutoSystemName(), nullptr);
        }
#if 0
        addWindowListener(new java.awt.event.WindowAdapter() {
            @Override
            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
                closingEvent(true);
            }
        });
#endif
        addHelpMenu("package.jmri.jmrit.display.CircuitBuilder", true);
}
/*public*/ void EditFrame::initContents()
{
        JPanel* contentPane = new JPanel();
        contentPane->setLayout(new QVBoxLayout());//contentPane, BoxLayout.Y_AXIS));
        Border* padding = BorderFactory::createEmptyBorder(10, 5, 4, 5);
        contentPane->setBorder(padding);

        //contentPane->layout()->addWidget(/*new JScrollPane*/(makeContentPanel()));
        QScrollArea* scrollArea = new QScrollArea();
        scrollArea->setWidget(makeContentPanel());
        scrollArea->setWidgetResizable(true);
        contentPane->layout()->addWidget(scrollArea);
        setContentPane(contentPane);

        pack();
        if (_loc.x() < 0) {
//            ((PlaceWindow*)InstanceManager::getDefault("PlaceWindow"))->nextTo(_parent->_editor, (JComponent*)nullptr, this);
        } else {
            setLocation(_loc.x(), _loc.y());
            resize(_dim);
        }
        setVisible(true);
    }

    // /*protected*/ abstract JPanel makeContentPanel();

    /*protected*/ JPanel* EditFrame::makeDoneButtonPanel() {
        JPanel* buttonPanel = new JPanel();
        buttonPanel->setLayout(new QVBoxLayout());//buttonPanel, BoxLayout.Y_AXIS));
        JPanel* panel = new JPanel();
        panel->setLayout(new FlowLayout());

        QPushButton* doneButton = new QPushButton(tr("Done"));
//        doneButton.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent a) {
        connect(doneButton, &QPushButton::clicked, [=]{
                closingEvent(false);
//            }
        });
        panel->layout()->addWidget(doneButton);
        buttonPanel->layout()->addWidget(panel);

        panel = new JPanel();
        panel->setLayout(new FlowLayout());
        panel->layout()->addWidget(buttonPanel);

        return panel;
    }

    /*protected*/ void EditFrame::checkCircuitIcons(QString editType) {
        QString sb;// = new StringBuilder();
        QString msg = _parent->checkForTrackIcons(_homeBlock, editType);
        if (msg.length() > 0) {
            _canEdit = false;
            sb.append(msg);
            sb.append("\n");
        }
        msg = _parent->checkForPortals(_homeBlock, editType);
        if (msg.length() > 0) {
            _canEdit = false;
            sb.append(msg);
            sb.append("\n");
        }
        msg = _parent->checkForPortalIcons(_homeBlock, editType);
        if (msg.length() > 0) {
            _canEdit = false;
            sb.append(msg);
        }
        if (!_canEdit) {
            JOptionPane::showMessageDialog(this, sb,
                    tr("Track Circuit Incomplete"), JOptionPane::INFORMATION_MESSAGE);
        }
    }

    /*protected*/ void EditFrame::clearListSelection() {
    }

    /**
     * Close frame if editing cannot be done
     * @return  whether editing can be done
     */
    /*protected*/ bool EditFrame::canEdit() {
        if (!_canEdit) {
            closingEvent(true, nullptr);
        }
        return _canEdit;
    }

    // /*protected*/ abstract void closingEvent(bool close);

    /*protected*/ bool EditFrame::closingEvent(bool close, QString msg) {
        if (!msg.isNull() && msg.length() > 0) {
            if (close) {
                JOptionPane::showMessageDialog(this, msg, tr("Edit Circuit"), JOptionPane::INFORMATION_MESSAGE);
            } else {
                QString sb;// = new StringBuilder(msg);
                sb.append(tr("\nIgnore message and Exit?"));
                int answer = JOptionPane::showConfirmDialog(this, sb, tr("Continue or Exit?"),
                        JOptionPane::YES_NO_OPTION, JOptionPane::QUESTION_MESSAGE);
                if (answer == JOptionPane::NO_OPTION) {
                    return false;
                }
            }
        }
        storeLocDim(getLocation(/*_loc*/), (_dim));
        _parent->closeCircuitBuilder(_homeBlock);
        dispose();
        return true;
    }

    /*private*/ /*static*/ void EditFrame::storeLocDim(/*@Nonnull*/ QPoint location, /*@Nonnull*/ QSize size) {
        _loc = location;
        _dim = size;
    }
