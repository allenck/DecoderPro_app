#include "catalogtreemanager.h"

CatalogTreeManager::CatalogTreeManager(QObject *parent) :
    Manager(parent)
{
    IMAGE_FILTER = QString("gif,jpg,jpeg,png").split(",");
    SOUND_FILTER <<"wav";
    SCRIPT_FILTER <<"py"<< "scpt";

}
CatalogTreeManager(const char * s, QObject *parent)
{

}
