#include "dominolinebuilder.h"

Domino::Domino(std::string theBlueSymbol, std::string theRedSymbol)
{
    blueSymbol = theBlueSymbol;
    redSymbol = theRedSymbol;
}

DominoLineBuilder::DominoLineBuilder(unsigned long int totalNumberOfDominoes, std::istream& dominoInputData)
{
    for (unsigned long int i = 0; i < totalNumberOfDominoes; ++i)
    {
        std::string aBlueSymbol, aRedSymbol;
        std::getline(dominoInputData, aBlueSymbol, ':');
        std::getline(dominoInputData, aRedSymbol, '\n');

        Domino* newDomino = new Domino(aBlueSymbol,aRedSymbol);
        newDomino->previous = lastDisorderedDomino;
        lastDisorderedDomino = newDomino;

        //Inserting the domino with the blue symbol as the key and a pointer to the current domnino as a value
        dominoMap.insert( {aBlueSymbol, newDomino} );
    }
}

bool DominoLineBuilder::nextRight()
{
    if (orderedLine.empty())
    {
        orderedLine.push_back(*lastDisorderedDomino);
        dominoMap.erase(lastDisorderedDomino->blueSymbol);
        delete lastDisorderedDomino;
        lastDisorderedDomino = lastDisorderedDomino->previous;
        return true;
    }

    std::string targetSymbol = orderedLine.back().redSymbol;

    auto location = dominoMap.find(targetSymbol);

    if (location != dominoMap.end()) {
        Domino* matchingDomino = location->second;
        orderedLine.push_back(*matchingDomino);
        dominoMap.erase(location);
        if (lastDisorderedDomino == matchingDomino)
        {
            lastDisorderedDomino = matchingDomino->previous;
        }
        return true;
    }

    return false;
}

void DominoLineBuilder::display(std::ostream& outputStream)
{
    for (Domino eachDomino : orderedLine)
    {
        outputStream << eachDomino.blueSymbol << ':' << eachDomino.redSymbol << ' ';
    }
}

DominoLineBuilder::~DominoLineBuilder()
{
    Domino* currentDomino = lastDisorderedDomino;
    while (currentDomino != nullptr)
    {
        Domino* dominoToDelete = currentDomino;
        currentDomino = currentDomino->previous;
        delete dominoToDelete;
    }
}

