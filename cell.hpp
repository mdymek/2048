class Cell {
private:
    friend class Map;
    int val;
    bool changed;
public:
    Cell();
    ~Cell();

    void setVal(int);
    int value() const;

    void change();
    void unchange();

    bool unchanged();
};
