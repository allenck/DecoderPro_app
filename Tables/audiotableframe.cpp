#include "audiotableframe.h"
#include "audiotablepanel.h"
#include <QBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include "savemenu.h"

//AudioTableFrame::AudioTableFrame(QWidget *parent) :
//  BeanTableFrame(parent)
//{
//}
/**
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 *
 * @author	Bob Jacobsen Copyright (C) 2003
 * @author Matthew Harris copyright (c) 2009
 * @version $Revision: 28746 $
 */
// /*public*/ class AudioTableFrame extends BeanTableFrame {

    //static final ResourceBundle rba = ResourceBundle.getBundle("jmri.jmrit.audio.swing.AudioTableBundle");
    /**
     *
     */
//    private static final long serialVersionUID = -92682823885444455L;

/*public*/ AudioTableFrame::AudioTableFrame(AudioTablePanel* panel,
        QString helpTarget, QWidget *parent) :
BeanTableFrame(parent)
{
 //super();

 audioPanel = panel;

 setFrameRef(getClassName());

 // general GUI config
 //getContentPane()->setLayout(new QVBoxLayout);//(getContentPane(), BoxLayout.Y_AXIS));
 QVBoxLayout* centralWidgetLayout;
 if(getContentPane(true) == NULL)
 {
  QWidget* centralWidget = new QWidget;
  centralWidget->setLayout(centralWidgetLayout = new QVBoxLayout);
  setCentralWidget(centralWidget);
 }
 else
  centralWidgetLayout = (QVBoxLayout*)centralWidget()->layout();

 // add save menu item
 QMenuBar* menuBar = new QMenuBar();
 QMenu* fileMenu = new QMenu(tr("File"));
 menuBar->addMenu(fileMenu);
 fileMenu->addMenu(new SaveMenu());

 //fileMenu.add(panel.getPrintItem());
 setMenuBar(menuBar);

 addHelpMenu(helpTarget, true);

 // install items in GUI
 //getContentPane().add(audioPanel);
 centralWidgetLayout->addWidget(audioPanel);
// bottomBox = Box.createHorizontalBox();
// bottomBox.add(Box.createHorizontalGlue());	// stays at end of box
 bottomBoxIndex = 0;

 //getContentPane().add(bottomBox);
 centralWidgetLayout->addWidget(bottomBox);

 // add extras, if desired by subclass
 extras();

}

//@Override
/*public*/ void AudioTableFrame::dispose() {
 if (audioPanel != NULL) {
     audioPanel->dispose();
 }
 BeanTableFrame::dispose();
}
