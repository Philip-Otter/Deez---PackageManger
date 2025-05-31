// Deez.cpp : Defines the entry point for the application.
//

#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <cstdint>
#include <cstdio>
#include <stdio.h>
//#include <openssl/md5.h>
#include <vector>
#include "Deez.h"

using namespace std;

class application {
public:
	// Set from config file
	string dotNutsFile;
	string nutDir;
	string databaseFile;
	vector <string> repositories;

	// Set from pre-processors
	string configFileDir;
	string OS;
	string osEnvironment;
	string osSystemArchitecture;


	void init() {
		this->readConfigFile("Deez");
		this->readConfigFile("REPOS");
	}


	vector <string> splitString(string _string, char _delimiter) {
		string head;
		string tail;
		vector <string> headPlusTail;
		bool isHead = true;
		
		for (int i = 0; i < (int)_string.size(); i++) {
			if (isHead) {
				if (_string[i] == _delimiter) {
					isHead = false;
					continue;
				}
				head = head + _string[i];
			}
			else {
				tail = tail + _string[i];
			}

		}

		headPlusTail.push_back(head);
		headPlusTail.push_back(tail);

		return headPlusTail;
	}


	// Hashing API Functions
	int getStringHash(string _string) {
		hash<string> h;
		int hashVal = h(_string);

		return hashVal;
	}


	// Need to install openssl library for this to work right
	int getFileHash(string _filePath) {
		ifstream file(_filePath, ios::in | ios::binary | ios::ate);

		long fileSize = file.tellg();
		char* fileInMemory = new char[fileSize];  // Alocate memory space for the file

		// Pull file into allocated memory space
		file.seekg(0, ios::beg);
		file.read(fileInMemory, fileSize);
		file.close();

		// unsigned char md5Hash[MD5_DIGEST_LENGTH];  <- This needs the openssl library
	}


	// Core IO API Functions
	string readFile(string _filePath) {
		ifstream file;
		string contents;
		string returnString;

		file.open(_filePath);

		while (getline(file, contents)){
			returnString = returnString + contents + "\n";
		}

		file.close();

		return returnString;
	}


	void writeFile(string _filePath, string _fileContents) {
		ofstream file(_filePath);

		file << _fileContents;

		file.close();
	}


	int deleteFile(string _filePath) {
		int status = remove(_filePath.c_str());  // Remove seems to require a C type string (const char array) rather than a C++ string 

		return status;
	}


	int makeDirectory() {
		;
	}

	
	int removeDirectory(string _dirPath) {
		int status = std::filesystem::remove_all(_dirPath.c_str());

		return status;
	}


	int downloadFile(string _URL) {  //  Download to default location
		;
	}


	int downloadFile(string _URL, string _outputFile) {  //  Download to specified output file
		;
	}


	int unzipFile(string _zipFile, string _outputLocation) {
		;
	}


	int zipFile(string _directory, string _outputFile) {  //  Zip a single file
		;
	}

	int zipFile(string _directory[], string _outputFile) {  //  Zip multiple files together
		;
	}

	void passToMemory() {
		;
	}

	
	void queryDB() {
		;
	}


	void writeDB() {
		;
	}

	
	string parseXML() {
		;
	}

	int runSystemCommand(string _command) {  //  Resource hungry and gross but the option is there.
		int returnCode = system(_command.c_str());  //  Only returns an int code value from the comman. Non-zero is a failure.

		return returnCode;
	}


	string runCommand(string _command) {
		;
	}

	// Core Deez API functions
	void readNutFile() {
		;
	}


	void readConfigFile(string _applicationName) {
		string contents;
		string applicationIndicator = "~~~" + _applicationName + "~~~";
		ifstream configFile;
		bool inApplication = false;

		configFile.open("C:\\ProgramData\\Deez\\Deez.config");

		while(getline(configFile, contents)) {
			// Ignore comments in config file
			if (contents.find("#") != std::string::npos) {
				continue;
			}
			if (contents.find(applicationIndicator) != std::string::npos) {
				inApplication = true;
				continue;
			}
			if (inApplication) {
				if (contents.find("~~~END~~~") != std::string::npos) {
					inApplication = false;
					continue;
				}
				if (_applicationName == "Deez") {
					vector <string> varNamePlusValue = this->splitString(contents, '=');  //  [0] Config variable name [1] config variable value

					switch (getStringHash(varNamePlusValue[0])) {
						case -1931167378: // DotNuts File
							this->dotNutsFile = varNamePlusValue[1];
							break;
						case 1745466219: // Nut Directory
							this->nutDir = varNamePlusValue[1];
							break;
						case 1006860175: // Database File
							this->databaseFile = varNamePlusValue[1];
							break;
					}
				}
				if (_applicationName == "REPOS") {
					this->repositories.push_back(contents);
				}
			}
		}
		configFile.close();
	}


