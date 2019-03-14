#ifndef LOOTMODEL_H
#define LOOTMODEL_H

#include <QAbstractTableModel>

class LootModel : public QAbstractTableModel {
  public:
    LootModel();

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const override;

    void loadData(QByteArray *jsonData);

  private:
    int count;
    QList<int> counts;
    QStringList names;

};

#endif // LOOTMODEL_H
