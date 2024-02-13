#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Functions.hpp"

int main()
{
    std::string line2;
    std::string f2_name = "database.txt";
    std::ifstream file(f2_name);
    std::string all_file_info;
    if (!file.is_open())
    {
        std::cout << "Error:" << std::endl;
        return 1;
    }
    while (std::getline(file, line2))
    {
        all_file_info += line2;
    }
    file.close();

    std::vector<std::string> base_words = base_word(all_file_info);

    std::string line;
    std::string f_name = "input.txt";
    std::ifstream file2(f_name);
    std::map<std::string, int> output_map;
    if (!file2.is_open())
    {
        std::cout << "Error:" << std::endl;
        return 1;
    }

    std::string jsonText;

    while (std::getline(file2, line))
    {
        std::vector<std::string> vec = IntoWords(line);

        for (int i = 0; i < vec.size(); ++i)
        {
            char tmp = 'X';

            if (!vec[i].empty())
            {
                if (vec[i][vec[i].size() - 1] < 'a' || vec[i][vec[i].size() - 1] > 'z')
                {
                    tmp = vec[i][vec[i].size() - 1];
                    vec[i].pop_back();
                }

                std::string word = vec[i];
                if (word[0] >= 'A' && word[0] <= 'Z')
                {
                    for (auto w : base_words)
                    {
                        if (w == word)
                        {
                            vec[i] = "<O>";
                            if (output_map.count(word) == 0)
                            {
                                output_map.insert({word, 1});
                            }
                            else
                            {
                                output_map[word]++;
                            }
                            break;
                        }
                    }
                }
            }
            if (tmp != 'X')
            {
                vec[i].push_back(tmp);
            }
        }
        jsonText += vec_to_string(vec);
    }
    std::cout << jsonText << std::endl;
    for (auto p : output_map)
    {
        std::cout << p.first << "  " << p.second << "\n";
    }

    file2.close();
    writeJsonOutput("output.json", jsonText, output_map);
}