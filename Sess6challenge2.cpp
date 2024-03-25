#include <iostream>  
#include <vector>  
using std::cout, std::endl, std::vector;
vector<int> addVectors(const vector<int>& vec1, const vector<int>& vec2)  {  
    // Check if the vectors have the same size  
    if (vec1.size() != vec2.size())  {  
        std::cout << "Error: Vectors must have the same size to add them." << std::endl;  
        return std::vector<int>();  
    }  
  
    // Create a vector to store the result  
    std::vector<int> result(vec1.size());  
  
    // Add the elements of vec1 and vec2 and store the result in result  
    for (int i = 0; i < vec1.size(); i++)  
    {  
        result[i] = vec1[i] + vec2[i];  
    }  
  
    return result;  
}  
  
int main()  
{  
    // Create two vectors  
    std::vector<int> vecOne = {1, 2, 3, 4, 5};  
    std::vector<int> vecTwo = {5, 4, 3, 2, 1};  
  
    // Add the two vectors  
    std::vector<int> result = addVectors(vecOne, vecTwo);  
  
    // Print the result  
    std::cout << "The result of adding the two vectors is: {";  
    for (int i = 0; i < result.size(); i++)  
    {  
        std::cout << result[i];  
        if (i != result.size() - 1)  
        {  
            std::cout << ", ";  
        }  
    }  
    std::cout << "}" << std::endl;  
  
    return 0;  
}  