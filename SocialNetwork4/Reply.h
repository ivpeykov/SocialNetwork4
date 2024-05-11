#pragma once
#include "Comment.h"

class Comment;

class Reply
{

public:

	Reply();

	Reply(const CustomString& author, const CustomString& text,
		const int score, const size_t id, const size_t discussionId,
		const size_t parentCommentId);

	Reply(const char* author, const char* text,
		const int score, const size_t id, const size_t discussionId,
		const size_t parentCommentId);

	Reply(const Reply& other);
	Reply(const Comment& comment);
	Reply(const Comment& comment, const size_t parentCommentId);

	~Reply();

	const CustomString& getAuthor() const;
	const CustomString& getText() const;
	const int getScore() const;
	const size_t getId() const;
	const size_t getDiscussionId() const;
	const size_t getParentCommentId() const;

	void setAuthor(const char* newAuthor);
	void setAuthor(const CustomString& newAuthor);

	void setText(const char* newText);
	void setText(const CustomString& newText);

	void setScore(const int newScore);
	void setId(const size_t newId);
	void setDiscussionId(const size_t newDiscussionId);
	void setParentCommentId(const size_t newId);

	bool isEqualWithoutId(const Reply& other) const;
	bool isNotEqualWithoutId(const Reply& other) const;

	Reply& operator=(const Reply& other);
	bool operator==(const Reply& other) const;
	bool operator!=(const Reply& other) const;

private:
	CustomString author;
	CustomString text;
	int score;
	size_t id;
	size_t discussionId;

	size_t parentCommentId;
};

