#include "Comment.h"

Comment::Comment() : author(nullptr), text(nullptr), score(0), id(0), discussionId(0) {}

Comment::Comment(CustomString& author, CustomString& text,
    int score, unsigned id, unsigned discussionId) :
    author(author), text(text), score(score), id(id), discussionId(discussionId) {}

Comment::Comment(const char* author, const char* text,
    int score, unsigned id, unsigned discussionId) :
    author(author), text(text), score(score), id(id), discussionId(discussionId) {}

const CustomString& Comment::getAuthor() const
{
    return author;
}

const CustomString& Comment::getText() const
{
    return text;
}

const int Comment::getScore() const
{
    return score;
}

const unsigned Comment::getId() const
{
    return id;
}

const unsigned Comment::getDiscussionId() const
{
    return discussionId;
}

void Comment::setAuthor(const char* newAuthor)
{
    author = newAuthor;
}

void Comment::setAuthor(const CustomString& newAuthor)
{
    author = newAuthor;
}

void Comment::setText(const char* newText)
{
    text = newText;
}

void Comment::setText(const CustomString& newText)
{
    text = newText;
}

void Comment::setScore(int newScore)
{
    score = newScore;
}

void Comment::setId(unsigned newId)
{
    id = newId;
}

void Comment::setDiscussionId(unsigned newDiscussionId)
{
    discussionId = newDiscussionId;
}

bool Comment::isEqualWithoutId(const Comment& other) const
{
    return (author == other.author &&
        text == other.text &&
        score == other.score &&
        discussionId == other.discussionId);
}

bool Comment::isNotEqualWithoutId(const Comment& other) const
{
    return !isEqualWithoutId(other);
}

Comment& Comment::operator=(const Comment& other)
{
    if (this != &other) {

        author = other.author;
        text = other.text;
        score = other.score;
        id = other.id;
        discussionId = other.discussionId;
    }
    return *this;
}

bool Comment::operator==(const Comment& other) const
{
    return (id == other.id && isEqualWithoutId(other));
}

bool Comment::operator!=(const Comment& other) const
{
    return !(*this == other);
}
