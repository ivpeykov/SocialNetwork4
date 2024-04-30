#include "Discussion.h"

Discussion::Discussion() : title(nullptr), description(nullptr), topicId(0), creatorId(0), id(0), comments() {}

Discussion::Discussion(CustomString& title,
	CustomString& description, unsigned topicId,
	unsigned creatorId, unsigned id) :
	title(title), description(description), topicId(topicId), creatorId(creatorId), id(id), comments() {}

Discussion::Discussion(const char* title, const char* description,
	unsigned topicId, unsigned creatorId, unsigned id) :
	title(title), description(description), topicId(topicId), creatorId(creatorId), id(id), comments() {}

Discussion::Discussion(const Discussion& other) :
	title(other.title), description(other.description), topicId(other.topicId),
	creatorId(other.creatorId), id(other.id), comments(other.comments) {}

Discussion::~Discussion()
{
}

const CustomString& Discussion::getTitle() const
{
	return title;
}

const CustomString& Discussion::getDescription() const
{
	return description;
}

const unsigned Discussion::getTopicId() const
{
	return topicId;
}

const unsigned Discussion::getCreatorId() const
{
	return creatorId;
}

const unsigned Discussion::getId() const
{
	return id;
}

Vector<Comment>& Discussion::getComments()
{
	return comments;
}

void Discussion::setTitle(const char* title)
{
	this->title = title;
}

void Discussion::setTitle(CustomString& title)
{
	this->title = title;
}

void Discussion::setDescription(const char* description)
{
	this->description = description;
}

void Discussion::setDescription(CustomString& description)
{
	this->description = description;
}

void Discussion::setTopicId(unsigned topicId)
{
	this->topicId = topicId;
}

void Discussion::setCreatorId(unsigned creatorId)
{
	this->creatorId = creatorId;
}

void Discussion::setId(unsigned id)
{
	this->id = id;
}

void Discussion::addComment(Comment& newComment)
{
	comments.pushBack(newComment);
}

bool Discussion::isEqualWithoutId(const Discussion& other) const
{
	return (title == other.title &&
		description == other.description &&
		topicId == other.topicId &&
		creatorId == other.creatorId &&
		comments == other.comments);
}

bool Discussion::isNotEqualWithoutId(const Discussion& other) const
{
	return !isEqualWithoutId(other);
}

Discussion& Discussion::operator=(const Discussion& other)
{
	if (this != &other) {
		title = other.title;
		description = other.description;
		topicId = other.topicId;
		creatorId = other.creatorId;
		id = other.id;
		comments = other.comments;
	}

	return *this;
}

bool Discussion::operator==(const Discussion& other) const
{
	return (id == other.id && isEqualWithoutId(other));
}

bool Discussion::operator!=(const Discussion& other) const
{
	return !(*this == other);
}

