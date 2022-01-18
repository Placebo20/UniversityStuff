#include "timer.h"

Timer::Timer(QTime time, QLabel description)
{
    this->time = time;
    this->description = description.text();
}

Timer::Timer(QTime time, QString description)
{
    this->time = time;
    this->description = description;
}

QTime Timer::getTime()
{
    return time;
}

void Timer::setTime(QTime newTime)
{
    time = newTime;
}

QString Timer::getDesc()
{
    return description;
}

void Timer::setDesc(QString newDesc)
{
    description = newDesc;
}

void Timer::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
}

Timer::Timer()
{
    this->time.setHMS(0,0,0);
    this->description = "\0";
}
