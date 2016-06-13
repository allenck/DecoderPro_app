#ifndef PREFERENCESPANE_H
#define PREFERENCESPANE_H
#include <QWidget>
#include "logger.h"

class GuiLafConfigPane;
class PreferencesPane : public QWidget
{
    Q_OBJECT
public:
    explicit PreferencesPane(QWidget *parent = 0);

signals:

public slots:
    void preferencesSavePressed();
private:
    void saveContents();
    GuiLafConfigPane* guiPrefs;
    Logger* log;
    bool configOK;

protected:
    /*protected*/ QString configFilename;// = null;
    /*protected*/ void loadPreferenceFile();// throw (JmriException);

};

#endif // PREFERENCESPANE_H
