#ifndef AUTOTRAINSFRAME_H
#define AUTOTRAINSFRAME_H
#include "jmrijframe.h"

class QVBoxLayout;
class QLabel;
class QRadioButton;
class QPushButton;
class QSlider;
class JSeparator;
class AutoActiveTrain;
class Throttle;
class PropertyChangeListener;
class DispatcherFrame;
class AutoTrainsFrame : public JmriJFrame
{
public:
 /*public*/ AutoTrainsFrame(DispatcherFrame* disp);
 /*public*/ QList<AutoActiveTrain*>* getAutoTrainsList();
 /*public*/ void addAutoActiveTrain(AutoActiveTrain* aat);
 /*public*/ void removeAutoActiveTrain(AutoActiveTrain* aat);
 /*public*/ QString getClassName() override;
  /*public*/ void stopResume(QString s);
  /*public*/ void manualAuto(QString s);
  /*public*/ void resumeAutoOperation(QString s);
  /*public*/ void directionButton(QString s);
  /*public*/ void sliderChanged(QString s, int value);
  /*public*/ void stopAllPressed(/*ActionEvent e*/);

private:
 Logger* log;
 // instance variables
 /*private*/ DispatcherFrame* _dispatcher;// = null;
 /*private*/ QList<AutoActiveTrain*>* _autoTrainsList;// = new QList<AutoActiveTrain*>();
 /*private*/ QList<PropertyChangeListener*>* _listeners; // = new QList<PropertyChangeListener*>();
 //Keep track of throttle and listeners to update frame with their current state.
 /*private*/ QList<Throttle*>* _throttles;// = new QList<Throttle>();
 /*private*/ QList<PropertyChangeListener*>* _throttleListeners; // = new QList<PropertyChangeListener*>();

 // variables for AutoTrains window
 /*protected*/ JmriJFrame* autoTrainsFrame;// = NULL;
 /*private*/ QWidget* contentPane;// = NULL;
 QVBoxLayout* contentPaneLayout;
 //This would be better refactored this all into a sub-class, rather than multiple arraylists.
 // note: the following array lists are synchronized with _autoTrainsList
 /*private*/ QList<QWidget*>* _JPanels;// = new QList<JPanel>();
 /*private*/ QList<QLabel*>* _throttleStatus;// = new QList<QLabel* >();
 /*private*/ QList<QLabel* >* _trainLabels;// = new QList<QLabel* >();
 /*private*/ QList<QPushButton* >* _stopButtons;// = new QList<QPushButton* >();
 /*private*/ QList<QPushButton* >* _manualButtons;// = new QList<QPushButton* >();
 /*private*/ QList<QPushButton* >* _resumeAutoRunningButtons;// = new QList<QPushButton* >();
 /*private*/ QList<QRadioButton*>* _forwardButtons;// = new QList<QRadioButton*>();
 /*private*/ QList<QRadioButton*>* _reverseButtons;// = new QList<QRadioButton*>();
 /*private*/ QList<QSlider*>* _speedSliders;// = new QList<JSlider>();

 /*private*/ QList<JSeparator*>* _separators;// = new QList<JSeparator*>();
 /*private*/ void initializeAutoTrainsWindow();
 /*private*/ void removeThrottleListener(AutoActiveTrain* aat);
 /*private*/ void newSeparator();
 /*private*/ void newTrainLine();
 /*private*/ void placeWindow();
 /*private*/ int getTrainIndex(QString s);

protected:
 /*protected*/ void displayAutoTrains();

};

#endif // AUTOTRAINSFRAME_H
