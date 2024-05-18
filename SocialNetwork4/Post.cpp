#include "Post.h"

Post::Post() : title(nullptr), content(nullptr), topicId(SIZE_MAX), creatorId(SIZE_MAX), id(SIZE_MAX), comments(1) {}

Post::Post(String& title,
	String& content, size_t topicId,
	size_t creatorId, size_t id) :
	title(title), content(content), topicId(topicId), creatorId(creatorId), id(id), comments(1) {}

Post::Post(const char* title, const char* content,
	size_t topicId, size_t creatorId, size_t id) :
	title(title), content(content), topicId(topicId), creatorId(creatorId), id(id), comments(1) {}

Post::Post(const Post& other) :
	title(other.title), content(other.content), topicId(other.topicId),
	creatorId(other.creatorId), id(other.id), comments(other.comments) {}

Post::~Post()
{
}

const String& Post::getTitle() const
{
	return title;
}

const String& Post::getContent() const
{
	return content;
}

const size_t Post::getTopicId() const
{
	return topicId;
}

const size_t Post::getCreatorId() const
{
	return creatorId;
}

const size_t Post::getId() const
{
	return id;
}

Vector<Comment>& Post::getComments()
{
	return comments;
}

const Vector<Comment>& Post::getComments() const
{
	return comments;
}

void Post::setTitle(const char* title)
{
	this->title = title;
}

void Post::setTitle(const String& title)
{
	this->title = title;
}

void Post::setContent(const char* content)
{
	this->content = content;
}

void Post::setContent(const String& content)
{
	this->content = content;
}

void Post::setTopicId(size_t topicId)
{
	this->topicId = topicId;
}

void Post::setCreatorId(size_t creatorId)
{
	this->creatorId = creatorId;
}

void Post::setId(size_t id)
{
	this->id = id;
}

void Post::addComment(const Comment& newComment)
{
	comments.pushBack(newComment);
}

bool Post::isEqualWithoutId(const Post& other) const
{
	return (title == other.title &&
		content == other.content &&
		topicId == other.topicId &&
		creatorId == other.creatorId &&
		comments == other.comments);
}

bool Post::isNotEqualWithoutId(const Post& other) const
{
	return !isEqualWithoutId(other);
}

void Post::clear()
{
	title.clearString();
	content.clearString();
	topicId = SIZE_MAX;
	creatorId = SIZE_MAX;
	id = SIZE_MAX;
	comments.clear();
}

Post& Post::operator=(const Post& other)
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

bool Post::operator==(const Post& other) const
{
	return (id == other.id && isEqualWithoutId(other));
}

bool Post::operator!=(const Post& other) const
{
	return !(*this == other);
}