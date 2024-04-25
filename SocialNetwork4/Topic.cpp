#include "Topic.h"

Topic::Topic() : title(nullptr), description(nullptr), creatorId(0), id(0), discussions() {}

Topic::Topic(CustomString& title, CustomString& description,
    unsigned creatorId, unsigned id) :
    title(title), description(description), creatorId(creatorId), id(id), discussions() {}

Topic::Topic(const char* title, const char* description,
    unsigned creatorId, unsigned id) :
    title(title), description(description), creatorId(creatorId), id(id), discussions() {}

Topic::Topic(const char* title, const char* description, unsigned creatorId, unsigned id, Vector<Discussion>& discussions) : title(title), description(description), creatorId(creatorId), id(id), discussions(discussions)
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

const unsigned Topic::getCreatorId() const
{
    return creatorId;
}

const unsigned Topic::getId() const
{
    return id;
}

Vector<Discussion>& Topic::getDiscussions()
{
    return discussions;
}

void Topic::setTitle(const char* newTitle)
{
    title = newTitle;
}

void Topic::setTitle(CustomString& newTitle)
{
    title = newTitle;
}

void Topic::setDescription(const char* newDescription)
{
    description = newDescription;
}

void Topic::setDescription(CustomString& newDescription)
{
    description = newDescription;
}

void Topic::setCreatorId(unsigned newCreatorId)
{
    creatorId = newCreatorId;
}

void Topic::setId(unsigned newId)
{
    id = newId;
}

void Topic::addDiscussion(Discussion& newDiscussion)
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
