#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QMessageBox>
#include <phonon/audiooutput.h>
#include <phonon/mediaobject.h>
#include <phonon/backendcapabilities.h>


class SoundManager : public QObject
{
    Q_OBJECT

public:
    SoundManager();
    
signals:

private slots:
    void stateChanged(Phonon::State newState, Phonon::State oldState);
    void sourceChanged(const Phonon::MediaSource &source);
    void aboutToFinish();

private:
    Phonon::MediaObject *_mediaObject;
    Phonon::AudioOutput *_audioOutput;
    QList<Phonon::MediaSource> _sources;

    QAction *_playAction;
    QAction *_pauseAction;

};

#endif // SOUNDMANAGER_H
