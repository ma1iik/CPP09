#include "PmergeMe.hpp"
#include <time.h>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(int ac, char **av) {
	for (int i = 1; i <= ac - 1; i++) {
		_vector.push_back(atoi(av[i]));
		//_deque.push_back(atoi(av[i]));
	}
	_pairsize = (ac - 1) /2;
}

PmergeMe::~PmergeMe() {}

////////////////////////////////////////////////////////////////

void	PmergeMe::makePair(std::pair<int, int> pairTab[], int *tmp) {
	int	count = 0;
	std::vector<int>::iterator it_vec = _vector.begin();
	std::vector<int>::iterator next;

	while (it_vec != _vector.end()) {
		next = it_vec;
		next++;
		if (next == _vector.end()) {
			*tmp = *it_vec;
			break;
    	}
		pairTab[count].first = *it_vec;
		it_vec++;
		pairTab[count].second = *it_vec;
		it_vec++;
		count++;
	}
	return ;
}

void	PmergeMe::sortPair(std::pair<int, int> pairTab[], int amount) {
	int	tmp;

	for(int i = 0; i < amount; i++) {
		if (pairTab[i].first > pairTab[i].second) {
			tmp = pairTab[i].first;
			pairTab[i].first = pairTab[i].second;
			pairTab[i].second = tmp;
		}
	}
	return ;
}

bool	PmergeMe::allpushed(std::pair<int, int> pairTab[]) {
	for (int i = 0; i < _pairsize; i++) {
	
		if (pairTab[i].second >= 0) {
			return false;
		}
	}
	return true;
}

void	PmergeMe::pushMaxToVec( std::pair<int, int> pairTab[]) {
	int	tmp;

	if (allpushed(pairTab) == true)
		return ;
	tmp = pairTab[0].second;
	for (int i = 1; i < _pairsize; i++) {
		if (pairTab[i].second > tmp) {
			tmp = pairTab[i].second;
		}
	}
	for (int i = 0; i < _pairsize; i++) {
		if (tmp == pairTab[i].second) {
			pairTab[i].second = -1;;
			break ;
		}
	}
	_vector_sorted.insert(_vector_sorted.begin(), tmp);
	pushMaxToVec(pairTab);
	return ;
}

void	PmergeMe::pushMaxToDeq( std::pair<int, int> pairTab[]) {
	int	tmp;

	if (allpushed(pairTab) == true)
		return ;
	tmp = pairTab[0].second;
	for (int i = 1; i < _pairsize; i++) {
		if (pairTab[i].second > tmp) {
			tmp = pairTab[i].second;
		}
	}
	for (int i = 0; i < _pairsize; i++) {
		if (tmp == pairTab[i].second) {
			pairTab[i].second = -1;;
			break ;
		}
	}
	_deque_sorted.insert(_deque_sorted.begin(), tmp);
	pushMaxToDeq(pairTab);
	return ;
}

void	PmergeMe::pushMinToVec(std::pair<int, int> pairTab[], int *last) {
	int	tmp;

	tmp = pairTab[0].first;
	for (int i = 1; i < _pairsize; i++) {
		if (pairTab[i].first < tmp)
			tmp = pairTab[i].first;
	}
	for (int i = 0; i < _pairsize; i++) {
		if (tmp == pairTab[i].first) {
			if (*last >= 0 && tmp >= *last) {
				tmp = *last;
				*last = -10;
			}
			else
				pairTab[i].first = -1; 
			_vector_sorted.insert(_vector_sorted.begin(), tmp);
		}
	}
	return ;
}

void	PmergeMe::pushMinToDeq(std::pair<int, int> pairTab[], int *last) {
	int	tmp;

	tmp = pairTab[0].first;
	for (int i = 1; i < _pairsize; i++) {
		if (pairTab[i].first < tmp)
			tmp = pairTab[i].first;
	}
	for (int i = 0; i < _pairsize; i++) {
		if (tmp == pairTab[i].first) {
			if (*last >= 0 && tmp >= *last) {
				tmp = *last;
				*last = -10;
			}
			else
				pairTab[i].first = -1; 
			_deque_sorted.insert(_deque_sorted.begin(), tmp);
		}
	}
	return ;
}

