#include "Comment.h"

Comment::Comment() : author(nullptr), text(nullptr), score(0), id(SIZE_MAX), postId(SIZE_MAX), replies(1) {
    replies.back().setParentCommentId(id);
}

Comment::Comment(const String& author, const String& text,
    const int score, const size_t id, const size_t postId) :
    author(author), text(text), score(score), id(id), postId(postId), replies(1) {

    replies.back().setParentCommentId(id);
}

Comment::Comment(const char* author, const char* text,
    const int score, const size_t id, const size_t postId) :
    author(author), text(text), score(score), id(id), postId(postId), replies(1) {
    replies.back().setParentCommentId(id);
}

Comment::Comment(const Comment& other) : author(other.author), text(other.text), score(other.score), id(other.id), postId(other.postId), replies(other.replies)
{
}

const String& Comment::getAuthor() const
{
    return author;
}

const String& Comment::getText() const
{
    return text;
}

const int Comment::getScore() const
{
    return score;
}

const size_t Comment::getId() const
{
    return id;
}

const size_t Comment::getPostId() const
{
    return postId;
}

const Vector<Reply>& Comment::getReplies() const
{
    return replies;
}

Vector<Reply>& Comment::getReplies()
{
    return replies;
}

void Comment::setAuthor(const char* newAuthor)
{
    author = newAuthor;
}

void Comment::setAuthor(const String& newAuthor)
{
    author = newAuthor;
}

void Comment::setText(const char* newText)
{
    text = newText;
}

void Comment::setText(const String& newText)
{
    text = newText;
}

void Comment::setScore(const int newScore)
{
    score = newScore;
}

void Comment::setId(const size_t newId)
{
    id = newId;
}

void Comment::setPostId(const size_t newPostId)
{
    postId = newPostId;
}

void Comment::setReplies(const Vector<Reply>& newReplies)
{
    replies = newReplies;
}

void Comment::addReply(const Reply& newReply)
{
    replies.pushBack(newReply);
}

bool Comment::isEqualWithoutId(const Comment& other) const
{
    return (author == other.author &&
        text == other.text &&
        score == other.score &&
        postId == other.postId &&
        replies == other.replies);
}

bool Comment::isNotEqualWithoutId(const Comment& other) const
{
    return !isEqualWithoutId(other);
}

void Comment::clear()
{
    author.clearString();
    text.clearString();
    score = 0;
    id = SIZE_MAX;
    postId = SIZE_MAX;

    replies.clear();
}

Comment& Comment::operator=(const Comment& other)
{
    if (this != &other) {

        author = other.author;
        text = other.text;
        score = other.score;
        id = other.id;
        postId = other.postId;
        replies = other.replies; 
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
