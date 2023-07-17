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
    bool JumpedOverLimitValue = true;
public:
    Incrementable(T value, T step, T min_value, T max_value) :
        _value(value), _step(step) , _min_value(min_value), _max_value(max_value)
    {
        if(step < 0)
            throw std::invalid_argument("_step must be bigger than 0");
    }

    bool virtual Increment()
    {
        T next_value = _value + _step;
        JumpedOverLimitValue = next_value >= _max_value;

        if(JumpedOverLimitValue)
            _value = _min_value + (next_value  - _max_value);
        else
            _value = next_value;

        return JumpedOverLimitValue;
    }
    bool virtual Decrement()
    {
        T next_value = _value - _step;
        JumpedOverLimitValue = next_value <= _min_value;

        if(JumpedOverLimitValue)
            _value = _max_value - (_min_value  - next_value);
        else
            _value = next_value;

        return JumpedOverLimitValue;
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

public:
    TimerManager(QLabel* lb_min, QLabel* lb_sec);
    void ChangeMinutes(bool IsUp);
    void ChangeSeconds(bool IsUp);

    int GetSeconds();

};

#endif // TIMERMANAGER_H
