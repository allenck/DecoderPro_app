#ifndef PANELEDITOR_H
#define PANELEDITOR_H
#include "editor.h"

class PanelEditor : public Editor
{
    Q_OBJECT
public:
    explicit PanelEditor(QWidget *parent = 0);
    
signals:
    
public slots:
    
private:
 Logger log;
};

#endif // PANELEDITOR_H
