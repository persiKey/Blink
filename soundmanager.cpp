#include "soundmanager.h"
#include "constants.h"

using namespace constants::Sound;

SoundManager::SoundManager()
{
    sounds = new QSound*[AMOUNT_OF_SOUNDS];
    for(int i = 1; i <= AMOUNT_OF_SOUNDS; ++i )
    {
        sounds[i-1] = new QSound("../Blink/sound/blink" + QString::number(i)+ ".wav", this);
    }
}

SoundManager::~SoundManager()
{
    qDeleteAll(sounds, sounds + AMOUNT_OF_SOUNDS);
    delete[] sounds;
}

void SoundManager::PlayRandomSound()
{
    srand(time(0));
    sounds[rand() % AMOUNT_OF_SOUNDS]->play();
}
