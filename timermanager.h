#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H

#include <stdexcept>
#include <QString>
#include <QLabel>

template<typename T>
class Incrementable
{
protected:
    T _value;
    T _step;
    T _min_value;
    T _max_value;
public:
    Incrementable(T value, T step, T min_value, T max_value) :
        _value(value), _step(step) , _min_value(min_value), _max_value(max_value)
    {
        if(step < 0)
            throw std::invalid_argument("_step must be bigger than 0");
    }

    bool virtual Increment()
    {
        bool isJumpedOver = false;
        T next_value = _value + _step;
        if(next_value >= _max_value)
        {
            _value = next_value % _step;
            isJumpedOver = true;
        }
        else
            _value = next_value;
        return isJumpedOver;
    }
    bool virtual Decrement()
    {
        bool isJumpedOver = false;
        T next_value = _value - _step;
        if(next_value < _min_value)
        {
            isJumpedOver = true;
            _value = _max_value - _step;
        }
        else
            _value = next_value;

        return isJumpedOver;
    }
    T Value()
    {
        return _value;
    }
};

class TimeLabelCounter : public Incrementable<int>
{
protected:
    QLabel *_lb;
    QString ConverFromIntToDisplayString(int value);
    void SyncDisplayString();
    TimeLabelCounter* _nextGreater;
public:
    TimeLabelCounter(int value, int step, int min_value, int max_value, QLabel *lb, TimeLabelCounter* nextGreater = nullptr);
    void PerformAction(bool IsUp);
};

class Minute : public TimeLabelCounter
{
public:
    Minute(int start_value, QLabel *lb);
};

class Second : public TimeLabelCounter
{
public:
    Second(int start_value, QLabel *lb, TimeLabelCounter* nextGreater);
};

class TimerManager
{
private:
    Minute minutes;
    Second seconds;

    ;
public:
    TimerManager(QLabel* lb_min, QLabel* lb_sec);
    void ChangeMinutes(bool IsUp);
    void ChangeSeconds(bool IsUp);

};

#endif // TIMERMANAGER_H
