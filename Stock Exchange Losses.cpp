#include <vector> 
#include <iostream> 
#include <string>

using namespace std;

static int findMaximumLoss(vector<int>);


int main() {

	int numberOfValues;
	cin >> numberOfValues; cin.ignore();

	int difference = 0;
	int highest = 0;
	vector<int> *values = new vector<int>();

	for (int i = 0; i < numberOfValues; i++) {
		int val;
		cin >> val; cin.ignore();
		values->push_back(val);
		cerr << "adding value " << val << endl;
	}
	cout << findMaximumLoss(*values) << endl;
}

static int findMaximumLoss(vector<int> stockValues) {
	int maximalLoss = 0;
    int lastPeakIndex = 0;
	for (int i = lastPeakIndex + 1; i < stockValues.size(); i++) {
		int lossOrGainFromLastPeak = stockValues.at(i) - stockValues.at(lastPeakIndex);
		if (lossOrGainFromLastPeak < 0 && lossOrGainFromLastPeak < maximalLoss) {
			maximalLoss = lossOrGainFromLastPeak;
		}
		else if (lossOrGainFromLastPeak > 0) {
			lastPeakIndex = i;
		}
	}
	return maximalLoss;
}
