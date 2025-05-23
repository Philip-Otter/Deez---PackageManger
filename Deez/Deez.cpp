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
#include "Deez.h"

using namespace std;

class application {
public:
	// Set from config file
	string dotNutsFile;
	string nutDir;
	string databaseFile;
	string repositories[10];  // Limit of 10 repos for now

	// Set from pre-processors
	string configFileDir;
	string OS;
	string osEnvironment;
	string osSystemArchitecture;


	void init() {
		this->readConfigFile("Deez");
		this->readConfigFile("REPOS");
	}


	string splitString(string _string, char _delimiter, string _headOrTail) {
		string head;
		string tail;
		bool isHead = true;
		
		for (int i = 0; i < (int)_string.size(); i++) {
			if (_string[i] == _delimiter) {
				isHead = false;
				continue;
			}
			if (isHead) {
				head = head + _string[i];
			}
			else {
				tail = tail + _string[i];
			}
		}

		if (_headOrTail == "head") {
			return head;
		}
		else if (_headOrTail == "tail") {
			return tail;
		}
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

	
	int removeDirecotry(string _dirPath) {
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
			if (contents.find("##") != std::string::npos) {
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
					string configVarName = splitString(contents, '=', "head");
					string configValue = splitString(contents, '=', "tail");

					switch (getStringHash(configVarName)) {
						case -1931167378: // DotNuts File
							this->dotNutsFile = configValue;
							break;
						case 1745466219: // Nut Directory
							this->nutDir = configValue;
							break;
						case 1006860175: // Database File
							this->databaseFile = configValue;
							break;
					}
				}
				if (_applicationName == "REPOS") {
					this->repositories->append(contents);
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


	void listInstalledNuts() {
		;
	}


	void searchRepositories() { //Test
		;
	}


	void makeNutPackage() {
		;
	}


	void getOverloaders() {
		;
	}


	int installPackage() {
		;
	}


	int loadSnapIn() {
		;
	}


	int doctor() {  //  Full packagemanager self repair
		;
	}


	int checkup() {  //  Full packagemanager system checkup
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
	cout << "Hello CMake." << endl;

	newApplication.init();
	cout << newApplication.getStringHash("DatabaseLocation") << endl;
	cout << newApplication.repositories[0] << endl;
	cout << newApplication.readFile("C:\\ProgramData\\Deez\\Deez.config");
	cout << newApplication.runSystemCommand("explorer.exe");

	return 0;
}
