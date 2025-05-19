#ifndef DOMINOLINEBUILDER_H
#define DOMINOLINEBUILDER_H

#include <iostream>
#include <vector>
#include <unordered_map>

struct Domino
{
    std::string blueSymbol;
    std::string redSymbol;
    Domino* previous = nullptr;

    Domino(std::string theBlueSymbol, std::string theRedSymbol);
};

class DominoLineBuilder
{
public:
    DominoLineBuilder(unsigned long int totalNumberOfDominoes, std::istream& dominoInputData);
    bool nextRight();
    void display(std::ostream& theOutputStream);

    ~DominoLineBuilder();

private:
    Domino* lastDisorderedDomino = nullptr;
    std::vector<Domino> orderedLine;
    std::unordered_map<std::string, Domino*> dominoMap;
};

#endif
