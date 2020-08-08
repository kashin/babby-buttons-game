#include "shortcutsmodel.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>

ShortcutsModel::ShortcutsModel(QObject *parent)
    : QObject(parent)
{
    QFile file("shortcuts.json");
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
}

QStringList ShortcutsModel::getShortcuts() const
{
    return shortcuts;
}

void ShortcutsModel::setShortcuts(const QStringList &value)
{
    shortcuts = value;
    emit shortcutsChanged(value);
}
