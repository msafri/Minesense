#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QVector>

/* This is the model part of the MVC pattern. */

typedef struct {
    float energy;
    int count;
} DataPoint_t;

class Data : public QObject
{
    Q_OBJECT

public:
    Data();
    bool LoadFile(QString filename);
    bool SaveFile(QString filename);
    QVector<DataPoint_t> GetData();
    DataPoint_t GetDataIdx(int idx);
    void SetData(QVector<DataPoint_t> data);
    void SetDataIdx(int idx, DataPoint_t data);
    void RemoveData(int idx);
    void AddData(int idx, DataPoint_t data);
    int count() { return data.size(); }
    void clear() { data.clear(); }

private:
    QVector<DataPoint_t> data;

signals:
    void Loaded();
    void Saved();
    void Updated(int);  // Update to index
    void Removed(int);  // Removed data at index
};

#endif // DATA_H
