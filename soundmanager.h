#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QSound>


class SoundManager : public QObject
{
    Q_OBJECT
    QSound **sounds;
public:
    SoundManager();
    ~SoundManager();
    void PlayRandomSound();
};

#endif // SOUNDMANAGER_H
