#ifndef SQUARE_HPP
#define SQUARE_HPP

class Square {
    private:
        int line;
        int column;

    public:
        Square(int line, int column);

        int getLine() const;
        int getColumn() const;
};

#endif