void	PmergeMe::add_last(std::pair<int, int> pairTab[], int *last) {
	std::vector<int>::iterator	itr;
	int	i = 0;

	while (i < _pairsize) {
		if (pairTab[i].first > 0) {
			itr = std::lower_bound(_vector_sorted.begin(), _vector_sorted.end(), pairTab[i].first);
			_vector_sorted.insert(itr, pairTab[i].first);
		}
		i++;
	}
	if (*last >= 0) {
		itr = std::lower_bound(_vector_sorted.begin(), _vector_sorted.end(), *last);
		_vector_sorted.insert(itr, *last);
	}
	return ;
}

void	PmergeMe::add_last_deq(std::pair<int, int> pairTab[], int *last) {
	std::deque<int>::iterator	itr;
	int	i = 0;

	while (i < _pairsize) {
		if (pairTab[i].first > 0) {
			itr = std::lower_bound(_deque_sorted.begin(), _deque_sorted.end(), pairTab[i].first);
			_deque_sorted.insert(itr, pairTab[i].first);
		}
		i++;
	}
	if (*last >= 0) {
		itr = std::lower_bound(_deque_sorted.begin(), _deque_sorted.end(), *last);
		_deque_sorted.insert(itr, *last);
	}
	return ;
}

void	PmergeMe::sortVector() {
	std::pair<int, int>		pairs[_pairsize];
	int						last = -69;

	makePair(pairs, &last);
	sortPair(pairs, _pairsize);
	pushMaxToVec(pairs);
	pushMinToVec(pairs, &last);
	add_last(pairs, &last);

}

void	PmergeMe::sortDeque() {
	std::pair<int, int>		pairs[_pairsize];
	int						last = -69;

	makePair(pairs, &last);
	sortPair(pairs, _pairsize);
	pushMaxToDeq(pairs);
	pushMinToDeq(pairs, &last);
	add_last_deq(pairs, &last);

}

void	PmergeMe::sort(void) {
	std::vector<int>::iterator next;
	std::deque<int>::iterator nextDeq;
	
	clock_t		start = std::clock();
	sortVector();
	clock_t		end = std::clock();

	int i = 0;

	std::cout << "\e[1;31mAfter\e[0m:	";
	for (std::vector<int>::iterator it = _vector_sorted.begin(); it != _vector_sorted.end(); it++) {
		next = it;	
		next++;
		if (i == 4 && _pairsize * 2 > 7) {
			std::cout << "[...]" << std::endl;
			break;
		}
		if (next == _vector_sorted.end())
			std::cout << *it << std::endl;
		else
			std::cout << *it << " ";
		i++;
	}
	double timeTaken = double(end - start) / double(CLOCKS_PER_SEC);
	std::cout << "Time to process a range of 5 elements with std::vector<int> : " << timeTaken * 1000 << " ms" << std::endl;

	start = std::clock();
	sortDeque();
	end = std::clock();
	i = 0;
	//print deque
	// std::cout << "\e[1;31mAfter (deq)\e[0m:	";
	// for (std::deque<int>::iterator it = _deque_sorted.begin(); it != _deque_sorted.end(); it++) {
	// 	nextDeq = it;	
	// 	nextDeq++;
	// 	if (i == 4 && _pairsize * 2 > 7) {
	// 		std::cout << "[...]" << std::endl;
	// 		break;
	// 	}
	// 	if (nextDeq == _deque_sorted.end())
	// 		std::cout << *it << std::endl;
	// 	else
	// 		std::cout << *it << " ";
	// 	i++;
	// }
	timeTaken = double(end - start) / double(CLOCKS_PER_SEC);
	std::cout << "Time to process a range of 5 elements with std::deque<int> : " << timeTaken * 1000 << " ms" << std::endl;

	return;
}