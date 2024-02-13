#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>

std::vector<std::string> IntoWords(const std::string &text)
{
    std::vector<std::string> words;
    std::istringstream iss(text);
    std::string word;
    while (iss >> word)
    {
        words.push_back(word);
    }

    return words;
}

std::vector<std::string> base_word(const std::string &text)
{
    std::string word;
    std::vector<std::string> words;
    for (int i = 0; i < text.size(); ++i)
    {

        if (text[i] == '<')
        {
            word.clear();
        }
        else if (text[i] == '>')
        {
            words.push_back(word);
        }
        else if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            word.push_back(text[i]);
        }
    }
    return words;
}

std::string vec_to_string(std::vector<std::string> &str)
{
    std::string ans;
    for (auto word : str)
    {
        ans += " " + word;
    }
    return ans;
}

void writeJsonOutput(const std::string &filename, const std::string &input, const std::map<std::string, int> &nameCount)
{
    std::ofstream ofs(filename);
    if (!ofs.is_open())
    {
        std::cout << "Error: Unable to open file " << filename << std::endl;
        return;
    }
    ofs << "{\n";
    ofs << "  \"Text\": \"" << input << "\",\n";
    ofs << "  \"ProperNouns\": {\n";
    for (auto it = nameCount.begin(); it != nameCount.end(); ++it)
    {
        ofs << "    \"" << it->first << "\": " << it->second;
        if (std::next(it) != nameCount.end())
        {
            ofs << ",\n";
        }
        else
        {
            ofs << "\n";
        }
    }
    ofs << "  }\n";
    ofs << "}\n";
    ofs.close();
}
