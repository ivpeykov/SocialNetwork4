#include "Topic.h"

Topic::Topic() : title(nullptr), description(nullptr), creatorId(SIZE_MAX), id(SIZE_MAX), posts(1) {}

Topic::Topic(const String& title, const String& description,
    const size_t creatorId, const size_t id) :
    title(title), description(description), creatorId(creatorId), id(id), posts(1) {}

Topic::Topic(const char* title, const char* description,
    const size_t creatorId, const size_t id) :
    title(title), description(description), creatorId(creatorId), id(id), posts(1) {}

Topic::Topic(const char* title, const char* description, 
    const size_t creatorId, const size_t id, const Vector<Post>& posts) : title(title), description(description), creatorId(creatorId), id(id), posts(posts)
{
}

Topic::Topic(const Topic& other) :
    title(other.title), description(other.description), creatorId(other.creatorId),
    id(other.id), posts(other.posts) {}

Topic::~Topic()
{
}

const String& Topic::getTitle() const
{
    return title;
}

const String& Topic::getDescription() const
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

Vector<Post>& Topic::getPosts()
{
    return posts;
}

const Vector<Post>& Topic::getPosts() const
{
    return posts;
}

void Topic::setTitle(const char* newTitle)
{
    title = newTitle;
}

void Topic::setTitle(const String& newTitle)
{
    title = newTitle;
}

void Topic::setDescription(const char* newDescription)
{
    description = newDescription;
}

void Topic::setDescription(const String& newDescription)
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

void Topic::addPost(const Post& newPost)
{
    posts.pushBack(newPost);
}

bool Topic::isEqualWithoutId(const Topic& other) const
{
    return (title == other.title &&
        description == other.description &&
        creatorId == other.creatorId &&
        posts == other.posts);
}

bool Topic::isNotEqualWithoutId(const Topic& other) const
{
    return !isEqualWithoutId(other);
}

void Topic::clear()
{
    title.clearString();
    description.clearString();
    creatorId = SIZE_MAX;
    id = SIZE_MAX;
    posts.clear();
}

Topic& Topic::operator=(const Topic& other)
{
    if (this != &other) {
        title = other.title;
        description = other.description;
        creatorId = other.creatorId;
        id = other.id;
        posts = other.posts;
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
