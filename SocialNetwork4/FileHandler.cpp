#include "FileHandler.h"

void FileHandler::loadSocialNetwork(const CustomString& filePath)
{
	std::fstream socialNetworkFile(filePath.getString(), std::ios::binary | std::ios::in);

	//If file doesn't exist, create it
	if (!socialNetworkFile.is_open()) {
		std::cout << "File does not exist! Creating..." << std::endl;
		socialNetworkFile.open(filePath.getString(), std::ios::binary | std::ios::out);
		if (!socialNetworkFile.is_open()) {
			std::cout << "Could not create file!" << std::endl;
			return;
		}
		CurrentData::getCurrSocialNetwork().setDirectory(filePath);
		return;
	}

	//If file exists, but is empty set currSocialNetwork as empty
	//continue here..

	//If file exists and isnt empty, read it...

	CurrentData::getCurrSocialNetwork().getCurrUsers().clear();
	CurrentData::getCurrSocialNetwork().getCurrTopics().clear();

	size_t usersCount = 0;
	size_t i = 0;

	socialNetworkFile.read(reinterpret_cast<char*>(&usersCount), sizeof(usersCount));
	Vector<User> readUsers(usersCount + 10); //add 10 more places to save some time/resources											later

	size_t strLength = 0;
	CustomString firstName, lastName, userName, password;
	unsigned id = 0, points = 0;
	bool isModerator = false;

	for (int j = 0; j < usersCount; j++) {

		//read firstName
		socialNetworkFile.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
		char* string = new char[strLength];
		socialNetworkFile.read(string, strLength);
		firstName.setLength(strLength);
		firstName.setString(string);
		delete[] string;

		//read lastName
		socialNetworkFile.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
		string = new char[strLength];
		socialNetworkFile.read(string, strLength);
		lastName.setLength(strLength);
		lastName.setString(string);
		delete[] string;

		//read userName
		socialNetworkFile.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
		string = new char[strLength];
		socialNetworkFile.read(string, strLength);
		userName.setLength(strLength);
		userName.setString(string);
		delete[] string;

		//read password
		socialNetworkFile.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
		string = new char[strLength];
		socialNetworkFile.read(string, strLength);
		password.setLength(strLength);
		password.setString(string);
		delete[] string;

		socialNetworkFile.read(reinterpret_cast<char*>(&id), sizeof(id));
		socialNetworkFile.read(reinterpret_cast<char*>(&points), sizeof(points));
		socialNetworkFile.read(reinterpret_cast<char*>(&isModerator), sizeof(isModerator));

		User newUser(firstName, lastName, userName, password, id, points, isModerator);

		readUsers.pushBack(newUser);

		firstName.clearString();
		lastName.clearString();
		userName.clearString();
		password.clearString();

	}

	CurrentData::getCurrSocialNetwork().setCurrUsers(readUsers);


	//READ TOPICS
	//continue
}

void FileHandler::saveSocialNetwork()
{
	if (CurrentData::getChangesMadeStatus() == false) {
		std::cout << "No changes to save!" << std::endl;
		return;
	}

	const char* filepath = CurrentData::getCurrSocialNetwork().getDirectory().getString();

	std::ofstream socialNetworkFile(filepath, std::ios::binary | std::ios::trunc);
	if (!socialNetworkFile.is_open()) {
		std::cout << "Error opening users file for saving!" << std::endl;
		//exception? handle this somehow
		return;
	}

	//WRITE USERS
	size_t usersCount = CurrentData::getCurrSocialNetwork().getCurrUsers().getSize();
	socialNetworkFile.write(reinterpret_cast<const char*>(&usersCount), sizeof(usersCount));

	size_t strLength = 0;
	for (int i = 0; i < usersCount; i++) {

		User userToSave = CurrentData::getCurrSocialNetwork().getCurrUsers()[i];

		//save firstName
		strLength = userToSave.getFirstName().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(userToSave.getFirstName().getString(), strLength);

		//save lastName
		strLength = userToSave.getLastName().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(userToSave.getLastName().getString(), strLength);

		//save userName
		strLength = userToSave.getUserName().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(userToSave.getUserName().getString(), strLength);

		//save password
		strLength = userToSave.getPassword().length();
		socialNetworkFile.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
		socialNetworkFile.write(userToSave.getPassword().getString(), strLength);

		unsigned id = userToSave.getId();
		unsigned points = userToSave.getPoints();
		bool moderatorStatus = userToSave.getModeratorStatus();

		socialNetworkFile.write(reinterpret_cast<const char*>(&id), sizeof(id));
		socialNetworkFile.write(reinterpret_cast<const char*>(&points), sizeof(points));
		socialNetworkFile.write(reinterpret_cast<const char*>(&moderatorStatus), sizeof(moderatorStatus));

	}

	//save topics now.....

	socialNetworkFile.close();
}
