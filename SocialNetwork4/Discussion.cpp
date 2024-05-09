#include "Discussion.h"

Discussion::Discussion() : title(nullptr), content(nullptr), topicId(0), creatorId(0), id(0), comments() {}

Discussion::Discussion(CustomString& title,
	CustomString& content, size_t topicId,
	size_t creatorId, size_t id) :
	title(title), content(content), topicId(topicId), creatorId(creatorId), id(id), comments() {}

Discussion::Discussion(const char* title, const char* content,
	size_t topicId, size_t creatorId, size_t id) :
	title(title), content(content), topicId(topicId), creatorId(creatorId), id(id), comments() {}

Discussion::Discussion(const Discussion& other) :
	title(other.title), content(other.content), topicId(other.topicId),
	creatorId(other.creatorId), id(other.id), comments(other.comments) {}

Discussion::~Discussion()
{
}

const CustomString& Discussion::getTitle() const
{
	return title;
}

const CustomString& Discussion::getContent() const
{
	return content;
}

const size_t Discussion::getTopicId() const
{
	return topicId;
}

const size_t Discussion::getCreatorId() const
{
	return creatorId;
}

const size_t Discussion::getId() const
{
	return id;
}

Vector<Comment>& Discussion::getComments()
{
	return comments;
}

const Vector<Comment>& Discussion::getComments() const
{
	return comments;
}

void Discussion::setTitle(const char* title)
{
	this->title = title;
}

void Discussion::setTitle(const CustomString& title)
{
	this->title = title;
}

void Discussion::setContent(const char* content)
{
	this->content = content;
}

void Discussion::setContent(const CustomString& content)
{
	this->content = content;
}

void Discussion::setTopicId(size_t topicId)
{
	this->topicId = topicId;
}

void Discussion::setCreatorId(size_t creatorId)
{
	this->creatorId = creatorId;
}

void Discussion::setId(size_t id)
{
	this->id = id;
}

void Discussion::addComment(const Comment& newComment)
{
	comments.pushBack(newComment);
}

bool Discussion::isEqualWithoutId(const Discussion& other) const
{
	return (title == other.title &&
		content == other.content &&
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
		content = other.content;
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

