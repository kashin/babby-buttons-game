#include "buttondata.h"

ButtonData::ButtonData(QObject *parent)
    : QObject(parent)
{

}

QString ButtonData::getName() const
{
    return name;
}

void ButtonData::setName(const QString &value)
{
    name = value;
}

QString ButtonData::getColor() const
{
    return color;
}

void ButtonData::setColor(const QString &value)
{
    color = value;
}

QString ButtonData::getImageSource() const
{
    return imageSource;
}

void ButtonData::setImageSource(const QString &value)
{
    imageSource = value;
}

QString ButtonData::getSoundsSource() const
{
    return soundsSource;
}

void ButtonData::setSoundsSource(const QString &value)
{
    soundsSource = value;
}

QString ButtonData::getShortcut() const
{
    return shortcut;
}

void ButtonData::setShortcut(const QString &value)
{
    shortcut = value;
}
