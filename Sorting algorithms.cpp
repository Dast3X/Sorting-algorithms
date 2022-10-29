#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>


std::string DATASET_FILE = "dataset-titanic.csv";

void InsertionSort(std::string arr[], int len)
{
    for (int i = 1; i < len; i++)
    {
        for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--)
        {
            std::string temp = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = temp;
        }
    }
    
}

void EvenOddSort(std::string arr[], int len)
{
    bool sorted = 0;
    while (!sorted)
    {
        sorted = true;
        for (int i = 0; i < len-1; i+=2)
        {
            if (arr[i] > arr[i + 1])
            {
                std::string temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                sorted = false;
            }
        }
        for (int i = 1; i < len - 1; i += 2)
        {
            if (arr[i] > arr[i + 1])
            {
                std::string temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                sorted = false;
            }
        }
     }
}

void Reader(std::string lines[], int len)
{
    std::fstream file;
    file.open(DATASET_FILE, std::ios::in);
    if (!file.is_open())
       throw std::exception("Error\n");
    for (int i = 0; i < len; i++)
    {
        std::getline(file, lines[i]);
    }
    file.close();
}

int main(int argc, char* argv[])
{
    std::string lines[100];
    int repetition = 10;
    int len = sizeof(lines) / sizeof(lines[0]);

 

    std::vector<int> insertionTime;
    std::vector<int> evenOddTime;
   

    for (int i = 0; i < repetition; i++)
    {
        Reader(lines, len);
        auto start = std::chrono::steady_clock::now();
        InsertionSort(lines, len);
        auto finish = std::chrono::steady_clock::now();
        insertionTime.push_back((int)std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count());
    }
    std::sort(insertionTime.begin(), insertionTime.end());

    std::cout << "Time to do something Insertion sort:\n[ ";
    for (const auto& i : insertionTime)
        std::cout << i << " ";
    std::cout << "] - microsec\n\n";


    for (int i = 0; i < repetition; i++)
    {
        Reader(lines, len);
        auto start = std::chrono::steady_clock::now();
        EvenOddSort(lines, len);
        auto finish = std::chrono::steady_clock::now();
        evenOddTime.push_back((int)std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count());
    }

    std::sort(evenOddTime.begin(), evenOddTime.end());
    std::cout << "\nTime to do something Even/odd sort:\n[ ";
    for (const auto& i : evenOddTime)
        std::cout << i << " ";
    std::cout << "] - microsec\n\n";
    return 0;
}