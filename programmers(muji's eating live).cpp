#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(pair<long, long> a, pair<long, long> b) {
	return a.second < b.second;
}

int solution(vector<int> food_times, long long k) {
    int answer = 0;
    vector<pair<long, long>> v;
	

	int food_size = food_times.size();
	for (int i = 0; i < food_size; i++) {
		v.push_back({food_times[i], i+1});
	}

	sort(v.begin(), v.end());
	
	long long i = 0;
	long long diff = 0;
	for (; i < food_size; ++i) {
		if (i == 0) {
			diff = v[i].first;
		}
		else {
			diff = v[i].first - v[i-1].first;
		}
		if (k < diff * (food_size - i))
			break;
		k -= diff * (food_size - i);
	}
	if (i == v.size())
		return -1;

	sort(v.begin() + i, v.end(), compare);
	answer = v[i + k % (food_size - i)].second;
	return answer;

}