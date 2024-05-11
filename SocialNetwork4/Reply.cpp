#include "Reply.h"

Reply::Reply() : author(nullptr), text(nullptr), score(0), id(SIZE_MAX), discussionId(SIZE_MAX), parentCommentId(SIZE_MAX)
{
}

Reply::Reply(const CustomString& author, const CustomString& text, const int score, const size_t id, 
	const size_t discussionId, const size_t parentCommentId) : 
	author(author), text(text), score(score), id(id), discussionId(discussionId),
	parentCommentId(parentCommentId)
{
}

Reply::Reply(const char* author, const char* text, const int score, const size_t id, const size_t discussionId, const size_t parentCommentId) : 
	author(author), text(text), score(score), id(id), discussionId(discussionId),
	parentCommentId(parentCommentId)
{
}

Reply::Reply(const Reply& other) : 
	author(other.author), text(other.text), score(other.score), id(other.id), discussionId(other.discussionId),
	parentCommentId(other.parentCommentId)
{
}

Reply::Reply(const Comment& comment) : author(comment.author), text(comment.text), score(comment.score), id(comment.id), discussionId(comment.discussionId), parentCommentId(SIZE_MAX)
{
}

Reply::Reply(const Comment& comment, const size_t parentCommentId) : author(comment.author), text(comment.text), score(comment.score), id(comment.id), discussionId(comment.discussionId), parentCommentId(parentCommentId)
{
}

Reply::~Reply()
{
}

const CustomString& Reply::getAuthor() const
{
	return author;
}

const CustomString& Reply::getText() const
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

const size_t Reply::getDiscussionId() const
{
	return discussionId;
}

const size_t Reply::getParentCommentId() const
{
	return parentCommentId;
}

void Reply::setAuthor(const char* newAuthor)
{
	author = newAuthor;
}

void Reply::setAuthor(const CustomString& newAuthor)
{
	author = newAuthor;
}

void Reply::setText(const char* newText)
{
	text = newText;
}

void Reply::setText(const CustomString& newText)
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

void Reply::setDiscussionId(const size_t newDiscussionId)
{
	discussionId = newDiscussionId;
}

void Reply::setParentCommentId(const size_t newId)
{
	parentCommentId = newId;
}

bool Reply::isEqualWithoutId(const Reply& other) const
{
	return (author == other.author &&
		text == other.text &&
		score == other.score &&
		discussionId == other.discussionId &&
		parentCommentId == other.parentCommentId);
}

bool Reply::isNotEqualWithoutId(const Reply& other) const
{
	return !isEqualWithoutId(other);
}

Reply& Reply::operator=(const Reply& other)
{
	if (this != &other) {

		author = other.author;
		text = other.text;
		score = other.score;
		id = other.id;
		discussionId = other.discussionId;
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
