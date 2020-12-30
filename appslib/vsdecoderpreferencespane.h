#ifndef VSDECODERPREFERENCESPANE_H
#define VSDECODERPREFERENCESPANE_H

#include <QWidget>
#include "appslib_global.h"

class Insets;
class JActionEvent;
class GridBagConstraints;
class JFrame;
class VSDecoderPreferences;
class QPushButton;
class QButtonGroup;
class QCheckBox;
class JTextField;
class QLabel;
class QRadioButton;
class PropertyChangeEvent;
class APPSLIBSHARED_EXPORT VSDecoderPreferencesPane : public QWidget
{
 Q_OBJECT
public:
 explicit VSDecoderPreferencesPane(QWidget *parent = 0);
 /*public*/ VSDecoderPreferencesPane(VSDecoderPreferences* tp,QWidget *parent = 0);
 /*public*/ void setContainer(JFrame* f);

signals:

public slots:
 void checkConsistency();
 /*public*/ void jbSaveActionPerformed(JActionEvent* evt = 0);
 /*public*/ void propertyChange(PropertyChangeEvent* evt);

private:
 /*private*/ QCheckBox* cbAutoStartEngine;
 /*private*/ QCheckBox* cbAutoLoadVSDFile;
 /*private*/ JTextField* tfDefaultVSDFilePath;
 /*private*/ JTextField* tfDefaultVSDFileName;
 /*private*/ QLabel* labelDefaultVSDFilePath;
 /*private*/ QLabel* labelDefaultVSDFileName;
 /*private*/ QRadioButton* audioModeRoomButton;
 /*private*/ QRadioButton* audioModeHeadphoneButton;
 /*private*/ QButtonGroup* audioModeGroup;

 /*private*/ QLabel* labelApplyWarning;
 /*private*/ QPushButton* jbApply;
 /*private*/ QPushButton* jbCancel;
 /*private*/ QPushButton* jbSave;
 /*private*/ JFrame* m_container;// = null;
 /*private*/ GridBagConstraints setConstraints(Insets* i, int x, int y, int width, int fill);
 /*private*/ void initComponents();
 /*private*/ void setComponents(VSDecoderPreferences* tp);
 /*private*/ VSDecoderPreferences* getVSDecoderPreferences();

private slots:
 /*private*/ void jbPathBrowseActionPerformed(JActionEvent* evt = 0);
 /*private*/ void jbFileBrowseActionPerformed(JActionEvent* evt = 0);
 /*private*/ void jbApplyActionPerformed(JActionEvent* evt= 0);
 /*private*/ void jbCancelActionPerformed(JActionEvent* evt = 0);

};

#endif // VSDECODERPREFERENCESPANE_H
