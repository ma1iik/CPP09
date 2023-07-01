#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>

int date_error(const std::string& dateStr) {
    std::istringstream iss(dateStr);

    int year, month, day;
    char dash1, dash2;

    if (!(iss >> year >> dash1 >> month >> dash2 >> day)) {
		std::cout << "Error: bad input => " << dateStr << std::endl;
        return 1;
    }

    if (iss.fail() || dash1 != '-' || dash2 != '-') {
		std::cout << "Error: bad input => " << dateStr << std::endl;
        return 1;
    }

    if (year < 1900 || year > 2100) {
		std::cout << "Error: bad input => " << dateStr << std::endl;
        return 1;
    }

    if (month < 1 || month > 12) {
		std::cout << "Error: bad input => " << dateStr << std::endl;
        return 1;
    }

    int maxDay = 31;
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        maxDay = 30;
    } else if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            maxDay = 29;
        } else {
            maxDay = 28;
        }
    }

    if (day < 1 || day > maxDay) {
		std::cout << "Error: bad input => " << dateStr << std::endl;
        return 1;
    }
    return 0;
}

int amount_error(float amount) {
    if (amount <= 0) {
        std::cout << "Error: not a positive number." << std::endl;
        return 1;
    }
    if (amount > std::numeric_limits<float>::max()) {
        std::cout << "Error: too large a number." << std::endl;
        return 1;
    }
    return 0;
}


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

			//std::cout << "\"" << date << "\"" << " = " << "\"" << exchangeRate << "\"" << std::endl;
		}
	}

}

void    pars_file(char *av, std::map<std::string, float> &data) {
    std::string		name = av;
    std::string		ext = ".txt";
	(void)data;
	// if extention isnt .txt //
	if (name.length() <= ext.length()) {std::cout << "Error: wrong file extension." << std::endl; exit(0);}
	if (name.substr(name.length() - ext.length()) != ext) {std::cout << "Error: wrong file extension." << std::endl; exit(0);}
	// if fails opening file //
	std::ifstream	file(name);
	if (!file.is_open()) {std::cout << "Error: could not open argument file." << std::endl; exit(0);}
	// process of program follows //
	std::string			line;
	while(std::getline(file, line)) {
		if (line == "date | value") {std::cout << "first line skipped" << std::endl; continue;}
		std::istringstream	stream(line);
		std::string			date, amount;
		if (std::getline(stream, date, '|') && std::getline(stream, amount, '|')) {
			// remove first and last space from both elements//
			date.erase(0, date.find_first_not_of(" "));
			date.erase(date.find_last_not_of(" ") + 1);
			amount.erase(0, amount.find_first_not_of(" "));
			amount.erase(amount.find_last_not_of(" ") + 1);
			float		TheAmount;
			try {
				TheAmount = std::stof(amount);
			} catch (const std::exception& e) {
                std::cout << "Error: invalid amount value." << std::endl;
                continue;
            }
			// handle possible errors on execution //
			if (date_error(date)) {continue;}
			if (amount_error(TheAmount)) {continue;}
			std::cout << "\"" << date << "\"" << " " << "\"" << amount << "\"" << std::endl;
		}


		
	}
	//-----------------------------//
}

int     main(int ac, char **av) {
    (void)ac;
    (void)av;
	std::map<std::string, float> Data;
    if (ac != 2) {std::cout << "Error: could not open file." << std::endl; exit(0);}
    pars_data(Data);
	pars_file(av[1], Data);

}