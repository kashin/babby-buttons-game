#include "shortcutsmodel.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QList>

#include "buttondata.h"

static const QLatin1String BUTTON_NAME_KEY("name");
static const QLatin1String BUTTON_COLOR_KEY("color");
static const QLatin1String BUTTON_IMAGE_SOURCE_KEY("imageSource");
static const QLatin1String BUTTON_SOUND_SORCE_KEY("soundSource");
static const QLatin1String BUTTON_SHORTCUT_KEY("shortcuts");
static const QLatin1String DEFAULT_SHORTCUTS_DATA_PATH("game_data.json");

ShortcutsModel::ShortcutsModel(QObject *parent)
    : QObject(parent)
{
}

QString ShortcutsModel::buttonName(int index)
{
    return (index >= 0 && index  < buttonsData.count()) ? buttonsData.at(index)->getName() : QString();
}

QString ShortcutsModel::buttonColor(int index)
{
    return (index >= 0 && index  < buttonsData.count()) ? buttonsData.at(index)->getColor() : QString();
}

QString ShortcutsModel::buttonSoundSource(int index)
{
    return (index >= 0 && index  < buttonsData.count()) ? buttonsData.at(index)->getSoundsSource() : QString();
}

QString ShortcutsModel::buttonImageSource(int index)
{
    return (index >= 0 && index  < buttonsData.count()) ? buttonsData.at(index)->getImageSource() : QString();
}

QStringList ShortcutsModel::buttonShortcuts(int index) const
{
    return (index >= 0 && index  < buttonsData.count()) ? buttonsData.at(index)->getShortcuts() : QStringList();
}

QStringList ShortcutsModel::getButtons() const
{
    return buttons;
}

void ShortcutsModel::loadShortcuts(const QString &dataPath)
{
    QString path = dataPath.isEmpty() ? DEFAULT_SHORTCUTS_DATA_PATH : dataPath;
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonArray buttons = doc.array();
    auto iter = buttons.begin();
    while (iter != buttons.end())
    {
        if (iter->isObject())
        {
            ButtonData *data = new ButtonData(this);
            auto object = iter->toObject();
            data->setName(object.value(BUTTON_NAME_KEY).toString());
            data->setColor(object.value(BUTTON_COLOR_KEY).toString());
            data->setImageSource(object.value(BUTTON_IMAGE_SOURCE_KEY).toString());
            data->setSoundsSource(object.value(BUTTON_SOUND_SORCE_KEY).toString());
            auto shortcutsArray = object.value(BUTTON_SHORTCUT_KEY).toArray();
            QStringList shortcutsSequences;
            auto shortcutsIter = shortcutsArray.begin();
            while (shortcutsIter != shortcutsArray.end())
            {
                shortcutsSequences << shortcutsIter->toString();
                shortcutsIter++;
            }
            data->setShortcuts(shortcutsSequences);
            buttonsData << data;
            addButton(data->getName());
        }
        iter++;
    }
    file.close();
}

void ShortcutsModel::addButton(const QString &newButton)
{
    buttons << newButton;
    emit buttonsChanged(buttons);
}
