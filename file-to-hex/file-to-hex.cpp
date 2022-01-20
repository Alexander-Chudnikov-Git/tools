#include <fstream>
#include <sys/stat.h>
#include <iostream>

inline bool exist(const std::string& name) 
{
  	struct stat buffer;   
  	return (stat (name.c_str(), &buffer) == 0); 
}

int main(int argc, char* argv[]) 
{
	if (argc > 1 && argc < 4)
	{
		
		char * buffer;
		int count = 0;
		if (exist(argv[1]))
		{
			if (exist(argv[2]))
			{
				std::remove(argv[2]);
			}
			std::fstream input_file (argv[1], std::ios::ate | std::ios::in | std::ios::binary);
			std::fstream output_file (argv[2], std::ios::out);
			long long size = input_file.tellg();
			input_file.seekg (0, input_file.beg);
			std::cout << size << std::endl;
			buffer = new char [size];
    		input_file.read ((char *) &buffer[0], size);
    		output_file << "0x" << std::setbase(16) << std::setw(2) << std::setfill('0') << (0xff & (unsigned int)buffer[0]);
    		for( int i = 1; i < size; i++ )
    		{
    			if (i % 8 == 0)
    			{
    				output_file << ",\r\n";
    			}
    			else 
    			{
    				output_file << ", ";
    			}
			    output_file << "0x" << std::setbase(16) << std::setw( 2 ) << std::setfill('0')  << (0xff & (unsigned int)buffer[i]);
			}

			input_file.close();
			output_file.close();
		}
		else 
		{
			std::cout << argv[1] << " doesn't exist" << std::endl;
		}
	}
	else {
		std::cout << "Please, use construction:" << std::endl;
		std::cout << "	1-	[input-file]" << std::endl;
		std::cout << "	2-	[output-file]" << std::endl;
	}
	return 0;
}

