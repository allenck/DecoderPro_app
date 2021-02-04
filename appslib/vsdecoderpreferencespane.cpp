#include "vsdecoderpreferencespane.h"
#include <QPushButton>
#include <QButtonGroup>
#include <QCheckBox>
#include "jtextfield.h"
#include <QLabel>
#include <QRadioButton>
#include "vsdecodermanager.h"
#include "vsdecoderpreferences.h"
#include "insets.h"
#include "gridbagconstraints.h"
#include <QGridLayout>
#include "jfilechooser.h"
#include "file.h"
#include "jframe.h"
#include "propertychangeevent.h"
#include <QUrl>
#include "rosterentry.h"

/**
 * Pane to show VSDecoder Preferences.
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author			Mark Underwood Copyright (C) 2011
 * @version			$Revision: 28746 $
 */
//class VSDecoderPreferencesPane extends javax.swing.QWidget*implements PropertyChangeListener {

    ///*private*/ static final long serialVersionUID = -5473594799045080011L;


/**
 * Creates new form VSDecoderPreferencesPane
 */
/*public*/ VSDecoderPreferencesPane::VSDecoderPreferencesPane(VSDecoderPreferences* tp, QWidget *parent) :
QWidget(parent) {
    initComponents();
    setComponents(tp);
    checkConsistency();
    tp->addPropertyChangeListener((PropertyChangeListener*)this);
}

/*public*/ VSDecoderPreferencesPane::VSDecoderPreferencesPane(QWidget *parent) :
QWidget(parent) {
    //this(VSDecoderManager::instance()->getVSDecoderPreferences());
 initComponents();
 setComponents(VSDecoderManager::instance()->getVSDecoderPreferences());
 checkConsistency();
 VSDecoderManager::instance()->getVSDecoderPreferences()->addPropertyChangeListener((PropertyChangeListener*)this);
}

/*private*/ GridBagConstraints VSDecoderPreferencesPane::setConstraints(Insets* i, int x, int y, int width, int fill) {
    GridBagConstraints gbc =  GridBagConstraints();
    gbc.insets = i;
    gbc.gridx = x;
    gbc.gridy = y;
    gbc.gridwidth = width;
    gbc.anchor = GridBagConstraints::LINE_START;
    gbc.fill = fill;
    return (gbc);
}

