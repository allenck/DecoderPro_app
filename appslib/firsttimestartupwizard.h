#ifndef FIRSTTIMESTARTUPWIZARD_H
#define FIRSTTIMESTARTUPWIZARD_H

#include <QObject>
#include <QSize>
#include <QLocale>
#include <QImage>

class QPushButton;
class QVBoxLayout;
class QComboBox;
class JTextField;
class WizardPage;
class QLabel;
class Apps3;
class JmrixConfigPane;
class JmriJFrame;
class QImage;
class Logger;
class FirstTimeStartUpWizard : public QObject
{
 Q_OBJECT
public:
 /*public*/ FirstTimeStartUpWizard(JmriJFrame* parent, Apps3* app);
 /*public*/ void dispose();
 /*public*/ QWidget* doLocale();
 /*public*/ QWidget* getPanel();


signals:

public slots:
 void onCancel();
 void onPrevious();
 void onNext();
 void onFinish();
 void onLocaleBox();
 void update(QMap<QString,QLocale>);

private:
 static Logger* log;
 QImage splashIm;

 JmriJFrame* parent;
 /*private*/ /*final*/ JmrixConfigPane* connectionConfigPane;// = JmrixConfigPane.createNewPanel();
 QLabel* header;// = new JLabel();
 QList<WizardPage*> wizPage;// = new ArrayList<>();
 Apps3* app;

 QWidget* entryPanel;// = new JPanel();
 QVBoxLayout* entryPanelLayout;
 QWidget* helpPanel;// = new JPanel();
 QSize minHelpFieldDim;// = new Dimension(160, 20);
 QSize maxHelpFieldDim;// = new Dimension(160, 300);
 JTextField* owner;// = new JTextField(20);
 int currentScreen = 0;
 QLocale initalLocale;
 QComboBox* localeBox;
 QMap<QString, QLocale> locale;
 QStringList localeNames;

 QWidget* mainWizardPanel;// = new JPanel();
 QWidget* createTopBanner();
 QWidget* createHelpPanel();
 void createScreens();
 QWidget* createEntryPanel();
 void setDefaultOwner();
 void setConnection();
 void firstWelcome();
 void finishAndConnect();
 QWidget* createButtonPanel();
 QPushButton* finish;
 QPushButton* previous;
 QPushButton* next;
 QLabel* formatText(QString text);

 friend class Connect;
};

/*protected*/ class Connect : public QObject//implements Runnable
{
Q_OBJECT
   // @Override
 FirstTimeStartUpWizard* wizard;
public:
 Connect(FirstTimeStartUpWizard* wizard);
public slots:
    /*public*/ void process();
signals:
 void finished();
};

/*static*/ class WizardPage : public QObject
{
 Q_OBJECT

    static QSize defaultInfoSize;// = new Dimension(500, 300);
    QWidget* panel;
    QWidget* helpDetails;// = new QWidget();
    QString headerText;// = "";
public:
    WizardPage(QWidget* mainPanel, QWidget* helpDetails, QString headerText) ;
    QWidget* getPanel() ;
    QWidget* getHelpDetails() ;
    QString getHeaderText();
};

class FindLocales : public QObject
{
 Q_OBJECT
 FirstTimeStartUpWizard* wizard;
 QVector<QString> localeNames;
 QMap<QString,QLocale> locale;

public:
 FindLocales(FirstTimeStartUpWizard* wizard);
public slots:
 void process();

signals:
 void finished();
 void update(QMap<QString,QLocale>);

};
#endif // FIRSTTIMESTARTUPWIZARD_H
