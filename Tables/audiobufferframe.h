#ifndef AUDIOBUFFERFRAME_H
#define AUDIOBUFFERFRAME_H
#include "abstractaudioframe.h"
#include "libtables_global.h"

class JActionEvent;
class QFileDialog;
class QCheckBox;
class QPushButton;
class LIBTABLESSHARED_EXPORT AudioBufferFrame : public AbstractAudioFrame
{
 Q_OBJECT
public:
 //explicit AudioBufferFrame(QWidget *parent = 0);
 /*public*/ AudioBufferFrame(QString title, AudioTableDataModel* model, QWidget *parent = 0);
 /*public*/ void layoutFrame();
 /*public*/ void resetFrame();
 /*public*/ void populateFrame(Audio* a);
 /*public*/ QString getClassName();

signals:

public slots:
 void browsePressed(JActionEvent* e = 0);
 void okPressed(JActionEvent* e = 0);
 void On_loopStart_valueChanged();
 void On_loopEnd_valueChanged();
private:
 /*private*/ static int counter;// = 1;

 /*private*/ bool _newBuffer;

 /*private*/ /*final*/ QObject* lock;// = new Object();

 // UI components for Add/Edit Buffer
 QLabel* urlLabel;// = new JLabel(rba.getString("LabelURL"));
 JTextField* url;// = new JTextField(40);
 QPushButton* buttonBrowse;// = new JButton(rba.getString("ButtonBrowse"));
 QCheckBox* stream;// = new JCheckBox(rba.getString("LabelStream"));
//    QLabel* formatLabel = new JLabel(rba.getString("LabelFormat"));
//    JTextField format = new JTextField(20);
 QLabel* loopStartLabel;// = new JLabel(rba.getString("LabelLoopStart"));
 QSpinBox* loopStart;// = new JSpinner();
 QLabel* loopEndLabel;// = new JLabel(rba.getString("LabelLoopEnd"));
 QSpinBox* loopEnd;// = new JSpinner();
 QFileDialog* fileChooser;
 Logger* log;
};

#endif // AUDIOBUFFERFRAME_H
