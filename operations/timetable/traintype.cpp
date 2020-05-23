#include "traintype.h"
#include "jmricolorchooser.h"
#include "timetabledatamanager.h"

namespace TimeTable
{

/**
 * Define the content of a Train Type record.
 *
 * @author Dave Sand Copyright (C) 2018
 */
///*public*/ class TrainType {

    /**
     * Create a new train type with default values.
     * @param layoutId The parent layout id.
     * @throws IllegalArgumentException TYPE_ADD_FAIL
     */
    /*public*/ TrainType::TrainType(int layoutId,QObject *parent) : QObject(parent) {
     _dm = TimeTableDataManager::getDataManager();

        if (_dm->getLayout(layoutId) == nullptr) {
            throw  IllegalArgumentException(TimeTableDataManager::TYPE_ADD_FAIL);
        }
        _typeId = _dm->getNextId("TrainType");  // NOI18N
        _layoutId = layoutId;
        _dm->addTrainType(_typeId, this);
    }

    /*public*/ TrainType::TrainType(int typeId, int layoutId, QString typeName, QString typeColor, QObject *parent) : QObject(parent) {
        _typeId = typeId;
        _layoutId = layoutId;
        setTypeName(typeName);
        setTypeColor(typeColor);
    }

    /*public*/ int TrainType::getTypeId() {
        return _typeId;
    }

    /*public*/ int TrainType::getLayoutId() {
        return _layoutId;
    }

    /*public*/ QString TrainType::getTypeName() {
        return _typeName;
    }

    /*public*/ void TrainType::setTypeName(QString newName) {
        _typeName = newName;
    }

    /*public*/ QString TrainType::getTypeColor() {
        return _typeColor;
    }

    /*public*/ void TrainType::setTypeColor(QString newColor) {
        _typeColor = newColor;
        JmriColorChooser::addRecentColor(/*Color.decode*/(newColor));
    }

    //@Override
    /*public*/ QString TrainType::toString() {
        return _typeName;
    }
}
