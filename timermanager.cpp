#include "timermanager.h"

Minute::Minute(int start_value, QLabel *lb) : TimeLabelCounter(start_value, 1, 0 , 10, lb)
{

}

Second::Second(int start_value, QLabel *lb) : TimeLabelCounter(start_value, 5, 0, 60, lb)
{

}

TimeLabelCounter::TimeLabelCounter(int value, int step, int min_value, int max_value, QLabel *lb) :
    Incrementable<int>(value, step, min_value, max_value), _lb(lb)
{
    SyncDisplayString();
}

void TimeLabelCounter::SyncDisplayString()
{
    QString displayString = ConverFromIntToDisplayString(_value);
    _lb->setText(displayString);
}

void TimeLabelCounter::PerformAction(bool IsUp)
{
    if(IsUp)
        Increment();
    else
        Decrement();
    SyncDisplayString();
}

QString TimeLabelCounter::ConverFromIntToDisplayString(int value)
{
    if(value >= 10)
    {
        return QString::number(value);
    }

    QString result = "0 ";
    result[1] = static_cast<char>(value) + '0';

    return result;
}


TimerManager::TimerManager(QLabel* lb_min, QLabel* lb_sec) : minutes(5, lb_min), seconds(30, lb_sec)
{

}

void TimerManager::ChangeMinutes(bool IsUp)
{
    minutes.PerformAction(IsUp);
}

void TimerManager::ChangeSeconds(bool IsUp)
{
    seconds.PerformAction(IsUp);
}

