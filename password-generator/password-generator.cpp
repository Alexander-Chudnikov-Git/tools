#include <iostream>
#include <cctype>

bool is_digit(char* array)
{
	std::string buffer(array);
	for(char& letter : buffer) 
	{
	    if((std::isdigit(letter) == 0)) 
	    { 
	        return 0;
	    }
	}
	return 1;
}

bool is_letter(char* array)
{
	std::string buffer(array);
	for(char& letter : buffer) 
	{
	    if((std::isalpha(letter) == 0)) 
	    { 
	        return 0;
	    }
	}
	return 1;
}

bool is_contained(char letter, std::string letters)
{
	for (char& letter_c : letters)
	{
		if (letter == letter_c)
		{
			return 1;
		}
	}
	return 0;
}

std::string passGen(int length, std::string letters, std::string charset = "")
{
	std::string password = "";
	if (charset == "")
	{
		for (char& letter : letters)
		{
			switch (letter)
			{
			case 'l':
				charset += "abcdefghijklmnopqrstuvwxyz";
				break;
			case 'u':
				charset += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
				break;
			case 'n':
				charset += "0123456789";
				break;
			case 's':
				charset += "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
				break;
			}
		}
	}
	while (length > 0)
	{
		password += charset[std::rand() % charset.length()];
		--length;
	}
	return password;
}

int main(int argc, char* argv[])
{
	switch (argc)
	{
	case 1:
	{
		std::cout << passGen(32, "suln") << std::endl;
	}
	break;
	case 2:
	{
		std::string number(argv[1]);
		if (is_digit(argv[1]))
		{
			int temp = 0;
			for (char& num : number)
			{
				temp += (int)num - 48;	
				temp *= 10;
			}
			temp /= 10;
			if (temp > 256 || temp <= 0)
			{
				std::cerr << "Invalid argument given (number should be in range of 256)" << std::endl;
				return -1;
			}
			else 
			{
				std::cout << passGen(temp, "suln") << std::endl;
			}
		}
		else if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "-help")
		{
			std::cout << "In total, there might be given 3 arguments: " << std::endl;
			std::cout << "" << std::endl;
			std::cout << argv[0] << std::endl;
			std::cout << "	1-	[number of symbols (up to 256)]" << std::endl;
			std::cout << "	2-	[charset modifiers (l -> lowercase letters; u -> uppercase letters; s -> special characters; n -> numbers; c -> custom (can be used alone))]" << std::endl;
			std::cout << "	3-	<charset (if c is used as charset modifier)>" << std::endl;
			std::cout << std::endl;
			return 0;
		}
		else 
		{
			std::cerr << "Invalid argument given (number should be in range of 256)" << std::endl;
			return -1;
		}
	}
	break;
 	case 3:
 	{
 		std::string number(argv[1]);
 		std::string buff(argv[2]);	
		if (is_digit(argv[1]) && is_letter(argv[2]))
		{
			int temp = 0;
			for (char& num : number)
			{
				temp += (int)num - 48;	
				temp *= 10;
			}
			temp /= 10;
			std::string args = "";
			if (temp > 256 || temp <= 0)
			{
				std::cerr << "Invalid argument given (number should be in range of 256)" << std::endl;
				return -1;
			}
			else 
			{
				for (char& letter : buff)
				{
					switch (letter)
					{
					case 'u':
						args += "u";
						break;
					case 'l':
						args += "l";
						break;
					case 'n':
						args += "n";
						break;
					case 's':
						args += "s";
						break;
					default:
						std::cerr << "Invalid argument passed: " << letter << std::endl;
						return -1;
					}
				}
				std::cout << passGen(temp, args) << std::endl;
				return 0;
			}
		}
		else 
		{
			std::cerr << "Invalid argument given (both arguments are invalid)" << std::endl;
			std::cerr << "Invalid argument given (number should be in range of 256)" << std::endl;
			std::cerr << "Invalid arguments passed: " << buff << std::endl;
			return -1;
		}
	}
	break;
	case 4:
	{
		std::string number(argv[1]);
 		std::string buff(argv[2]);	
 		std::string args_c(argv[3]);
 		bool mult = 0;
		if (is_digit(argv[1]) && is_letter(argv[2]))
		{
			int temp = 0;
			for (char& num : number)
			{
				temp += (int)num - 48;	
				temp *= 10;
			}
			temp /= 10;
			std::string args = "";	
				
			if (temp > 256 || temp <= 0)
			{
				std::cerr << "Invalid argument given (number should be in range of 256)" << std::endl;
				return -1;
			}
			if (buff == "c")
			{
				for (char& letter : args_c)
				{
					if (is_contained(letter, args))
					{
						mult = 1;
					}
					else 
					{	
						args += letter;
					}
				}
				if (mult)
				{
					std::cerr << "Invalid argument (multiple identical characters) -- programm will continue working" << std::endl;
				}
				std::cout << passGen(temp, buff, args) << std::endl;
				return 0;
			}
			else 
			{
				std::cerr << "Invalid argument amount (use single c in case you whant to use custom charset)" << std::endl;
				return -1;
			}
		}
		else
		{
			std::cerr << "Invalid arguments (more than 3)" << std::endl;
			std::cerr << "Invalid argument given (number should be in range of 256)" << std::endl;
			std::cerr << "Invalid arguments passed: " << buff << std::endl;
			return -1;
		}
	}
	break;
	default:
	{
		std::cerr << "Invalid arguments amount given use -h for help" << std::endl;
		return -1;
	}
	break;
	}
}
