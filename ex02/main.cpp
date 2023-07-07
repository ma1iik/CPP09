#include "PmergeMe.hpp"

int main(int ac, char **av) {
	if(ac < 2) {
		std::cout << "Error: not enough arguments!" << std::endl;
		return (0);
	}
	
	 for (int i = 1; i < ac; i++) {
        for(int j = 0; av[i][j] != '\0'; j++) {
            if (!isdigit(av[i][j])) {
                std::cout << "Error: Argument " << i << " is not a positive integer!" << std::endl;
                return 1;
            }
        }
		if (static_cast<unsigned  long long>(atoi(av[i])) > 2147483647) {
			std::cout << "Error: Argument " << i << " is bigger than an integer!" << std::endl;
			return 1;
		}
    }

	PmergeMe	sorter(ac, av);

	std::cout << "\e[1;31mBefore\e[0m:	";
	for (int i = 1; av[i]; i++) {
		if (i == 5 &&  ac - 1 > 7) {
			std::cout << "[...]" << std::endl;
			break;
		}
		if (!av[i + 1])
			std::cout << av[i] << std::endl;
		else
			std::cout << av[i] << " ";
	}
	
	sorter.sort();
}