#ifndef SHORTCUTSMODEL_H
#define SHORTCUTSMODEL_H

#include <QObject>

class ButtonData;

class ShortcutsModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList buttons READ getButtons NOTIFY buttonsChanged)
public:
    explicit ShortcutsModel(QObject *parent = nullptr);

    Q_INVOKABLE QString buttonName(int index);
    Q_INVOKABLE QString buttonColor(int index);
    Q_INVOKABLE QString buttonSoundSource(int index);
    Q_INVOKABLE QString buttonImageSource(int index);
    Q_INVOKABLE QStringList buttonShortcuts(int index) const;
    QStringList getButtons() const;
    Q_INVOKABLE void loadShortcuts(const QString &dataPath);
    void addButton(const QString &newButton);

signals:
    void buttonsChanged(QStringList buttons);

private:
    QStringList buttons;
    QList<ButtonData*> buttonsData;
};

#endif // SHORTCUTSMODEL_H
