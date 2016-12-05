#include "fieldwidget.h"

#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtGui/QPaintEvent>

#include <iostream>

FieldWidget::FieldWidget(QWidget * parent) : QWidget(parent)
{
    field = new Field();
}

void FieldWidget::resizeField(int width, int height)
{
    delete field;
    field = new Field(width, height);

    repaint();
}

void FieldWidget::paintEvent(QPaintEvent * event)
{
    QPainter p(this);

    QPen gridPen;
    if (cellSize <= 10)
    {
        gridPen = QPen(Qt::darkGray, 0, Qt::NoPen);
    }
    else if (cellSize <= 20)
    {
        gridPen = QPen(Qt::darkGray, 1, Qt::SolidLine);
    }
    else
    {
        gridPen = QPen(Qt::darkGray, 2, Qt::SolidLine);
        // For lines to hit pixels when antialiasing:
        //p.translate(0.5,0.5);
        p.setRenderHint(QPainter::Antialiasing);
    }

    QBrush backround(Qt::black);
    p.fillRect(0,0, this->width(), this->height(), backround);

    p.translate(cellOffset);

    DrawCells(p);
    DrawGrid(p, gridPen);
    DrawBorder(p);
}

void FieldWidget::DrawCells(QPainter & p)
{
    QPen myPen(Qt::darkGray, 0, Qt::NoPen);
    p.setPen(myPen);

    QBrush head(Qt::blue);
    QBrush tail(Qt::red);
    QBrush conductor(Qt::yellow);

    for (int x = 0; x < field->getWidth(); ++x)
    {
        for (int y = 0; y < field->getHeight(); ++y)
        {
            QRectF cell(x * cellSize,
                        y * cellSize,
                        cellSize, cellSize);
            if (field->getCell(x, y) == 1)
            {
                p.fillRect(cell, head);
            }
            else if (field->getCell(x, y) == 2)
            {
                p.fillRect(cell, tail);
            }
            else if (field->getCell(x, y) == 3)
            {
                p.fillRect(cell, conductor);
            }
        }
    }
}

void FieldWidget::DrawGrid(QPainter & p, QPen pen)
{
    p.setPen(pen);

    int fieldWidth = field->getWidth() * cellSize;
    int fieldHeight = field->getHeight() * cellSize;

    for (int x = 0; x < field->getWidth() + 1; ++x)
    {
        QLineF line(x * cellSize,
                    0,
                    x * cellSize,
                    fieldHeight);
        p.drawLine(line);
    }

    for (int y = 0; y < field->getHeight() + 1; ++y)
    {
        QLineF line(0,
                    y * cellSize,
                    fieldWidth,
                    y * cellSize);
        p.drawLine(line);
    }
}

void FieldWidget::DrawBorder(QPainter &p)
{
    int fieldWidth = field->getWidth() * cellSize;
    int fieldHeight = field->getHeight() * cellSize;

    QPen myPen(Qt::red, 4, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    p.setPen(myPen);
    QBrush myBrush(Qt::NoBrush);
    p.setBrush(myBrush);

    p.drawRect(-5, -5, fieldWidth+10, fieldHeight+10);
}

void FieldWidget::LoadField(QString file)
{
    QImage image(file);

    delete field;
    field = new Field(image.width(), image.height());


    for (int x = 0; x < field->getWidth(); ++x)
    {
        for (int y = 0; y < field->getHeight(); ++y)
        {
            QColor c = image.pixelColor(x,y);

            if(c == Qt::blue)
            {
                field->setCell(x, y, 1);
            }
            else if(c == Qt::red)
            {
                field->setCell(x, y, 2);
            }
            else if(c == Qt::yellow)
            {
                field->setCell(x, y, 3);
            }
            else
            {
                field->setCell(x, y, 0);
            }
        }
    }

    repaint();
}

void FieldWidget::SaveField(QString file)
{
    QImage image(field->getWidth(), field->getHeight(), QImage::Format_RGB32);

    for (int x = 0; x < field->getWidth(); ++x)
    {
        for (int y = 0; y < field->getHeight(); ++y)
        {
            switch (field->getCell(x, y)) {
            case 0:
                image.setPixelColor(x,y, Qt::black);
                break;
            case 1:
                image.setPixelColor(x,y, Qt::blue);
                break;
            case 2:
                image.setPixelColor(x,y, Qt::red);
                break;
            case 3:
                image.setPixelColor(x,y, Qt::yellow);
                break;
            }
        }
    }

    if (file.endsWith(".bmp"))
        image.save(file);
    else
        image.save(file+".bmp");
}

void FieldWidget::mouseMoveEvent(QMouseEvent *event)
{
    mousePosition = event->pos();

    cellOffset += mousePosition - previousMousePosition;

    previousMousePosition = mousePosition;

    repaint();
}

void FieldWidget::mousePressEvent(QMouseEvent *event)
{
    mousePosition = event->pos();
    previousMousePosition = mousePosition;
}

QPoint FieldWidget::screenToWorld(QPoint screenCoordinates) const
{
    QPoint worldCoordinates = screenCoordinates;
    worldCoordinates -= cellOffset;
    worldCoordinates.setX(worldCoordinates.x() / cellSize);
    worldCoordinates.setY(worldCoordinates.y() / cellSize);

    return worldCoordinates;
}

void FieldWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mousePosition = event->pos();

    QPoint worldCoordinates = screenToWorld(mousePosition);

    if (worldCoordinates.x() >= 0 &&
            worldCoordinates.y() >= 0 &&
            worldCoordinates.x() < field->getWidth() &&
            worldCoordinates.y() < field->getHeight())
    {
        if (event->button() == Qt::LeftButton)
        {
            field->invertCell(worldCoordinates.x(), worldCoordinates.y(), -1);
        }
        else if (event->button() == Qt::RightButton)
        {
            field->invertCell(worldCoordinates.x(), worldCoordinates.y(), 1);
        }
    }

    repaint();
}
