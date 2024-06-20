#pragma once
#include "Comment.h"

class Comment;

class Reply
{

public:

	//constructors and destructor
	Reply();

	Reply(const String& author, const String& text,
		const int score, const size_t id, const size_t postId,
		const size_t parentCommentId);

	Reply(const char* author, const char* text,
		const int score, const size_t id, const size_t postId,
		const size_t parentCommentId);

	Reply(const Reply& other);
	Reply(const Comment& comment);
	Reply(const Comment& comment, const size_t parentCommentId);

	~Reply();

	//operators
	Reply& operator=(const Reply& other);
	bool operator==(const Reply& other) const;
	bool operator!=(const Reply& other) const;

	//methods tied to operators
	bool isEqualWithoutId(const Reply& other) const;
	bool isNotEqualWithoutId(const Reply& other) const;

	//getters
	const String& getAuthor() const;
	const String& getText() const;
	const int getScore() const;
	const size_t getId() const;
	const size_t getPostId() const;
	const size_t getParentCommentId() const;

	//setters
	void setAuthor(const char* newAuthor);
	void setAuthor(const String& newAuthor);

	void setText(const char* newText);
	void setText(const String& newText);

	void setScore(const int newScore);
	void setId(const size_t newId);
	void setPostId(const size_t newPostId);
	void setParentCommentId(const size_t newId);

private:
	String author;
	String text;
	int score;
	size_t id;
	size_t postId;

	size_t parentCommentId;

};

