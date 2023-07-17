#include "timermanager.h"
#include "constants.h"

using namespace constants::Time;

Minute::Minute(int start_value, QLabel *lb) :
    TimeLabelCounter(start_value, MINUTES_STEP, MINUTES_MIN , MINUTES_MAX, lb)
{}

Second::Second(int start_value, QLabel *lb, TimeLabelCounter* nextGreater) :
    TimeLabelCounter(start_value, SECONDS_STEP, SECONDS_MIN, SECONDS_MAX, lb, nextGreater)
{}

TimeLabelCounter::TimeLabelCounter(int value, int step, int min_value, int max_value, QLabel *lb, TimeLabelCounter* nextGreater) :
    Incrementable<int>(value, step, min_value, max_value), _lb(lb), _nextGreater(nextGreater)
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
    {
        if(Increment() && _nextGreater)
        {
            _nextGreater->PerformAction(IsUp);
        }
    }
    else
    {
        if(Decrement() && _nextGreater)
        {
            _nextGreater->PerformAction(IsUp);
        }
    }
    SyncDisplayString();
}

QString TimeLabelCounter::ConverFromIntToDisplayString(int value)
{
    if(value >= 10)
        return QString::number(value);


    QString result = "0 ";
    result[1] = static_cast<char>(value) + '0';

    return result;
}


TimerManager::TimerManager(QLabel* lb_min, QLabel* lb_sec) :
    minutes(MINUTES_DEFAULT, lb_min), seconds(SECONDS_DEFAULT, lb_sec, &minutes)
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

