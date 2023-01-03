#include <map>
#include <iostream>
#include <iterator>
template<typename K, typename V>
class interval_map {
	friend void IntervalMapTest();
	V m_valBegin;
	std::map<K, V> m_map;
public:
	interval_map(V const& val)
		: m_valBegin(val)
	{}

	void assign(K const& keyBegin, K const& keyEnd, V const& val) {
		if(!(keyBegin < keyEnd))
			return;



		if (m_map.empty() and !(val == m_valBegin)) {
			m_map.insert({ keyBegin, val });
			m_map.insert({ keyEnd, m_valBegin });
			return;
		}

		
		
		V endVal;
		bool isSmallest = true;
		for (auto it = m_map.rbegin(); it != m_map.rend(); ++it) {
			if (it->first < keyEnd) {
				endVal = it->second;
				isSmallest = false;
				break;
			}
		}

		if (isSmallest)
			endVal = m_valBegin;

		m_map.erase(keyBegin);

		m_map.insert({ keyBegin, val });
		m_map.insert({ keyEnd, endVal });

		auto begin_itr = m_map.find(keyBegin);
		auto end_itr = m_map.find(keyEnd);
		

		for (auto it = std::next(begin_itr); it != end_itr; ) {
			auto t = std::next(it);
			m_map.erase(it);
			it = t;
		}


		//processing m_map for canonic form
		auto it = m_map.begin();
		while (next(it) != m_map.end()) {
			auto next_it = next(it);

			if (next_it->second == it->second) {
				m_map.erase(next_it);
				continue;
			}

			if (it != m_map.end())
				it++;
		}

		if (m_map.begin()->second == m_valBegin)
			m_map.erase(m_map.begin());
	}

	// look-up of the value associated with key
	V const& operator[](K const& key) const {
		auto it = m_map.upper_bound(key);
		if (it == m_map.begin()) {
			return m_valBegin;
		}
		else {
			return (--it)->second;
		}
	}

	int size() {
		return m_map.size();
	}

	void print_map() {
		std::cout << "[ ";
		for (const auto& n : m_map) {
			std::cout << "(" << n.first << ", " << n.second << "), ";
		}

		std::cout << "]\n";
	}
};



void print_map(const std::map<int, int>& m)
{

	 for (const auto& n : m) {
	      std::cout << n.first << " = " << n.second << "; ";
	 }

	std::cout << '\n';
}

int main() {
	using std::cout;
	using std::cin;
	using std::map;

	cout << "Testing\n";

	interval_map<float, std::string> im("value");

	im.assign(5.3, 9.1, "hello");
	im.print_map();

	im.assign(9.1, 10, "world");
	im.print_map();

	im.assign(4, 4.5, "value");
	im.print_map();


	im.assign(2.3, 3.3, "left");
	im.print_map();

	im.assign(1.5, 4.1, "left and inside");
	im.print_map();

	im.assign(5.5, 5.6, "inside");
	im.print_map();

	im.assign(5.6, 11, "isdide right");
	im.print_map();

	im.assign(12, 12.1, "right");
	im.print_map();


	cout<<"im[5.4] - " <<im[5.4];
}