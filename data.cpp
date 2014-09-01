#include "data.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>

Data::Data()
{
}

bool Data::LoadFile(QString filename)
{
    data.clear();

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        DataPoint_t dp;
        file.readLine();    //skip first line

        while (!file.atEnd())
        {
            QString line = file.readLine();
            QStringList list = line.split(QString(","));
            dp.energy = list[0].toFloat();
            dp.count = list[1].toInt();
            data.append(dp);
        }
        file.close();

        emit Loaded();

        return true;
    }
    else
    {
        return false;
    }
}

bool Data::SaveFile(QString filename)
{
    //dump data to file.
    QFile file(filename);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << "Energy (keV)," << "Counts" << endl;
        for (int idx = 0; idx < data.size(); idx++) {
            stream << data[idx].energy << "," << data[idx].count << endl;
        }
        file.close();

        return true;
    }
    else
    {
        return false;
    }
}

QVector<DataPoint_t> Data::GetData()
{
    return data;
}

DataPoint_t Data::GetDataIdx(int idx)
{
    return data[idx];
}

void Data::SetData(QVector<DataPoint_t> data)
{
    this->data = data;
}

void Data::SetDataIdx(int idx, DataPoint_t data)
{
    this->data[idx] = data;
}

void Data::RemoveData(int idx) {
    data.remove(idx);
}

void Data::AddData(int idx, DataPoint_t data)
{
    this->data.insert(idx, data);
}
