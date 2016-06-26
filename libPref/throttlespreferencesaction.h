#ifndef THROTTLESPREFERENCESACTION_H
#define THROTTLESPREFERENCESACTION_H

#include <QAction>
#include "libpref_global.h"

class LIBPREFSHARED_EXPORT ThrottlesPreferencesAction : public QAction
{
    Q_OBJECT
public:
    explicit ThrottlesPreferencesAction(QObject *parent = 0);
    /*public*/ ThrottlesPreferencesAction(QString s, QObject *parent = 0);
    ///*public*/ ThrottlesPreferencesAction();
public slots:
    /*public*/ void actionPerformed(ActionEvent* e = 0);

signals:

public slots:

};

#endif // THROTTLESPREFERENCESACTION_H
