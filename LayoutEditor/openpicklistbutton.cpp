#include "openpicklistbutton.h"
#include "borderfactory.h"
#include "box.h"
#include "placewindow.h"
#include "instancemanager.h"
#include "picksinglepanel.h"

/**
 *
 * @author Pete Cressman Copyright: Copyright (c) 2019
 *
 * @param <T> type of NamedBean in PickList
 */
// /*public*/ class OpenPickListButton<T extends NamedBean> {


    OpenPickListButton::OpenPickListButton(QStringList blurbLines, PickListModel/*<T>*/* model, QWidget* parent) {
        _model = model;
        _blurbLines = blurbLines;
        _buttonPanel = makePickListPanel();
        _parent = parent;
    }

    /*private*/ JPanel* OpenPickListButton::makePickListPanel() {
        JPanel* buttonPanel = new JPanel();
        buttonPanel->setLayout(new QVBoxLayout());//buttonPanel, BoxLayout.Y_AXIS));
        JPanel* panel = new JPanel();
        panel->setLayout(new FlowLayout());

        _openPicklistButton = new QPushButton(tr("Open %1 Picklist").arg(_model->getName()));
        //_openPicklistButton.addActionListener((ActionEvent a) -> {
        connect(_openPicklistButton, &QPushButton::clicked, [=]{
            if (_pickFrame == nullptr) {
                openPickList();
            } else {
                closePickList();
            }
        });
        panel->layout()->addWidget(_openPicklistButton);

        buttonPanel->layout()->addWidget(panel);
        return buttonPanel;
    }

    /*public*/ JPanel* OpenPickListButton::getButtonPanel() {
        return _buttonPanel;
    }

    void OpenPickListButton::openPickList() {
        _pickFrame = new JFrame();
        _pickFrame->setTitle(_model->getName());
        JPanel* content = new JPanel();
        content->setLayout(new QVBoxLayout());//content, BoxLayout.Y_AXIS));
        Border* padding = BorderFactory::createEmptyBorder(10, 5, 3, 5);
        content->setBorder(padding);

        JPanel* blurb = new JPanel();
        blurb->setLayout(new QVBoxLayout());//blurb, BoxLayout.Y_AXIS));
        for (QString text : _blurbLines) {
            ((QVBoxLayout*)blurb->layout())->addWidget(new JLabel(text),0, Qt::AlignCenter);
        }
        blurb->layout()->addWidget(Box::createVerticalStrut(5));
        JPanel* panel = new JPanel(new FlowLayout());
        panel->layout()->addWidget(blurb);
        content->layout()->addWidget(panel);
        PickSinglePanel/*<T>*/* pickPanel = new PickSinglePanel/*<T>*/(_model);
        content->layout()->addWidget(pickPanel);
        content->setToolTip(tr("Click on either the system or user name, then drag it and drop it into the entry field."));
        pickPanel->setToolTip(tr("Click on either the system or user name, then drag it and drop it into the entry field."));
        pickPanel->getTable()->setToolTip(tr("Click on either the system or user name, then drag it and drop it into the entry field."));

        //_pickFrame->setContentPane(content);
        _pickFrame->setCentralWidget(content);
#if 0
        _pickFrame.addWindowListener(new java.awt.event.WindowAdapter() {
            @Override
            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
                closePickList();
            }
        });
#endif
        ((PlaceWindow*)InstanceManager::getDefault("PlaceWindow"))-> nextTo(_parent, nullptr, _pickFrame);
        _pickFrame->toFront();
        _pickFrame->setVisible(true);
        _pickFrame->pack();
        _openPicklistButton->setText(tr("Click on either the system or user name, then drag it and drop it into the entry field."));
    }

    /*public*/ void OpenPickListButton::closePickList() {
        if (_pickFrame != nullptr) {
            _pickFrame->dispose();
            _pickFrame = nullptr;
            _openPicklistButton->setText(tr("Open %1 Picklist").arg(_model->getName()));
        }
    }
