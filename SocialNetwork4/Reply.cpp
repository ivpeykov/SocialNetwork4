#include "Reply.h"

//constructors and destructor
Reply::Reply() : author(nullptr), text(nullptr), score(0), id(SIZE_MAX), postId(SIZE_MAX), parentCommentId(SIZE_MAX)
{
}

Reply::Reply(const String& author, const String& text, const int score, const size_t id,
	const size_t postId, const size_t parentCommentId) :
	author(author), text(text), score(score), id(id), postId(postId),
	parentCommentId(parentCommentId)
{
}

Reply::Reply(const char* author, const char* text, const int score, const size_t id, const size_t postId, const size_t parentCommentId) :
	author(author), text(text), score(score), id(id), postId(postId),
	parentCommentId(parentCommentId)
{
}

Reply::Reply(const Reply& other) :
	author(other.author), text(other.text), score(other.score), id(other.id), postId(other.postId),
	parentCommentId(other.parentCommentId)
{
}

Reply::Reply(const Comment& comment) : author(comment.author), text(comment.text), score(comment.score), id(comment.id), postId(comment.postId), parentCommentId(SIZE_MAX)
{
}

Reply::Reply(const Comment& comment, const size_t parentCommentId) : author(comment.author), text(comment.text), score(comment.score), id(comment.id), postId(comment.postId), parentCommentId(parentCommentId)
{
}

Reply::~Reply()
{
}

//operators
Reply& Reply::operator=(const Reply& other)
{
	if (this != &other) {

		author = other.author;
		text = other.text;
		score = other.score;
		id = other.id;
		postId = other.postId;
		parentCommentId = other.parentCommentId;
	}
	return *this;
}

bool Reply::operator==(const Reply& other) const
{
	return (id == other.id && isEqualWithoutId(other));
}

bool Reply::operator!=(const Reply& other) const
{
	return !(*this == other);
}

//methods tied to operators
bool Reply::isEqualWithoutId(const Reply& other) const
{
	return (author == other.author &&
		text == other.text &&
		score == other.score &&
		postId == other.postId &&
		parentCommentId == other.parentCommentId);
}

bool Reply::isNotEqualWithoutId(const Reply& other) const
{
	return !isEqualWithoutId(other);
}

//getters
const String& Reply::getAuthor() const
{
	return author;
}

const String& Reply::getText() const
{
	return text;
}

const int Reply::getScore() const
{
	return score;
}

const size_t Reply::getId() const
{
	return id;
}

const size_t Reply::getPostId() const
{
	return postId;
}

const size_t Reply::getParentCommentId() const
{
	return parentCommentId;
}

//setters
void Reply::setAuthor(const char* newAuthor)
{
	author = newAuthor;
}

void Reply::setAuthor(const String& newAuthor)
{
	author = newAuthor;
}

void Reply::setText(const char* newText)
{
	text = newText;
}

void Reply::setText(const String& newText)
{
	text = newText;
}

void Reply::setScore(const int newScore)
{
	score = newScore;
}

void Reply::setId(const size_t newId)
{
	id = newId;
}

void Reply::setPostId(const size_t newPostId)
{
	postId = newPostId;
}

void Reply::setParentCommentId(const size_t newId)
{
	parentCommentId = newId;
}