#pragma once
#include "CustomString.h"

class Comment
{
public:

	Comment();

	Comment(CustomString& author, CustomString& text,
		int score, unsigned id, unsigned discussionId);

	Comment(const char* author, const char* text,
		int score, unsigned id, unsigned discussionId);

	const CustomString& getAuthor() const;
	const CustomString& getText() const;
	const int getScore() const;
	const unsigned getId() const;
	const unsigned getDiscussionId() const;

	void setAuthor(const char* newAuthor);
	void setAuthor(const CustomString& newAuthor);

	void setText(const char* newText);
	void setText(const CustomString& newText);

	void setScore(int newScore);
	void setId(unsigned newId);
	void setDiscussionId(unsigned newDiscussionId);

	bool isEqualWithoutId(const Comment& other) const;
	bool isNotEqualWithoutId(const Comment& other) const;

	Comment& operator=(const Comment& other);
	bool operator==(const Comment& other) const;
	bool operator!=(const Comment& other) const;


private:
	CustomString author;
	CustomString text;
	int score;
	unsigned id;
	unsigned discussionId;
};
