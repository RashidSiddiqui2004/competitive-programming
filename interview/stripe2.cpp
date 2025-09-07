#include <iostream>
using namespace std;

vector<string> getIds(const string &concatenatedApplicationIds)
{
    int n = concatenatedApplicationIds.size();
    vector<string> ids;
    int i = 0;

    while (i < n)
    {
        int len = 0;
        char ch = concatenatedApplicationIds[i];
        while (i < n and ch >= '0' and ch <= '9')
        {
            len *= 10;
            len += (ch - '0');
            ch = concatenatedApplicationIds[++i];
        }
        if (len == 0)
        {
            break;
        }
        string currendId = "";
        for (size_t j = 0; j < len; j++)
        {
            currendId += concatenatedApplicationIds[i + j];
        }
        ids.push_back(currendId);
        i += len;
    }
    return ids;
}

int main(int argc, char const *argv[])
{
    string concatenatedApplicationIds;
    cin >> concatenatedApplicationIds;

    auto ids = getIds(concatenatedApplicationIds);
    for (auto id : ids)
    {
        cout << id << endl;
    }
    return 0;
}
