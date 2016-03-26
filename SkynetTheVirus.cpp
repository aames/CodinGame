#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

struct points {
	int point1;
	int point2;
};

class Link {
public:
	Link(int &point1, int &point2) {
		m_points = new points();
		m_points->point1 = point1;
		m_points->point2 = point2;
		m_broken = false;
	}
	~Link() {
		delete m_points;
	}
	void breakLink() {
		m_broken = true;
	}
	bool isBroken() { return m_broken; }
	points getLinks() {
		return *m_points;
	}
private:
	points* m_points;
	bool m_broken;
};

static bool contains(int value, std::vector<int> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == value)
		{
			return true;
		}
	}

	return false;
}

int main()
{
	auto nodeCount = 0; // the total number of nodes in the level, including the gateways
	auto numberOfLinks = 0; // the number of links
	auto numberOfGateways = 0; // the number of exit gateways
	vector<int> *gateways = new vector<int>();
	vector<Link*> *links = new vector<Link*>();

	cin >> nodeCount >> numberOfLinks >> numberOfGateways; cin.ignore();
	cerr << "node count " << nodeCount << " number of links " << numberOfLinks << " number of gateways " << numberOfGateways << endl;
	// get the links
	for (int i = 0; i < numberOfLinks; i++) {
		int n1;
		int n2;
		cin >> n1 >> n2; cin.ignore();
		Link* n = new Link(n1, n2);
		links->push_back(n);
	}
	// get the indexes
	for (int i = 0; i < numberOfGateways; i++) {
		int gateway = 0; // the index of a gateway node
		cin >> gateway; cin.ignore();
		gateways->push_back(gateway);
	}

	int lastSI = -1; // the last known location of the Skynet bot - init to -1 (out of bounds)
					 // game loop
	while (1) {
		cerr << "entering game loop" << endl;
		int SI; // The index of the node on which the Skynet agent is positioned this turn
		cin >> SI; cin.ignore();
		cerr << "SI IS: " << SI << endl;

		bool noGatewayNode = true;

		for (int i = 0; i < numberOfLinks; i++) {
			// if link contains SI and gateway - break it

			// if it's already broken, ignore it
			if (links->at(i)->isBroken())
			{
				continue;
			}
			// if SI in points and gateway in points
			// delete link
			if ((lastSI != links->at(i)->getLinks().point1) && (lastSI != links->at(i)->getLinks().point2))
			{

				if ((links->at(i)->getLinks().point1 == SI) || (links->at(i)->getLinks().point2 == SI))
				{
					// Great, one of the points matches the SI
					// Now check for the gateway in points 1 and 2
					if (contains(links->at(i)->getLinks().point1, *gateways)) {
						cerr << "found in if block 1" << "loop count:" << i
							<< " Output is " << links->at(i)->getLinks().point1
							<< " " << links->at(i)->getLinks().point2 << endl;
						cout << links->at(i)->getLinks().point1 << " " << links->at(i)->getLinks().point2 << endl;
						links->at(i)->breakLink();
						lastSI = SI;
						noGatewayNode = false;
						break;
					}
					if (contains(links->at(i)->getLinks().point2, *gateways)) {
						cerr << "found in if block 2" << "loop count:" << i
							<< " Output is " << links->at(i)->getLinks().point1
							<< " " << links->at(i)->getLinks().point2 << endl;
						cout << links->at(i)->getLinks().point1 << " " << links->at(i)->getLinks().point2 << endl;
						links->at(i)->breakLink();
						lastSI = SI;
						noGatewayNode = false;
						break;
					}
				}
			}
			cerr << "loop " << i << endl; // print the loop count to stderr
		}
		if (noGatewayNode) {
			for (int j = 0; j < numberOfLinks; j++)
			{
				if (links->at(j)->isBroken())
				{
					continue;
				}
				cerr << "Hitting a random link because the gateway link could not be found" << endl;
				cout << links->at(j)->getLinks().point1 << " " << links->at(j)->getLinks().point2 << endl;
				links->at(j)->breakLink();
				lastSI = SI;
				break;
			}
		}
	}
}
