#include <iostream>
#include <vector>

// Function to perform steps 1 and 2 of Ford-Johnson algorithm
std::vector<int> fordJohnsonStep1and2(std::vector<int>& input) {
    int n = input.size();
    std::vector<int> result;

    for (int i = 0; i < n - 1; i += 2) {
        if (input[i] < input[i + 1]) {
            result.push_back(input[i]);
            result.push_back(input[i + 1]);
        } else {
            result.push_back(input[i + 1]);
            result.push_back(input[i]);
        }
    }

    // If there's an odd number of elements, add the last element
    if (n % 2 == 1) {
        result.push_back(input[n - 1]);
    }

    return result;
}

// Function to perform step 3 of Ford-Johnson algorithm
std::vector<int> fordJohnsonStep3(std::vector<int>& largerElements) {
    int n = largerElements.size();

    if (n <= 1) {
        return largerElements;
    }

    int mid = n / 2;
    std::vector<int> leftHalf(largerElements.begin(), largerElements.begin() + mid);
    std::vector<int> rightHalf(largerElements.begin() + mid, largerElements.end());

    leftHalf = fordJohnsonStep3(leftHalf);
    rightHalf = fordJohnsonStep3(rightHalf);

    std::vector<int> sorted;
    int leftIdx = 0;
    int rightIdx = 0;

    while (leftIdx < leftHalf.size() && rightIdx < rightHalf.size()) {
        if (leftHalf[leftIdx] < rightHalf[rightIdx]) {
            sorted.push_back(leftHalf[leftIdx]);
            leftIdx++;
        } else {
            sorted.push_back(rightHalf[rightIdx]);
            rightIdx++;
        }
    }

    while (leftIdx < leftHalf.size()) {
        sorted.push_back(leftHalf[leftIdx]);
        leftIdx++;
    }

    while (rightIdx < rightHalf.size()) {
        sorted.push_back(rightHalf[rightIdx]);
        rightIdx++;
    }

    return sorted;
}

// Function to perform step 4 and 5 of Ford-Johnson algorithm
std::vector<int> fordJohnsonStep4and5(std::vector<int>& sorted, int smallestElement, std::vector<int>& unpairedElements) {
    std::vector<int> result;
    result.push_back(smallestElement);

    int n = unpairedElements.size();

    for (int i = 0; i < n; i++) {
        int currentElement = unpairedElements[i];
        int j = 0;
        while (j < result.size() && result[j] < currentElement) {
            j++;
        }
        result.insert(result.begin() + j, currentElement);
    }

    return result;
}

int main() {
    std::vector<int> input = {9, 1, 78, 25, 66};

    // Step 1 and 2: Group into pairs and find the larger element
    std::vector<int> result1 = fordJohnsonStep1and2(input);

    // Step 3: Recursively sort the larger elements
    std::vector<int> result3 = fordJohnsonStep3(result1);

    // Step 4: Insert the smallest element from step 1
    int smallestElement = input[0];

    // Step 5: Insert the remaining unpaired elements
    std::vector<int> unpairedElements;
    for (int i = 1; i < input.size(); i += 2) {
        unpairedElements.push_back(input[i]);
    }
    std::vector<int> finalResult = fordJohnsonStep4and5(result3, smallestElement, unpairedElements);

    // Display the final sorted result
    for (int i = 0; i < finalResult.size(); i++) {
        std::cout << finalResult[i] << " ";
    }

    return 0;
}