/*private*/ void VSDecoderPreferencesPane::initComponents() {

    QWidget*prefsPane = new QWidget();
    QWidget*controlPane = new QWidget();

    QGridLayout* g = new QGridLayout();
    this->setLayout(g);
    //this->setBorder(BorderFactory.createEmptyBorder());

    jbCancel = new QPushButton();
    jbSave = new QPushButton();
    jbApply = new QPushButton();

    labelApplyWarning = new QLabel();
    labelDefaultVSDFilePath = new QLabel();
    labelDefaultVSDFileName = new QLabel();

    cbAutoStartEngine = new QCheckBox();
    cbAutoLoadVSDFile = new QCheckBox();
    tfDefaultVSDFilePath = new JTextField(40);
    tfDefaultVSDFileName = new JTextField(40);
    QPushButton* jbPathBrowse = new QPushButton(tr("Browse"));
//    jbPathBrowse.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
//            jbPathBrowseActionPerformed(evt);
//        }
//    });
    connect(jbPathBrowse, SIGNAL(clicked()), this, SLOT(jbPathBrowseActionPerformed()));
    QPushButton* jbFileBrowse = new QPushButton(tr("Browse"));
//    jbFileBrowse.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
//            jbFileBrowseActionPerformed(evt);
//        }
//    });
    connect(jbFileBrowse, SIGNAL(clicked()), this, SLOT(jbFileBrowseActionPerformed()));

    // Audio Mode
    audioModeRoomButton = new QRadioButton("Room Ambient");
    audioModeHeadphoneButton = new QRadioButton("Headphones");
    audioModeGroup = new QButtonGroup();
    audioModeGroup->addButton(audioModeRoomButton);
    audioModeGroup->addButton(audioModeHeadphoneButton);
    QWidget*amPanel = new QWidget();
    QHBoxLayout* amPanelLayout;
    amPanel->setLayout(amPanelLayout = new QHBoxLayout()); //(amPanel, BoxLayout.LINE_AXIS));
    amPanelLayout->addWidget(new QLabel("Audio Mode:"));
    amPanelLayout->addWidget(audioModeRoomButton);
    amPanelLayout->addWidget(audioModeHeadphoneButton);

    // Get label strings from the resource bundle and assign it.
    cbAutoStartEngine->setText(tr("AutoStartEngine"));
    cbAutoLoadVSDFile->setText(tr("AutoLoadVSDFile"));
    tfDefaultVSDFilePath->setColumns(30);
    tfDefaultVSDFilePath->setColumns(30);
    labelDefaultVSDFilePath->setText(tr("DefaultVSDFilePath"));
    labelDefaultVSDFileName->setText(tr("DefaultVSDFileName"));
    labelApplyWarning->setText(tr("ExVSDecoderLabelApplyWarning"));

    // Set action listener to check consistency when the user makes changes.
//    java.awt.event.ActionListener al = new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
//            checkConsistency();
//        }
//    };

    //cbAutoStartEngine->addActionListener(al);
    connect(cbAutoStartEngine, SIGNAL(clicked()), this, SLOT(checkConsistency()));
    //cbAutoLoadVSDFile.addActionListener(al);
    connect(cbAutoLoadVSDFile, SIGNAL(clicked()), this, SLOT(checkConsistency()));
   // tfDefaultVSDFilePath.addActionListener(al);
    connect(tfDefaultVSDFilePath, SIGNAL(clicked()), this, SLOT(checkConsistency()));
    //tfDefaultVSDFileName.addActionListener(al);
    connect(tfDefaultVSDFileName, SIGNAL(clicked()), this, SLOT(checkConsistency()));

    // Set action listeners for save / cancel / reset buttons
    jbSave->setText(tr("VSDecoderPrefsSave"));
//    jbSave.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
//            jbSaveActionPerformed(evt);
//        }
//    });
    connect(jbSave, SIGNAL(clicked()), this, SLOT(jbSaveActionPerformed()));
    jbSave->setVisible(false);

    jbCancel->setText(tr("VSDecoderPrefsReset"));
//    jbCancel.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
//            jbCancelActionPerformed(evt);
//        }
//    });
    connect(jbCancel, SIGNAL(clicked()), this, SLOT(jbCancelActionPerformed()));

    jbApply->setText(tr("VSDecoderPrefsApply"));
//    jbApply.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
//            jbApplyActionPerformed(evt);
//        }
//    });
    connect(jbApply, SIGNAL(clicked()), this, SLOT(jbApplyActionPerformed()));
    QGridLayout* g2 = new QGridLayout();
    prefsPane->setLayout(g2);
    //prefsPane->setBorder(BorderFactory.createEmptyBorder());
    QGridLayout* g3 = new QGridLayout();
    controlPane->setLayout(g3);
    //controlPane->setBorder(BorderFactory.createEmptyBorder());

    //prefsPane.add(cbAutoStartEngine, setConstraints(new Insets(2, 10, 2, 2), 0, 0, 2, GridBagConstraints::NONE)); //1
    GridBagConstraints gb2 = setConstraints(new Insets(2, 10, 2, 2), 0, 0, 2, GridBagConstraints::NONE);
    g2->addWidget(cbAutoStartEngine,gb2.gridy, gb2.gridx, gb2.rowSpan(), gb2.colSpan());
    //prefsPane.add(cbAutoLoadVSDFile, setConstraints(new Insets(2, 10, 2, 2), 0, 1, 2, GridBagConstraints::NONE)); //2
    gb2 = setConstraints(new Insets(2, 10, 2, 2), 0, 1, 2, GridBagConstraints::NONE);
    g2->addWidget(cbAutoLoadVSDFile,gb2.gridy, gb2.gridx, gb2.rowSpan(), gb2.colSpan());

    //prefsPane.add(labelDefaultVSDFilePath, setConstraints(new Insets(2, 10, 2, 2), 0, 2, 1, GridBagConstraints::NONE)); //5
    gb2= setConstraints(new Insets(2, 10, 2, 2), 0, 2, 1, GridBagConstraints::NONE);
    g2->addWidget(labelDefaultVSDFilePath,gb2.gridy, gb2.gridx, gb2.rowSpan(), gb2.colSpan());
    //prefsPane.add(tfDefaultVSDFilePath, setConstraints(new Insets(2, 10, 2, 2), 1, 2, 3, GridBagConstraints::HORIZONTAL)); //3
    gb2=setConstraints(new Insets(2, 10, 2, 2), 1, 2, 3, GridBagConstraints::HORIZONTAL);
    g2->addWidget(tfDefaultVSDFilePath,gb2.gridy, gb2.gridx, gb2.rowSpan(), gb2.colSpan());
    //prefsPane.add(jbPathBrowse, setConstraints(new Insets(2, 2, 2, 2), 5, 2, 1, GridBagConstraints::NONE)); //3
    gb2=setConstraints(new Insets(2, 2, 2, 2), 5, 2, 1, GridBagConstraints::NONE);
    g2->addWidget(jbPathBrowse,gb2.gridy, gb2.gridx, gb2.rowSpan(), gb2.colSpan());

    //prefsPane.add(labelDefaultVSDFileName, setConstraints(new Insets(2, 10, 2, 2), 0, 3, 1, GridBagConstraints::NONE)); //6
    gb2 = setConstraints(new Insets(2, 10, 2, 2), 0, 3, 1, GridBagConstraints::NONE);
    g2->addWidget(labelDefaultVSDFileName,gb2.gridy, gb2.gridx, gb2.rowSpan(), gb2.colSpan());
    //prefsPane.add(tfDefaultVSDFileName, setConstraints(new Insets(2, 10, 2, 2), 1, 3, 2, GridBagConstraints::HORIZONTAL)); //4
    gb2 = setConstraints(new Insets(2, 10, 2, 2), 1, 3, 2, GridBagConstraints::HORIZONTAL);
    g2->addWidget(tfDefaultVSDFileName,gb2.gridy, gb2.gridx, gb2.rowSpan(), gb2.colSpan());
    //prefsPane.add(jbFileBrowse, setConstraints(new Insets(2, 2, 2, 2), 5, 3, 1, GridBagConstraints::NONE)); //3
    gb2=setConstraints(new Insets(2, 2, 2, 2), 5, 3, 1, GridBagConstraints::NONE);
    g2->addWidget(jbFileBrowse,gb2.gridy, gb2.gridx, gb2.rowSpan(), gb2.colSpan());
    //prefsPane.add(amPanel, setConstraints(new Insets(2, 10, 2, 2), 0, 6, 2, GridBagConstraints::HORIZONTAL));
    gb2 = setConstraints(new Insets(2, 10, 2, 2), 0, 6, 2, GridBagConstraints::HORIZONTAL);
    g2->addWidget(amPanel,gb2.gridy, gb2.gridx, gb2.rowSpan(), gb2.colSpan());

    //controlPane.add(jbSave, setConstraints(new Insets(5, 3, 5, 2), 2, 100, 1, GridBagConstraints::NONE)); //7
    GridBagConstraints gb3 = setConstraints(new Insets(5, 3, 5, 2), 2, 100, 1, GridBagConstraints::NONE);
    g3->addWidget(jbSave,gb3.gridy, gb3.gridx, gb3.rowSpan(), gb3.colSpan());
    //controlPane.add(jbCancel, setConstraints(new Insets(5, 3, 5, 2), 0, 100, 1, GridBagConstraints::NONE)); //8
    gb3=setConstraints(new Insets(5, 3, 5, 2), 0, 100, 1, GridBagConstraints::NONE);
    g3->addWidget(jbCancel,gb3.gridy, gb3.gridx, gb3.rowSpan(), gb3.colSpan());

    //controlPane.add(jbApply, setConstraints(new Insets(5, 3, 5, 5), 1, 100, 1, GridBagConstraints::NONE)); //9
    gb3=setConstraints(new Insets(5, 3, 5, 5), 1, 100, 1, GridBagConstraints::NONE);
    g3->addWidget(jbApply,gb3.gridy, gb3.gridx, gb3.rowSpan(), gb3.colSpan());


    //this.add(prefsPane, setConstraints(new Insets(2, 2, 2, 2), 0, 0, 1, GridBagConstraints::NONE));
    GridBagConstraints gb = setConstraints(new Insets(2, 2, 2, 2), 0, 0, 1, GridBagConstraints::NONE);
    g->addWidget(prefsPane,gb.gridy, gb.gridx, gb.rowSpan(), gb.colSpan());
    //this.add(controlPane, setConstraints(new Insets(2, 2, 2, 2), 0, 1, 1, GridBagConstraints::NONE));
    gb = setConstraints(new Insets(2, 2, 2, 2), 0, 1, 1, GridBagConstraints::NONE);
    g->addWidget(controlPane,gb.gridy, gb.gridx, gb.rowSpan(), gb.colSpan());

    this->setVisible(true);
}