	int installPackage(string _pkgName) {
		;
	}


	int installPackage(int _listNumber) {  //  Alternative install based off of last search result's order. Search would cache the relationship between the package name and list number. Should make life easier for the user.
		;
	}


	void writeConfigFile() {
		;
	}


	void updatePackages() {
		;
	}


	string listInstalledNuts() {
		string allNuts = this->readFile(this->dotNutsFile);
		vector <string> nutLines = this->splitString(allNuts, '\n');

		while ((this->splitString(nutLines.back(), '\n')[1].find("\n")) != std::string::npos) {
			vector <string> tempVectStringHolder = this->splitString(nutLines.back(), '\n');
			nutLines.pop_back();
			nutLines.push_back(tempVectStringHolder[0]);
			nutLines.push_back(tempVectStringHolder[1]);
		}

		string installedPackages;

		for (int i = 0; i < nutLines.size(); i++) {
			if (nutLines[i].find("##") != std::string::npos) {  // Ignore comments in the file
				continue;
			}
			if (nutLines[i] == "\n") {  // Ignore blank lines
				continue;
			}
			else {
				vector <string> nutProperties = this->splitString(nutLines[i], '|');

				while ((this->splitString(nutProperties.back(), '|')[1].find("|")) != std::string::npos) {
					vector <string> tempVectStringHolder = this->splitString(nutProperties.back(), '|');
					nutProperties.pop_back();
					nutProperties.push_back(tempVectStringHolder[0]);
					nutProperties.push_back(tempVectStringHolder[1]);
				}
				vector <string> tempVectStringHolder = this->splitString(nutProperties.back(), '|');
				nutProperties.pop_back();
				nutProperties.push_back(tempVectStringHolder[0]);
				nutProperties.push_back(tempVectStringHolder[1]);
				
				// All nut line attributes
				string packageName = nutProperties[0];			//	index 0
				string packageVersion = nutProperties[1];		//	index 1
				string packageRepository = nutProperties[2];	//	index 2
				string packageDescription = nutProperties[3];	//	indez 3
				string packageAuthor = nutProperties[4];		//	index 4
				string packageArchs = nutProperties[5];			//	index 5
				string packageHash = nutProperties[6];			//	index 6
				bool packageInstalled = false;					//	index 7 should contain indicator of "***" for installed

					if (nutProperties[7].find("***") != std::string::npos) {
						packageInstalled = true;
					}

					if (packageInstalled) {
						installedPackages = (packageName + " " + packageVersion + "\n");
					}
			}

		}

		return installedPackages;
	}


	void searchRepos(string _packageName) { //Test
		;
	}


	void makeNutPackage() {
		;
	}


	void getOverloaders() {
		;
	}


	int loadSnapIn() {
		;
	}


	int doctor() {  //  Full packagemanager self repair
		;
	}


	int checkup(string _packageName) {  // Package specific checkup
		;
	}
};

int main()
{
	application newApplication;

// Pre-Processors Based on OS and OS Environment
// 
// Linux
#if __linux__ || __linux || linux || __gnu_linux__
	newApplication.OS = "Linux";
#if __ANDROID__
	newApplication.OS = "Android";
	newApplication.configFileDir = "/data/data/Deez";
#endif // __ANDROID__
	newApplication.configFileDir = "/etc/Deez/";

// Windows
#elif _WIN32
	newApplication.configFileDir = "C:\\ProgramData\\Deez";
#if _WIN64
	newApplication.osSystemArchitecture = "x64";
#else
	newApplication.osSystemArchitecture = "x86";
#endif // _WIN64

// BSD
#elif __bsdi__
	newApplication.OS = "BSD";
#if __FreeBSD__
	newApplication.osEnvironment = "FreeBSD";
#endif // __FreeBSD__
#if __NetBSD__
	newApplication.osEnvironment = "NetBSD";
#endif // __NetBSD__
#if __OpenBSD__
	newApplication.osEnvironment = "__OpenBSD__";
#endif // __OpenBSD__

// MacOS
#if __APPLE__ || __MACH__ || macintosh || Macintosh
	newApplication.OS = "MacOS"
	newApplication.confiFileDir = "~/Library/Application Support/Deez"
#endif // __APPLE__ && __MACH__ || macintosh || Macintosh


#endif

	newApplication.init();
	cout << newApplication.getStringHash("DatabaseLocation") << endl;
	cout << newApplication.repositories[0] << endl;
	cout << newApplication.readFile("C:\\ProgramData\\Deez\\Deez.config");
	cout << newApplication.runSystemCommand("explorer.exe") << endl;
	cout << newApplication.dotNutsFile << endl;
	cout << newApplication.listInstalledNuts() << endl;
	return 0;
}
