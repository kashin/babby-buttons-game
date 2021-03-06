#include "shortcutsmodel.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QList>
#include <QTextToSpeech>
#include <QDebug>

#include "buttondata.h"

static const QLatin1String BUTTON_NAME_KEY("name");
static const QLatin1String BUTTON_COLOR_KEY("color");
static const QLatin1String BUTTON_IMAGE_SOURCE_KEY("imageSource");
static const QLatin1String BUTTON_SOUND_SORCE_KEY("soundSource");
static const QLatin1String BUTTON_VOICE_LINE_KEY("voiceLine");
static const QLatin1String BUTTON_SHORTCUT_KEY("shortcuts");
static const QLatin1String DEFAULT_SHORTCUTS_DATA_PATH("game_data.json");
static const QLatin1String DATA_PATH_KEY("dataPath");
static const QLatin1String DATA_KEY("data");

ShortcutsModel::ShortcutsModel(QObject *parent)
    : QObject(parent),
      voiceGenerator(new QTextToSpeech(this))
{
}

QString ShortcutsModel::buttonName(int index)
{
    auto button = findButtonDataByIndex(index);
    return button ? button->getName() : QString();
}

QString ShortcutsModel::buttonColor(int index)
{
    auto button = findButtonDataByIndex(index);
    return button ? button->getColor() : QString();
}

QString ShortcutsModel::buttonSoundSource(int index)
{
    auto button = findButtonDataByIndex(index);
    QString result = button ? button->getSoundsSource() : QString();
    if (!result.startsWith("qrc:/") && !result.isEmpty())
    {
        result.prepend(pathToData);
    }
    return result;
}

QString ShortcutsModel::buttonVoiceLine(int index)
{
    auto button = findButtonDataByIndex(index);
    return button ? button->getVoiceLine() : QString();
}

QString ShortcutsModel::buttonImageSource(int index)
{
    auto button = findButtonDataByIndex(index);
    QString result = button ? button->getImageSource() : QString();
    if (!result.startsWith("qrc:/") && !result.isEmpty())
    {
        result.prepend(pathToData);
    }
    return result;
}

QStringList ShortcutsModel::buttonShortcuts(int index) const
{
    auto button = findButtonDataByIndex(index);
    return button ? button->getShortcuts() : QStringList();
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
    QJsonObject mainObject = doc.object();
    pathToData = mainObject.value(DATA_PATH_KEY).toString();
    QJsonArray buttons = mainObject.value(DATA_KEY).toArray();
    auto iter = buttons.begin();
    while (iter != buttons.end())
    {
        if (iter->isObject())
        {
            ButtonData *data = new ButtonData(this);
            auto object = iter->toObject();
            data->setName(object.value(BUTTON_NAME_KEY).toString());
            data->setColor(object.value(BUTTON_COLOR_KEY).toString());
            data->setVoiceLine(object.value(BUTTON_VOICE_LINE_KEY).toString());
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

void ShortcutsModel::say(const QString &line)
{
    if (!voiceGenerator || voiceGenerator->state() == QTextToSpeech::BackendError)
    {
        qWarning() << "Voice generator is not available:" << voiceGenerator->availableEngines() << voiceGenerator->availableLocales() << voiceGenerator->availableVoices().size();
        return;
    }
    voiceGenerator->say(line);
}

void ShortcutsModel::addButton(const QString &newButton)
{
    buttons << newButton;
    emit buttonsChanged(buttons);
}

const ButtonData *ShortcutsModel::findButtonDataByIndex(int index) const
{
    return (index >= 0 && index  < buttonsData.count()) ? buttonsData.at(index) : nullptr;
}
