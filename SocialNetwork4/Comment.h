#pragma once
#include "CustomString.h"

class Comment
{
public:

	Comment();

	Comment(const CustomString& author, const CustomString& text,
		const int score, const size_t id, const size_t discussionId);

	Comment(const char* author, const char* text,
		const int score, const size_t id, const size_t discussionId);

	const CustomString& getAuthor() const;
	const CustomString& getText() const;
	const int getScore() const;
	const size_t getId() const;
	const size_t getDiscussionId() const;

	void setAuthor(const char* newAuthor);
	void setAuthor(const CustomString& newAuthor);

	void setText(const char* newText);
	void setText(const CustomString& newText);

	void setScore(const int newScore);
	void setId(const size_t newId);
	void setDiscussionId(const size_t newDiscussionId);

	bool isEqualWithoutId(const Comment& other) const;
	bool isNotEqualWithoutId(const Comment& other) const;

	Comment& operator=(const Comment& other);
	bool operator==(const Comment& other) const;
	bool operator!=(const Comment& other) const;


private:
	CustomString author;
	CustomString text;
	int score;
	size_t id;
	size_t discussionId;
};
