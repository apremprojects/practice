#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <bitset>
#include <iostream>

using namespace std;

int getEnd(const bitset<800000>& b) {
    int i = b.size() - 1;
    while (!b[i]) {
        i--;
    }
    return i;
}

const char* hex_char_to_bin(char c)
{
    // TODO handle default / error
    switch (toupper(c))
    {
    case '0': return "0000";
    case '1': return "0001";
    case '2': return "0010";
    case '3': return "0011";
    case '4': return "0100";
    case '5': return "0101";
    case '6': return "0110";
    case '7': return "0111";
    case '8': return "1000";
    case '9': return "1001";
    case 'A': return "1010";
    case 'B': return "1011";
    case 'C': return "1100";
    case 'D': return "1101";
    case 'E': return "1110";
    case 'F': return "1111";
    }
}

std::string hex_str_to_bin_str(const std::string& hex)
{
    // TODO use a loop from <algorithm> or smth
    std::string bin;
    for (unsigned i = 0; i != hex.length(); ++i)
        bin += hex_char_to_bin(hex[i]);
    return bin;
}

int main() {
    string s;
    cin >> s;
    /*
    stringstream ss;
    ss << hex << s;
    unsigned n;
    ss >> n;*/
    bitset<800000> b(hex_str_to_bin_str(s));
    int end = getEnd(b);
    string octNum;
    for (int start = 0; start < end + 3; start += 3) {
        bitset<3> tmp;
        tmp[0] = b[start];
        tmp[1] = b[start + 1];
        tmp[2] = b[start + 2];
        octNum = char(tmp.to_ulong() + '0') + octNum;
    }
    for (int i = 0; i < octNum.size(); i++) {
        if (octNum[i] != '0') {
            cout << octNum.substr(i) << "\n";
            return 0;
        }
    }
    //cout << octNum << "\n";
}