/*private*/ void VSDecoderPreferencesPane::setComponents(VSDecoderPreferences* tp) {
    if (tp == NULL) {
        return;
    }
    cbAutoStartEngine->setChecked(tp->isAutoStartingEngine());
    cbAutoLoadVSDFile->setChecked(tp->isAutoLoadingDefaultVSDFile());
    tfDefaultVSDFilePath->setText(tp->getDefaultVSDFilePath());
    tfDefaultVSDFileName->setText(tp->getDefaultVSDFileName());
    switch (tp->getAudioMode()) {
        case VSDecoderPreferences::HEADPHONES:
            audioModeHeadphoneButton->setChecked(true);
            break;
        case VSDecoderPreferences::ROOM_AMBIENT:
        default:
            audioModeRoomButton->setChecked(true);
            break;
    }
}

/*private*/ VSDecoderPreferences* VSDecoderPreferencesPane::getVSDecoderPreferences() {
    VSDecoderPreferences* tp = new VSDecoderPreferences();
    tp->setAutoStartEngine(cbAutoStartEngine->isChecked());
    tp->setAutoLoadDefaultVSDFile(cbAutoLoadVSDFile->isChecked());
    tp->setDefaultVSDFilePath(tfDefaultVSDFilePath->text());
    tp->setDefaultVSDFileName(tfDefaultVSDFileName->text());
    tp->setListenerPosition(VSDecoderManager::instance()->getVSDecoderPreferences()->getListenerPosition());
    if (audioModeRoomButton->isChecked()) {
        tp->setAudioMode(VSDecoderPreferences::ROOM_AMBIENT);
    } else if (audioModeHeadphoneButton->isChecked()) {
        tp->setAudioMode(VSDecoderPreferences::HEADPHONES);
    }

    return tp;
}

