#ifndef HASHFIELD_H
#define HASHFIELD_H


class HashField
{
public:
    HashField(int width = 15, int height = 15);

    bool getCell(int x, int y) const;
    void setCell(int x, int y, bool value);
    void invertCell(int x, int y);

    void clearField();
    void randomizeField();

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void step(int count);

private:
    int width;
    int height;

    int getNeighboursCount(int x, int y) const;
    void stepOnce();

    bool * cells;
};

#endif // HASHFIELD_H
