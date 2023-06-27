#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>

void	pars_data(std::map<std::string, float> &Data) {
	std::ifstream	file;
	file.open("data.csv");
	if (!file.is_open()) {
		file.open("input.csv");
		if (!file.is_open()) {
			std::cout << "Error: could not open file." << std::endl;
			exit(0);
		}
	}

	std::cout << "all good" << std::endl;
	std::string	line;
	while (std::getline(file, line)) {
		if (line == "date,exchange_rate") {std::cout << "lol im here" << std::endl; continue;}
		std::istringstream stream(line);
		std::string date, rate;
		if (std::getline(stream, date, ',') && std::getline(stream, rate, ',')) {
			float	exchangeRate;
			try {
                exchangeRate = std::stof(rate);
            } catch (const std::exception& e) {
                std::cout << "Error: invalid exchange rate value." << std::endl;
                continue;
            }

			Data[date] = exchangeRate;

			std::cout << date << " = " << exchangeRate << std::endl;
		}
	}

}

void    pars_file(char *av) {
    std::string		name = av;
    std::string		ext = ".txt";

	if (name.substr(name.length() - ext.length()) != ext) {std::cout << "Error: could not open file." << std::endl; exit(0);}
	//-----------------------------//
	std::ifstream	file(name);

	if (!file.is_open()) {std::cout << "Error: could not open file." << std::endl; exit(0);}
	//-----------------------------//
	std::string		line;

	while(std::getline(file, line)) {
		if (line == "date,exchange_rate") {std::cout << "lol im here" << std::endl;}
	}
	//-----------------------------//
}

int     main(int ac, char **av) {
    (void)ac;
    (void)av;
	std::map<std::string, float> Data;
    if (ac != 2) {std::cout << "Error: could not open file." << std::endl; exit(0);}
    pars_data(Data);
	//pars_file(av[1]);

}