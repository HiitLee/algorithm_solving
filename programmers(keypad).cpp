#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

vector<int> changXY(string numbers) {
	vector<int> point;
	if (numbers == "0")
	{
		point = { 3,1 };
		return point;
	}
	else if (numbers == "#") {
		point = { 3,2 };
		return point;
	}
	else if (numbers == "*") {
		point = { 3,0 };
		return point;
	}
	int number = stoi(numbers)-1;
	int x = (number) / 3;
	int y = (number) % 3;

	point = { x,y };
	return  point;
}

string solution(vector<int> numbers, string hand) {
	string answer = "";
	// 앞: 왼, 뒤: 오
	vector<string> now = { "*","#" };
	int leftHand[10];
    memset(leftHand,0,sizeof(leftHand));
	leftHand[1] = 1; leftHand[4] = 1; leftHand[7] = 1;
	int rightHand[10];
    memset(rightHand,0,sizeof(rightHand));
	rightHand[3] = 1; rightHand[6] = 1; rightHand[9] = 1;
	for (int i = 0; i < numbers.size(); i++) {
		string L = now[0];
		string R = now[1];

		vector<int> temp;
		vector<int> right;
		vector<int> left;
		temp = changXY(to_string(numbers[i]));
		right = changXY(R);
		left = changXY(L);

		if (rightHand[numbers[i]]==1) {
			answer += 'R';
			now[1] = to_string(numbers[i]);
			continue;
		}
		else if (leftHand[numbers[i]]==1) {
			answer+='L';
			now[0] = to_string(numbers[i]);
			continue;
		}
		
		int distL = abs(left[0] - temp[0]) + abs(left[1] - temp[1]);
		int distR = abs(right[0] - temp[0]) + abs(right[1] - temp[1]);

		if (distL < distR) {
			answer += "L";
			now[0] = to_string(numbers[i]);
			continue;
		}
		else if (distL > distR) {
			answer += "R";
			now[1] = to_string(numbers[i]);
			continue;
		}
		else if (distL == distR) {
			if (hand == "right") {
				answer += "R";
				now[1] = to_string(numbers[i]);
				continue;
			}
			else if(hand=="left"){
				answer += "L";
				now[0] = to_string(numbers[i]);
				continue;
			}
		}
  }
	return answer;
}