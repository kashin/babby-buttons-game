#ifndef SHORTCUTSMODEL_H
#define SHORTCUTSMODEL_H

#include <QObject>

class ButtonData;
class QTextToSpeech;

class ShortcutsModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList buttons READ getButtons NOTIFY buttonsChanged)
public:
    explicit ShortcutsModel(QObject *parent = nullptr);

    Q_INVOKABLE QString buttonName(int index);
    Q_INVOKABLE QString buttonColor(int index);
    Q_INVOKABLE QString buttonSoundSource(int index);
    Q_INVOKABLE QString buttonVoiceLine(int index);
    Q_INVOKABLE QString buttonImageSource(int index);
    Q_INVOKABLE QStringList buttonShortcuts(int index) const;
    QStringList getButtons() const;
    Q_INVOKABLE void loadShortcuts(const QString &dataPath);
    Q_INVOKABLE void say(const QString &line);
    void addButton(const QString &newButton);

private:
    const ButtonData *findButtonDataByIndex(int index) const;

signals:
    void buttonsChanged(QStringList buttons);

private:
    QStringList buttons;
    QList<ButtonData*> buttonsData;
    QTextToSpeech *voiceGenerator;
};

#endif // SHORTCUTSMODEL_H
