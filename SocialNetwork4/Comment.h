#pragma once
#include "CustomString.h"
#include "Reply.h"
#include "Vector.h"

class Reply;

class Comment //change loading, saving of comments, creating of comments
{
public:

	Comment();

	Comment(const CustomString& author, const CustomString& text,
		const int score, const size_t id, const size_t discussionId);

	Comment(const char* author, const char* text,
		const int score, const size_t id, const size_t discussionId);

	Comment(const Comment& other);

	const CustomString& getAuthor() const;
	const CustomString& getText() const;
	const int getScore() const;
	const size_t getId() const;
	const size_t getDiscussionId() const;

	const Vector<Reply>& getReplies() const;
	Vector<Reply>& getReplies();

	void setAuthor(const char* newAuthor);
	void setAuthor(const CustomString& newAuthor);

	void setText(const char* newText);
	void setText(const CustomString& newText);

	void setScore(const int newScore);
	void setId(const size_t newId);
	void setDiscussionId(const size_t newDiscussionId);

	void setReplies(const Vector<Reply>& newReplies);
	void addReply(const Reply& newReply);

	bool isEqualWithoutId(const Comment& other) const;
	bool isNotEqualWithoutId(const Comment& other) const;

	Comment& operator=(const Comment& other);
	bool operator==(const Comment& other) const;
	bool operator!=(const Comment& other) const;


private:
	
	friend class Reply;

	CustomString author;
	CustomString text;
	int score;
	size_t id;
	size_t discussionId;

	Vector<Reply> replies;
};
