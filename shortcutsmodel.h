#ifndef SHORTCUTSMODEL_H
#define SHORTCUTSMODEL_H

#include <QObject>

class ShortcutsModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList shortcuts READ getShortcuts NOTIFY shortcutsChanged)
public:
    explicit ShortcutsModel(QObject *parent = nullptr);

    QStringList getShortcuts() const;
    void setShortcuts(const QStringList &value);

signals:
    void shortcutsChanged(QStringList shortcuts);

private:
    QStringList shortcuts;
};

#endif // SHORTCUTSMODEL_H
