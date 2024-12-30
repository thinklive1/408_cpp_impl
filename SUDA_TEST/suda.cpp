#include <vector>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    vector<int> temp, result;
    for (auto i = nums.begin(); i != nums.end();i++) {
        temp.push_back(target - *i);
    }
    int index1 = 0;
    for (auto i = nums.begin(); i != nums.end();i++) {
        int index2 = index1 + 1;
        auto it = temp.begin();
        for (int t = 0;t < index2;t++) it++;
        while (it != temp.end()) {
            if (*i == *it) {
                result.push_back(index1);
                result.push_back(index2);
                return result;
            }
            it++;
            index2++;
        }
        index1++;
    }
    return result;
};

