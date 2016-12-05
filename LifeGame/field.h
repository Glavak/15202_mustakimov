#ifndef FIELD_H
#define FIELD_H


class Field
{
public:
    Field(int width = 15, int height = 15);

    char getCell(int x, int y) const;
    void setCell(int x, int y, char value);
    void invertCell(int x, int y, char direction);

    void clearField();
    void randomizeField();

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void step(int count);

private:
    int width;
    int height;

    int getElectronHeadsCount(int x, int y) const;
    void stepOnce();

    char * cells;
};

#endif // FIELD_H
