#pragma once
#include "Vector.h"
#include "CustomString.h"
#include "Comment.h"

//add move semantics

class Discussion
{
public:

	Discussion();

	Discussion(CustomString& title, CustomString& description,
		unsigned topicId, unsigned creatorId, unsigned id);

	Discussion(const char* title, const char* description,
		unsigned topicId, unsigned creatorId, unsigned id);

	Discussion(const Discussion& other);

	~Discussion();


	const CustomString& getTitle() const;
	const CustomString& getDescription() const;
	const unsigned getTopicId() const;
	const unsigned getCreatorId() const;
	const unsigned getId() const;
	Vector<Comment>& getComments();

	void setTitle(const char* title);
	void setTitle(CustomString& title);

	void setDescription(const char* description);
	void setDescription(CustomString& description);

	void setTopicId(unsigned topicId);
	void setCreatorId(unsigned creatorId);
	void setId(unsigned id);
	void addComment(Comment& newComment);

	bool isEqualWithoutId(const Discussion& other) const;
	bool isNotEqualWithoutId(const Discussion& other) const;

	Discussion& operator=(const Discussion& other);
	bool operator==(const Discussion& other) const;
	bool operator!=(const Discussion& other) const;

private:
	CustomString title;
	CustomString description;
	unsigned topicId;
	unsigned creatorId;
	unsigned id;
	Vector<Comment> comments;

};