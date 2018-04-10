#ifndef PIZZA_H
#define PIZZA_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QPen>
#include <QPainter>
#include <QGridLayout>
#include <QComboBox>

class Pizza : public QWidget
{
    Q_OBJECT

public:
    Pizza(QWidget *parent = Q_NULLPTR);
    ~Pizza();

    void setAngulo(qreal angulo);
    void inserirSetor(qreal angulo);
    void inserirSetores(QVector<qreal> angulos);
    void inserirSetorCanhao(qreal angulo);
    void inserirSetoresCanhao(QVector<qreal> angulos);

private slots:
    void on_comboBox_change(int index);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    enum PixelsSize {
        PixelOffset = 40,
        MinimalSize = 150
    };

    int brushStyle = 0;
    qreal m_angulo = 0;
    QVector<qreal> m_angulos = { 0 };
    QVector<qreal> m_angulosCanhao = { 0 };
    QTimer *timer;
    QGridLayout *layout = nullptr;
    QComboBox *comboBox = nullptr;
};

#endif // PIZZA_H
