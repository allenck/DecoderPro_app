#include "audiosource.h"

int AudioSource::LOOP_CONTINUOUS = -1;
int AudioSource::LOOP_NONE = 0;

AudioSource::AudioSource(QObject* parent) : Audio("", parent) {}

AudioSource::AudioSource(QString systemName, QObject* parent) : Audio(systemName, parent) {}

AudioSource::AudioSource(QString systemName, QString userName, QObject* parent) : Audio(systemName, userName, parent) {}
