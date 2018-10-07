#pragma once

#include <vector>
#include <algorithm>

template <class T>
class Permuter 
{
public:
	Permuter(std::vector<T> entries);
	bool validate();
	bool generate(int k);
	void initialize(int k);
	bool isEnd();
	std::vector<std::vector<T>> generateResults();
private:
	std::vector<int> 	_stack;
	std::vector<T> 		_entries;
};

template <class T>
Permuter<T>::Permuter(std::vector<T> entries) :
	_entries(entries)
{}

template <class T>
std::vector<std::vector<T>> Permuter<T>::generateResults()
{
	int k = 0;
	std::vector<std::vector<T>> results;

	while (k > -1) {
		initialize(k);

		if (generate(k) == false) {
			// can't generate more variants,
			// return to the previous stack level
			k--;
			_stack.pop_back();
			continue;
		}

		if (isEnd()) {
			std::vector<T> gresult;
			for (auto i : _stack) {
				gresult.push_back(_entries[i]);
			}
			results.push_back(gresult);
			k--;
			_stack.pop_back();
		} else {
			k++;
		}
	}

	return results;
}

template <class T>
void Permuter<T>::initialize(int k)
{
	if (static_cast<int>(_stack.size()) - 1  < k) {
		_stack.push_back(-1);
	}
}

template <class T>
bool Permuter<T>::generate(int k)
{
	if (static_cast<int>(_stack.size()) == k)
		return false;

	do {
		_stack[k]++;
	} while (std::find(_stack.begin(), _stack.begin() + k, _stack[k]) != _stack.begin() + k); 

	if (_stack[k] > static_cast<int>(_entries.size()) - 1)
		return false;

	return true;
}

template <class T>
bool Permuter<T>::isEnd()
{
	if (_stack.size() == _entries.size())
		return true;
	return false;
}
