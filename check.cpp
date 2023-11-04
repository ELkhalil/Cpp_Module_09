#include <iostream>
#include <vector>
#include <utility>
#include <unistd.h>
#include <sstream>
#include <list>
#include <limits>

// do not forget the idea of the simulation


std::vector<unsigned int>    mergeInsertionSort( std::vector< unsigned int> const& input )
{
    std::vector<unsigned int> original = input;
    unsigned int unpaired_element = -1;
    std::vector<unsigned int > X;
    std::vector<unsigned int > S;
    std::pair<unsigned int, unsigned int> tmpPair;

    if (original.size() <= 1)
        return original;
    if (original.size() % 2 != 0)
    {
        unpaired_element = original.back();
        original.pop_back();
    }

    /*  Step 1 && 2 : split data into pairs and compare to swap */
    for (int i = 0; i < original.size() ; i+=2)
    {
        if (i + 1 <= original.size())
        {
            tmpPair = std::make_pair(original[i], original[i + 1]);
            if (tmpPair.first > tmpPair.second)
                std::swap(tmpPair.first, tmpPair.second);
            X.push_back(tmpPair.first);
            S.push_back(tmpPair.second);
        }
    }

    /* step 3: sort the bigger elements vector */
    std::vector<unsigned int>::iterator it_begin = S.begin();
    std::vector<unsigned int>::iterator it_end = S.end();
    std::sort(it_begin, it_end);

    /* step 4: insert elements from the initial X to the new sequence at it's position */
    for(int i = 0; i < X.size(); i++)
    {
        // perform binary search and insert element at the extacted position
        std::vector<unsigned int>::iterator it_pos = std::lower_bound(S.begin(), S.end(), X[i]);
        // insert element at the founded position
        S.insert(it_pos, X[i]);
    }

    /* step 5: insert the odd element if any */
    if (unpaired_element != -1)
    {
        std::vector<unsigned int>::iterator it_pos = std::lower_bound(S.begin(), S.end(), unpaired_element);
        S.insert(it_pos, unpaired_element);
    }
    return S;
}



void    _errorExit( void )
{
    std::cout << "Error" << std::endl;\
    _exit(1);
}

unsigned int     _stringToInt( std::string const& input)
{
    std::istringstream iss(input);
    unsigned long value;

    iss >> value;

    if (iss.fail() || !iss.eof() || value < 0)
        _errorExit();
    if (value > std::numeric_limits<unsigned int>::max() || value < std::numeric_limits<unsigned int>::min())
        _errorExit();
    return static_cast<unsigned int>(value);
}

int main(int ac, char *av[])
{
    if (ac < 2)
    {
        std::cout << "Error" << std::endl;
        return 1;
    }
    std::vector<unsigned int>    inputSequence;
    for (int i = 1; i < ac; i++)
    {
        std::string input = av[i];
        inputSequence.push_back(_stringToInt(input));
    }
    std::cout << "before:   ";
    for (size_t i = 0; i < inputSequence.size(); ++i)
    {
        std::cout << inputSequence[i] << " ";
    }

    std::vector<unsigned int> newVec = mergeInsertionSort( inputSequence );

    std::cout << std::endl;

    std::cout << "After:    ";
    for (size_t i = 0; i < newVec.size(); ++i)
    {
        std::cout << newVec[i] << " ";
    }
    std::cout << "\n";


    return 0;
}