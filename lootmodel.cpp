#include "lootmodel.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

LootModel::LootModel()
{
  count = 0;
}

int LootModel::rowCount(const QModelIndex &parent) const
{
  return count;
}

int LootModel::columnCount(const QModelIndex &parent) const
{
  return 2;
}

QVariant LootModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid() || role != Qt::DisplayRole)
    { return QVariant(); }

  return index.column() == 0 ? QVariant(names[index.row()]) : QVariant(
           counts[index.row()]);
}

QVariant LootModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
  if (role == Qt::DisplayRole)
    {
      if (orientation == Qt::Horizontal)
        {
          return section == 0 ? "Имя" : "Количество";
        }
      else
        {
          return section + 1;
        }
    }

  return QVariant();
}

void LootModel::loadData(QByteArray *jsonData)
{
  beginResetModel();
  QJsonDocument json;
  QJsonArray array;
  json = QJsonDocument::fromJson(*jsonData);
  array = json.array();
  count = array.size();
  counts.clear();
  names.clear();

  foreach (const QJsonValue value, array)
    {
      QJsonObject record = value.toObject();
      counts << record["count"].toInt();
      names << record["itemDesc"].toString();
    }

  endResetModel();
}
