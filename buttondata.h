#ifndef BUTTONDATA_H
#define BUTTONDATA_H

#include <QObject>

class ButtonData : public QObject
{
    Q_OBJECT
public:
    explicit ButtonData(QObject *parent = nullptr);

    QString getName() const;
    void setName(const QString &value);

    QString getColor() const;
    void setColor(const QString &value);

    QString getImageSource() const;
    void setImageSource(const QString &value);

    QString getSoundsSource() const;
    void setSoundsSource(const QString &value);

    QString getShortcut() const;
    void setShortcut(const QString &value);

private:
    QString name;
    QString color;
    QString imageSource;
    QString soundsSource;
    QString shortcut;
};

#endif // BUTTONDATA_H
