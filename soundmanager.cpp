#include "soundmanager.h"

SoundManager::SoundManager()
{
    _audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    _mediaObject = new Phonon::MediaObject(this);

    _mediaObject->setTickInterval(1000);

    connect(_mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
            this, SLOT(stateChanged(Phonon::State,Phonon::State)));
    connect(_mediaObject, SIGNAL(currentSourceChanged(Phonon::MediaSource)),
            this, SLOT(sourceChanged(Phonon::MediaSource)));
    connect(_mediaObject, SIGNAL(aboutToFinish()), this, SLOT(aboutToFinish()));

    Phonon::createPath(_mediaObject, _audioOutput);

    //Phonon::MediaSource source(/*PUT PATH TO SONG HERE*/);
    //_mediaObject->setCurrentSource(source);
}

void SoundManager::sourceChanged(const Phonon::MediaSource &source)
{
    if (source.fileName() != "") {
        _mediaObject->play();
    }
}

void SoundManager::stateChanged(Phonon::State newState, Phonon::State oldState)
{
    switch (newState) {
        case Phonon::ErrorState:
            qDebug() << "Error playing music" << _mediaObject->errorString();
            break;
        case Phonon::StoppedState:
            //nothin
            break;
        case Phonon::PlayingState:
            //nothin
            break;
        case Phonon::BufferingState:
            break;
        default:
            ;

    }
}

void SoundManager::aboutToFinish()
{
    qDebug() << "nothin for now, maybe restart";
}
