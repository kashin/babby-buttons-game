#ifndef SHORTCUTSMODEL_H
#define SHORTCUTSMODEL_H

#include <QObject>

class ButtonData;

class ShortcutsModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList shortcuts READ getShortcuts NOTIFY shortcutsChanged)
public:
    explicit ShortcutsModel(QObject *parent = nullptr);

    Q_INVOKABLE QString buttonName(int index);
    Q_INVOKABLE QString buttonColor(int index);
    Q_INVOKABLE void loadShortcuts(const QString &dataPath);
    QStringList getShortcuts() const;
    void setShortcuts(const QStringList &value);
    void addShortcut(const QString &newShortcut);

signals:
    void shortcutsChanged(QStringList shortcuts);

private:
    QStringList shortcuts;
    QList<ButtonData*> buttonsData;
};

#endif // SHORTCUTSMODEL_H
