#include "pizza.h"

#include <QPen>
#include <QPainter>
#include <QtCore/QtMath>
#include <QPaintEvent>
#include <QDebug>

Pizza::Pizza(QWidget *parent) :
    QWidget(parent)
{
    m_angulos.clear();
    setMinimumSize(MinimalSize, MinimalSize);

    layout = new QGridLayout(this);

    comboBox = new QComboBox(this);

    connect(comboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(on_comboBox_change(int)));

    comboBox->addItem("NoBrush");
    comboBox->addItem("SolidPattern");
    comboBox->addItem("Dense1Pattern");
    comboBox->addItem("Dense2Pattern");
    comboBox->addItem("Dense3Pattern");
    comboBox->addItem("Dense4Pattern");
    comboBox->addItem("Dense5Pattern");
    comboBox->addItem("Dense6Pattern");
    comboBox->addItem("Dense7Pattern");
    comboBox->addItem("HorPattern");
    comboBox->addItem("VerPattern");
    comboBox->addItem("CrossPattern");
    comboBox->addItem("BDiagPattern");
    comboBox->addItem("FDiagPattern");
    comboBox->addItem("DiagCrossPattern");
    comboBox->addItem("LinearGradientPattern");
    comboBox->addItem("RadialGradientPattern");
    comboBox->addItem("ConicalGradientPattern");
    comboBox->addItem("TexturePattern");

    layout->addWidget(comboBox, 0, 0, 1, 1, Qt::AlignCenter);

    setLayout(layout);
}

Pizza::~Pizza()
{
}

void Pizza::setAngulo(qreal angulo)
{
    m_angulo = angulo;
}

void Pizza::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    QPen pen;
    QBrush brush;

    int cor = Qt::darkRed;
    painter.setRenderHint(QPainter::Antialiasing, true);

    qreal m_size = width() < height() ? width() : height();
    qreal m_centroh = height() / 2;
    qreal m_centrow = width() / 2;
    qreal sum = 0;
    qreal angOffset = -90;
    QRect rec;


    //// Desenho do Canhao
    brush.setStyle(Qt::BrushStyle(brushStyle));
    rec.setWidth(m_size);
    rec.setHeight(m_size);
    rec.moveCenter(QPoint(m_centrow, m_centroh));
    sum = 0;

    for (const auto i : m_angulosCanhao)
    {
        pen.setColor((Qt::GlobalColor) cor);
        brush.setColor((Qt::GlobalColor) cor);
        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawPie(rec, (sum + angOffset) * -16, i * -16);
        sum += i;
        ++cor;
    }
    ////

    //// Desenho do Setor
    brush.setStyle(Qt::SolidPattern);
    rec.setWidth(m_size - 2 * PixelOffset);
    rec.setHeight(m_size - 2 * PixelOffset);
    rec.moveCenter(QPoint(m_centrow, m_centroh));
    sum = 0;

    for (const auto i : m_angulos)
    {
        pen.setColor((Qt::GlobalColor) cor);
        brush.setColor((Qt::GlobalColor) cor);
        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawPie(rec, (sum + angOffset) * -16, i * -16);
        sum += i;
        ++cor;
    }
    ////

    //// Desenho do Setor Restrito
    if (sum < 360)
    {
        pen.setColor(Qt::gray);
        brush.setColor(Qt::gray);
        painter.setBrush(brush);
        painter.setPen(pen);
        painter.drawPie(rec, (sum + angOffset) * -16, (360 - sum) * -16);
    }
    ////

    //// Desenho da Posicao
    qreal m_anguloAux = m_angulo - angOffset;
    qreal p_aux = (m_centroh < m_centrow ? m_centroh : m_centrow) - PixelOffset;
    qreal co = qSin(qDegreesToRadians(m_anguloAux)) * p_aux;
    qreal ca = qCos(qDegreesToRadians(m_anguloAux)) * p_aux;
    qreal pos_x = m_centrow - ca;
    qreal pos_y = m_centroh - co;

    QPointF fim(pos_x, pos_y);
    QPointF centro(m_centrow, m_centroh);

    pen.setWidth(3);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawLine(centro, fim);
    ////
}

void Pizza::inserirSetor(qreal angulo)
{
    m_angulos.push_back(angulo);
}

void Pizza::inserirSetorCanhao(qreal angulo)
{
    m_angulosCanhao.push_back(angulo);
}

void Pizza::inserirSetores(QVector<qreal> angulos)
{
    m_angulos.clear();

    for (const auto i : angulos)
        m_angulos.push_back(i);
}

void Pizza::inserirSetoresCanhao(QVector<qreal> angulos)
{
    m_angulosCanhao.clear();

    for(const auto i : angulos)
        m_angulosCanhao.push_back(i);
}

void Pizza::on_comboBox_change(int index)
{
    brushStyle = index;
    repaint();
}
