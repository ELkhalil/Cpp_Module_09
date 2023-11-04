#include <iostream>
#include <vector>
#include <algorithm>

// Custom comparator to sort pairs by the second element in descending order
struct PairComparator
{
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second > b.second;
    }
};

// Function to insert an element into a sorted sequence using binary search
void insertElement(std::vector<int>& sequence, int element)
{
    // Find the insertion point using binary search
    std::vector<int>::iterator it = std::lower_bound(sequence.begin(), sequence.end(), element);
    // Insert the element at the found position
    sequence.insert(it, element);
}

// Step 1: Split the input elements into pairs
std::vector<std::pair<int, int> > splitIntoPairs(const std::vector<int>& elements)
{
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i < elements.size(); i += 2) {
        // Create pairs with two elements, or one element with -1 to indicate unpaired
        if (i + 1 < elements.size()) {
            pairs.push_back(std::make_pair(elements[i], elements[i + 1]));
        } else {
            pairs.push_back(std::make_pair(elements[i], -1));
        }
    }
    return pairs;
}

// Step 2: Sort the pairs and ensure the first element is smaller
std::vector<std::pair<int, int> > sortPairs(const std::vector<std::pair<int, int> >& pairs)
{

    std::vector<std::pair<int, int> > sortedPairs = pairs;
    for (size_t i = 0; i < sortedPairs.size(); ++i)
    {
        if (sortedPairs[i].second != -1 && sortedPairs[i].first > sortedPairs[i].second) 
        {
            int temp = sortedPairs[i].first;
            sortedPairs[i].first = sortedPairs[i].second;
            sortedPairs[i].second = temp;
        }
    }
    return sortedPairs;
}

// Step 3: Recursively sort the larger elements from each pair
void sortByLargerValue(std::vector<std::pair<int, int> >& sortedPairs)
{
    // Use std::sort to sort pairs by the second element (larger)
    std::sort(sortedPairs.begin(), sortedPairs.end(), PairComparator());
}

// Step 4 and 5: Merge and insertion sort
std::vector<int> mergeInsertionSort(const std::vector<int>& elements)
{
    std::vector<std::pair<int, int> > pairs = splitIntoPairs(elements);
    std::vector<std::pair<int, int> > sortedPairs = sortPairs(pairs);
    
    sortByLargerValue(sortedPairs);
    
    std::vector<int> sortedSequence;
    
    for (size_t i = 0; i < sortedPairs.size(); ++i)
    {
        insertElement(sortedSequence, sortedPairs[i].first);
        if (sortedPairs[i].second != -1) {
            insertElement(sortedSequence, sortedPairs[i].second);
        }
    }
    
    return sortedSequence;
}

int main()
{
    int                     unsortedArr[] = {8, 9, 2, 3, 7, 5, 11, 13};
    std::vector<int>        unsorted(unsortedArr, unsortedArr + sizeof(unsortedArr) / sizeof(int));
    
    // Sort the unsorted array using Merge-Insertion Sort
    std::vector<int> sorted = mergeInsertionSort(unsorted);
    
    // Print the unsorted and sorted arrays
    std::cout << "Unsorted array: ";
    for (size_t i = 0; i < unsorted.size(); ++i) {
        std::cout << unsorted[i] << " ";
    }
    std::cout << "\n";
    
    std::cout << "Sorted array: ";
    for (size_t i = 0; i < sorted.size(); ++i) {
        std::cout << sorted[i] << " ";
    }
    std::cout << "\n";
    return 0;
}