/*private*/ void VSDecoderPreferencesPane::checkConsistency() {
    /*
     cbSaveThrottleOnLayoutSave->setEnabled( cbUseExThrottle.isSelected() );
     cbUseToolBar->setEnabled( cbUseExThrottle.isSelected() );
     cbUseFunctionIcon->setEnabled( cbUseExThrottle.isSelected() );
     cbEnableRosterSearch->setEnabled( cbUseExThrottle.isSelected() );
     cbEnableAutoLoad->setEnabled( cbUseExThrottle.isSelected() );
     cbUseRosterImage->setEnabled( cbUseExThrottle.isSelected() );
     cbResizeWinImg->setEnabled( cbUseExThrottle.isSelected()  &&  cbUseRosterImage.isSelected() );
     cbHideUndefinedButtons->setEnabled( cbUseExThrottle.isSelected() );
     cbIgnoreThrottlePosition->setEnabled( cbUseExThrottle.isSelected() && cbEnableAutoLoad.isSelected() );
     cbCleanOnDispose->setEnabled( cbUseExThrottle.isSelected() );
     if ( cbUseExThrottle.isSelected() ) {
     if ( cbUseToolBar.isSelected() ) {
     cbIgnoreThrottlePosition->setChecked( true );
     cbIgnoreThrottlePosition->setEnabled( false );
     }
     }
     */
}

