#pragma once
#include "String.h"
#include "Reply.h"
#include "Vector.h"

class Reply;

class Comment
{
public:

	Comment();

	Comment(const String& author, const String& text,
		const int score, const size_t id, const size_t postId);

	Comment(const char* author, const char* text,
		const int score, const size_t id, const size_t postId);

	Comment(const Comment& other);

	const String& getAuthor() const;
	const String& getText() const;
	const int getScore() const;
	const size_t getId() const;
	const size_t getPostId() const;

	const Vector<Reply>& getReplies() const;
	Vector<Reply>& getReplies();

	void setAuthor(const char* newAuthor);
	void setAuthor(const String& newAuthor);

	void setText(const char* newText);
	void setText(const String& newText);

	void setScore(const int newScore);
	void setId(const size_t newId);
	void setPostId(const size_t newPostId);

	void setReplies(const Vector<Reply>& newReplies);
	void addReply(const Reply& newReply);

	bool isEqualWithoutId(const Comment& other) const;
	bool isNotEqualWithoutId(const Comment& other) const;

	void clear();

	Comment& operator=(const Comment& other);
	bool operator==(const Comment& other) const;
	bool operator!=(const Comment& other) const;

private:
	
	friend class Reply;

	String author;
	String text;
	int score;
	size_t id;
	size_t postId;

	Vector<Reply> replies;
};
