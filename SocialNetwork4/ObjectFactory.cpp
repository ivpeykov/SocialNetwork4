#include "ObjectFactory.h"

Topic ObjectFactory::createTopic(const SocialNetwork& socialNetwork)
{
	//Ensure a logged in user creates the topic
	if (!socialNetwork.isThereLoggedInUser()) {
		throw std::runtime_error("Topic could not be created! Please log in before creating!");
	}

	//advice recieved: get input for all the metadata and create a topic, then add it to the currTopics vector

	Topic newTopic;

	//Title
	ConsoleInputGetter::recieveTitleInput(newTopic);
	if (!InputValidator::isValidTitle(newTopic.getTitle())) {
		throw std::runtime_error("Topic could not be created! Invalid Title!");
	}

	//Description
	ConsoleInputGetter::recieveDescriptionInput(newTopic);
	if (!InputValidator::isValidDescription(newTopic.getDescription())) {
		throw std::runtime_error("Topic could not be created! Invalid Description!");
	}

	//CreatorId
	newTopic.setCreatorId(socialNetwork.getLoggedInUser().getId());

	//id
	if (socialNetwork.getCurrTopics().back().getTitle() != nullptr) {
		size_t lastTopicId = socialNetwork.getCurrTopics().back().getId();
		newTopic.setId(lastTopicId + 1);
	}

	else {
		newTopic.setId(0);
	}

	return newTopic;
}
