#include "Topic.h"

Topic::Topic() : title(nullptr), description(nullptr), creatorId(SIZE_MAX), id(SIZE_MAX), discussions(1) {}

Topic::Topic(const CustomString& title, const CustomString& description,
    const size_t creatorId, const size_t id) :
    title(title), description(description), creatorId(creatorId), id(id), discussions(1) {}

Topic::Topic(const char* title, const char* description,
    const size_t creatorId, const size_t id) :
    title(title), description(description), creatorId(creatorId), id(id), discussions(1) {}

Topic::Topic(const char* title, const char* description, 
    const size_t creatorId, const size_t id, const Vector<Discussion>& discussions) : title(title), description(description), creatorId(creatorId), id(id), discussions(discussions)
{
}

Topic::Topic(const Topic& other) :
    title(other.title), description(other.description), creatorId(other.creatorId),
    id(other.id), discussions(other.discussions) {}

Topic::~Topic()
{
}

const CustomString& Topic::getTitle() const
{
    return title;
}

const CustomString& Topic::getDescription() const
{
    return description;
}

const size_t Topic::getCreatorId() const
{
    return creatorId;
}

const size_t Topic::getId() const
{
    return id;
}

Vector<Discussion>& Topic::getDiscussions()
{
    return discussions;
}

const Vector<Discussion>& Topic::getDiscussions() const
{
    return discussions;
}

void Topic::setTitle(const char* newTitle)
{
    title = newTitle;
}

void Topic::setTitle(const CustomString& newTitle)
{
    title = newTitle;
}

void Topic::setDescription(const char* newDescription)
{
    description = newDescription;
}

void Topic::setDescription(const CustomString& newDescription)
{
    description = newDescription;
}

void Topic::setCreatorId(const size_t newCreatorId)
{
    creatorId = newCreatorId;
}

void Topic::setId(const size_t newId)
{
    id = newId;
}

void Topic::addDiscussion(const Discussion& newDiscussion)
{
    discussions.pushBack(newDiscussion);
}

bool Topic::isEqualWithoutId(const Topic& other) const
{
    return (title == other.title &&
        description == other.description &&
        creatorId == other.creatorId &&
        discussions == other.discussions);
}

bool Topic::isNotEqualWithoutId(const Topic& other) const
{
    return !isEqualWithoutId(other);
}

Topic& Topic::operator=(const Topic& other)
{
    if (this != &other) {
        title = other.title;
        description = other.description;
        creatorId = other.creatorId;
        id = other.id;
        discussions = other.discussions;
    }

    return *this;
}

bool Topic::operator==(const Topic& other) const
{
    return (id == other.id && isEqualWithoutId(other));
}

bool Topic::operator!=(const Topic& other) const
{
    return !(*this == other);
}