/*private*/ void VSDecoderPreferencesPane::jbPathBrowseActionPerformed(JActionEvent* /*evt*/) {
    // Browse for a path.  Update the UI
    // use the path currently in the window text field, if possible.
    QString path;
    if (tfDefaultVSDFilePath->text() != NULL) {
        path = tfDefaultVSDFilePath->text();
    } else {
        path = VSDecoderManager::instance()->getVSDecoderPreferences()->getDefaultVSDFilePath();
    }
    /*final*/ JFileChooser* fc = new JFileChooser(path);
    fc->setFileSelectionMode(JFileChooser::DIRECTORIES_ONLY);
    int rv = fc->showOpenDialog(this);
    if (rv == JFileChooser::APPROVE_OPTION) {
        //try {
            tfDefaultVSDFilePath->setText(fc->getSelectedFile()->getCanonicalPath());
//        } catch (java.io.IOException e) {
//            // do nothing.
//        }
    }
}

/*private*/ void VSDecoderPreferencesPane::jbFileBrowseActionPerformed(JActionEvent* /*evt*/) {
    // Browse for a file. Update the UI
    QString path;
    if (tfDefaultVSDFilePath->text() != NULL) {
        path = tfDefaultVSDFilePath->text();
    } else {
        path = VSDecoderManager::instance()->getVSDecoderPreferences()->getDefaultVSDFilePath();
    }
    /*final*/ JFileChooser* fc = new JFileChooser(path);
    fc->setFileSelectionMode(JFileChooser::FILES_ONLY);
    int rv = fc->showOpenDialog(this);
    if (rv == JFileChooser::APPROVE_OPTION)
    {
#if 0
        //try {
            QUrl* base = NULL;
            if (tfDefaultVSDFilePath->text() != NULL) {
                base = QUrl::create(tfDefaultVSDFilePath->text());
            } else {
                base = QUrl::create(VSDecoderManager.instance().getVSDecoderPreferences().getDefaultVSDFilePath());
            }
            QUrl absolute = QUrl.create(fc.getSelectedFile().getCanonicalPath());
            QUrl relative = base.relativize(absolute);

            tfDefaultVSDFileName->setText(relative.path());
#endif
//        } catch (java.io.IOException e) {
//            // do nothing.
//        }
    }
}

/*private*/ void VSDecoderPreferencesPane::jbApplyActionPerformed(JActionEvent* /*evt*/) {
    VSDecoderManager::instance()->getVSDecoderPreferences()->set(getVSDecoderPreferences());
}

/*public*/ void VSDecoderPreferencesPane::jbSaveActionPerformed(JActionEvent* /*evt*/) {
    VSDecoderManager::instance()->getVSDecoderPreferences()->set(getVSDecoderPreferences());
    VSDecoderManager::instance()->getVSDecoderPreferences()->save();
    if (m_container != NULL) {
        VSDecoderManager::instance()->getVSDecoderPreferences()->removePropertyChangeListener((PropertyChangeListener*)this);
        m_container->setVisible(false); // should do with events...
        m_container->dispose();
    }
}

/*private*/ void VSDecoderPreferencesPane::jbCancelActionPerformed(JActionEvent* /*evt*/) {
    setComponents(VSDecoderManager::instance()->getVSDecoderPreferences());
    checkConsistency();
    if (m_container != NULL) {
        VSDecoderManager::instance()->getVSDecoderPreferences()->removePropertyChangeListener((PropertyChangeListener*)this);
        m_container->setVisible(false); // should do with events...
        m_container->dispose();
    }
}

/*public*/ void VSDecoderPreferencesPane::setContainer(JFrame* f) {
    m_container = f;
    jbSave->setVisible(true);
    jbCancel->setText(tr("VSDecoderPrefsCancel"));
}

/*public*/ void VSDecoderPreferencesPane::propertyChange(PropertyChangeEvent* evt)
{
 if ((evt == NULL) || (evt->getPropertyName() == NULL))
 {
     return;
 }
 if (evt->getPropertyName().compare("VSDecoderPreferences") == 0)
 {
  if ((evt->getNewValue() == QVariant()) || (evt->getNewValue() == QVariant()))
  {
   return;
  }
  setComponents((VSDecoderPreferences*) VPtr<VSDecoderPreferences>::asPtr(evt->getNewValue()));
  checkConsistency();
 }
}

