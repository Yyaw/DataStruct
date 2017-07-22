#ifndef _READ_DATA_FROM_FILE
#define _READ_DATA_FROM_FILE

#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>

class ReadFile
{
  public:
    ReadFile(std::string filepath)
    {
        assert(fileIsExist(filepath));
        in = std::ifstream(filepath);
    }

    ~ReadFile()
    {
        in.close();
    }

    void readload(std::string filepath)
    {
        assert(fileIsExist(filepath));
        in.close();
        in = std::ifstream(filepath);
    }

    std::vector<std::vector<int>> readData()
    {
        std::vector<std::vector<int>> result;
        std::vector<int> line;

        while (!in.eof())
        {
            int size;
            int data;
            in >> size;
            for (int i = 0; i < size; i++)
            {
                if (!in.eof())
                {
                    in >> data;
                }
                line.push_back(data);
            }

            std::vector<int> r(line);
            result.push_back(r);
            line.clear();
        }
        return result;
    }

  private:
    std::ifstream in;
    bool fileIsExist(std::string filepath)
    {
        bool result = true;
        std::fstream file;
        file.open(filepath, std::ios::in);
        if (!file)
        {
            result = false;
        }
        return result;
    }
};

#endif