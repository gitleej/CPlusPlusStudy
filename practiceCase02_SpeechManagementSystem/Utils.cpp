#include "Utils.hpp"

vector<string> Utils::Utils::strSplit(const string & src, const char pattern)
{
    vector<string> res;
    stringstream input(src);
    string temp;
    while (getline(input, temp, pattern))
    {
        res.push_back(temp);
    }
    return res;
}

void Utils::Utils::printContestantInfo(const ContestantType & contestant)
{
    cout << "name: " << contestant.name << "\tage: " << contestant.age << "\tid: " << contestant.id << endl;
}
